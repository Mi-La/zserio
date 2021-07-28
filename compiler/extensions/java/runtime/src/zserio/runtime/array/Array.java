package zserio.runtime.array;

import java.io.IOException;

import zserio.runtime.BitPositionUtil;
import zserio.runtime.BitSizeOfCalculator;
import zserio.runtime.ZserioError;
import zserio.runtime.array.OffsetChecker;
import zserio.runtime.io.BitStreamReader;
import zserio.runtime.io.BitStreamWriter;

/**
 * Array wrapper which is used for mapping of all zserio arrays.
 *
 * Array wrapper is defined by:
 * - raw array holder which contains raw array
 * - array traits which define zserio methods for array elements of corresponding Java native types
 * - array type (normal, auto, implicit)
 * - offset initializer to set offsets for indexed offsets arrays
 * - offset checker to check offsets for indexed offsets arrays
 */
public class Array
{
    /**
     * Constructor.
     *
     * @param rawArrayHolder Raw array holder to construct from.
     * @param arrayTraits    Array traits to construct from.
     */
    public Array(RawArrayHolder rawArrayHolder, ArrayTraits arrayTraits)
    {
        this(rawArrayHolder, arrayTraits, ArrayType.NORMAL, null, null);
    }

    /**
     * Constructor.
     *
     * @param rawArrayHolder Raw array holder to construct from.
     * @param arrayTraits    Array traits to construct from.
     * @param arrayType      Array type to construct from.
     */
    public Array(RawArrayHolder rawArrayHolder, ArrayTraits arrayTraits, ArrayType arrayType)
    {
        this(rawArrayHolder, arrayTraits, arrayType, null, null);
    }

    /**
     * Constructor.
     *
     * @param rawArrayHolder    Raw array holder to construct from.
     * @param arrayTraits       Array traits to construct from.
     * @param arrayType         Array type to construct from.
     * @param offsetInitializer Offset initializer to construct from.
     * @param offsetChecker     Offset checker to construct from.
     */
    public Array(RawArrayHolder rawArrayHolder, ArrayTraits arrayTraits, ArrayType arrayType,
            OffsetInitializer offsetInitializer, OffsetChecker offsetChecker)
    {
        this.rawArrayHolder = rawArrayHolder;
        this.arrayTraits = arrayTraits;
        this.arrayType = arrayType;
        this.offsetInitializer = offsetInitializer;
        this.offsetChecker = offsetChecker;
    }

    /**
     * Gets the underlying raw array.
     *
     * @return Underlying raw array.
     */
    public <T> T getRawArray()
    {
        return rawArrayHolder.getRawArray();
    }

    /**
     * Gets the bit size of the array if it is stored in the bit stream.
     *
     * @param bitPosition Current bit position in the bit stream.
     *
     * @return Bit size of the array if it is stored in the bit stream.
     */
    public int bitSizeOf(long bitPosition)
    {
        long endBitPosition = bitPosition;
        final int size = rawArrayHolder.size();
        if (arrayType == ArrayType.AUTO)
            endBitPosition += BitSizeOfCalculator.getBitSizeOfVarSize(size);

        if (arrayTraits.isBitSizeOfConstant() && size > 0)
        {
            final int elementSize = arrayTraits.bitSizeOf(rawArrayHolder, endBitPosition, 0);
            if (offsetInitializer != null)
            {
                endBitPosition += size * elementSize;
            }
            else
            {
                endBitPosition = BitPositionUtil.alignTo(Byte.SIZE, endBitPosition);
                endBitPosition += elementSize + (size - 1) * BitPositionUtil.alignTo(Byte.SIZE, elementSize);
            }
        }
        else
        {
            for (int index = 0; index < size; ++index)
            {
                if (offsetInitializer != null)
                {
                    endBitPosition = BitPositionUtil.alignTo(Byte.SIZE, endBitPosition);
                }
                endBitPosition += arrayTraits.bitSizeOf(rawArrayHolder, endBitPosition, index);
            }
        }

        return (int)(endBitPosition - bitPosition);
    }

    /**
     * Initializes indexed offsets for the array.
     *
     * @param bitPosition Current bit position in the bit stream.
     *
     * @return Updated bit stream position which points to the first bit after the array.
     */
    public long initializeOffsets(long bitPosition)
    {
        long endBitPosition = bitPosition;
        final int size = rawArrayHolder.size();
        if (arrayType == ArrayType.AUTO)
            endBitPosition += BitSizeOfCalculator.getBitSizeOfVarSize(size);

        for (int index = 0; index < size; ++index)
        {
            if (offsetInitializer != null)
            {
                endBitPosition = BitPositionUtil.alignTo(Byte.SIZE, endBitPosition);
                offsetInitializer.setOffset(index, BitPositionUtil.bitsToBytes(endBitPosition));
            }
            endBitPosition = arrayTraits.initializeOffsets(rawArrayHolder, endBitPosition, index);
        }

        return endBitPosition;
    }


    /**
     * Reads the array from the bit stream.
     *
     * @param reader Bit stream reader to read from.
     *
     * @throws IOException Failure during bit stream manipulation.
     * @throws ZserioError Failure during offset checking.
     */
    public void read(BitStreamReader reader) throws IOException, ZserioError
    {
        read(reader, -1);
    }

    /**
     * Reads the array from the bit stream.
     *
     * @param reader Bit stream reader to read from.
     * @param size   Number of elements stored in the array which shall be read.
     *
     * @throws IOException Failure during bit stream manipulation.
     * @throws ZserioError Failure during offset checking.
     */
    public void read(BitStreamReader reader, int size) throws IOException, ZserioError
    {
        int readSize = size;
        if (arrayType == ArrayType.IMPLICIT)
        {
            if (!arrayTraits.isBitSizeOfConstant())
                throw new UnsupportedOperationException(
                        "Array: Implicit array elements must have constant bit size!");

            final long readerBitPosition = reader.getBitPosition();
            final int elementSize = arrayTraits.bitSizeOf(rawArrayHolder, readerBitPosition, 0);
            final long remainingBits = reader.getBufferBitSize() - readerBitPosition;
            readSize = (int)(remainingBits / elementSize);
        }
        else if (arrayType == ArrayType.AUTO)
        {
            readSize = reader.readVarSize();
        }

        rawArrayHolder.reset(readSize);

        for (int index = 0; index < readSize; ++index)
        {
            if (offsetChecker != null)
            {
                reader.alignTo(Byte.SIZE);
                offsetChecker.checkOffset(index, reader.getBytePosition());
            }
            arrayTraits.read(rawArrayHolder, reader, index);
        }
    }

    /**
     * Writes the array element to the bit stream.
     *
     * @param writer Bit stream write to write to.
     *
     * @throws IOException Failure during bit stream manipulation.
     * @throws ZserioError Failure during offset checking.
     */
    public void write(BitStreamWriter writer) throws IOException, ZserioError
    {
        final int size = rawArrayHolder.size();
        if (arrayType == ArrayType.AUTO)
            writer.writeVarSize(size);

        for (int index = 0; index < size; ++index)
        {
            if (offsetChecker != null)
            {
                writer.alignTo(Byte.SIZE);
                offsetChecker.checkOffset(index, writer.getBytePosition());
            }
            arrayTraits.write(rawArrayHolder, writer, index);
        }
    }

    private final RawArrayHolder rawArrayHolder;
    private final ArrayTraits arrayTraits;
    private final ArrayType arrayType;
    private final OffsetInitializer offsetInitializer;
    private final OffsetChecker offsetChecker;
}
