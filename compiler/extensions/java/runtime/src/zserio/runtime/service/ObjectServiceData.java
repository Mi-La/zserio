package zserio.runtime.service;

import java.io.IOException;

import zserio.runtime.io.Writer;
import zserio.runtime.io.ByteArrayBitStreamWriter;
import zserio.runtime.ZserioError;

/** ServiceData implementation based on generated Zserio objects. */
public class ObjectServiceData<T extends Writer> implements ServiceData<T>
{
    /**
     * Constructor from object generated by Zserio.
     *
     * @param zserioObject Zserio object from which to create service data.
     */
    public ObjectServiceData(T zserioObject)
    {
        this.zserioObject = zserioObject;
        this.byteArray = null;
    }

    /**
     * Gets the Zserio object which represents the request.
     *
     * @return The Zserio object.
     */
    @Override
    public T getZserioObject()
    {
        return zserioObject;
    }

    /**
     * Gets the data which represent the request.
     *
     * @return The request data which are created by serialization of Zserio object.
     */
    @Override
    public byte[] getByteArray()
    {
        if (byteArray == null)
        {
            try
            {
                final ByteArrayBitStreamWriter writer = new ByteArrayBitStreamWriter();
                zserioObject.write(writer);
                byteArray = writer.toByteArray();
            }
            catch (IOException exception)
            {
                throw new ZserioError("ObjectServiceData: " + exception, exception);
            }
        }
        return byteArray;
    }

    private final T zserioObject;
    private byte[] byteArray;
}
