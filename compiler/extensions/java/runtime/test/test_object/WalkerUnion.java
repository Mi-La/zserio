/**
 * Automatically generated by Zserio Java extension version 2.11.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode.
 */

package test_object;

public class WalkerUnion implements zserio.runtime.io.Writer, zserio.runtime.SizeOf
{
    public WalkerUnion()
    {
    }

    public WalkerUnion(zserio.runtime.io.BitStreamReader in)
            throws java.io.IOException
    {
        read(in);
    }

    public WalkerUnion(zserio.runtime.array.PackingContextNode contextNode, zserio.runtime.io.BitStreamReader in)
            throws java.io.IOException
    {
        read(contextNode, in);
    }

    public static zserio.runtime.typeinfo.TypeInfo typeInfo()
    {
        final java.lang.String templateName = "";
        final java.util.List<zserio.runtime.typeinfo.TypeInfo> templateArguments =
                new java.util.ArrayList<zserio.runtime.typeinfo.TypeInfo>();
        final java.util.List<zserio.runtime.typeinfo.FieldInfo> fieldList =
                java.util.Arrays.asList(
                        new zserio.runtime.typeinfo.FieldInfo(
                                "value", // schemaName
                                "getValue", // getterName
                                "setValue", // setterName
                                zserio.runtime.typeinfo.TypeInfo.BuiltinTypeInfo.getUInt32(), // typeInfo
                                new java.util.ArrayList<java.util.function.BiFunction<java.lang.Object, java.lang.Integer, java.lang.Object>>(), // typeArguments
                                false, // isExtended
                                null, // alignment
                                null, // offset
                                null, // initializer
                                false, // isOptional
                                null, // optionalCondition
                                "", // isUsedIndicatorName
                                "", // isSetIndicatorName
                                null, // constraint
                                false, // isArray
                                null, // arrayLength
                                false, // isPacked
                                false // isImplicit
                        ),
                        new zserio.runtime.typeinfo.FieldInfo(
                                "text", // schemaName
                                "getText", // getterName
                                "setText", // setterName
                                zserio.runtime.typeinfo.TypeInfo.BuiltinTypeInfo.getString(), // typeInfo
                                new java.util.ArrayList<java.util.function.BiFunction<java.lang.Object, java.lang.Integer, java.lang.Object>>(), // typeArguments
                                false, // isExtended
                                null, // alignment
                                null, // offset
                                null, // initializer
                                false, // isOptional
                                null, // optionalCondition
                                "", // isUsedIndicatorName
                                "", // isSetIndicatorName
                                null, // constraint
                                false, // isArray
                                null, // arrayLength
                                false, // isPacked
                                false // isImplicit
                        ),
                        new zserio.runtime.typeinfo.FieldInfo(
                                "nestedArray", // schemaName
                                "getNestedArray", // getterName
                                "setNestedArray", // setterName
                                test_object.WalkerNested.typeInfo(), // typeInfo
                                java.util.Arrays.asList(), // typeArguments
                                false, // isExtended
                                null, // alignment
                                null, // offset
                                null, // initializer
                                false, // isOptional
                                null, // optionalCondition
                                "", // isUsedIndicatorName
                                "", // isSetIndicatorName
                                null, // constraint
                                true, // isArray
                                null, // arrayLength
                                false, // isPacked
                                false // isImplicit
                        )
                );
        final java.util.List<zserio.runtime.typeinfo.ParameterInfo> parameterList =
                new java.util.ArrayList<zserio.runtime.typeinfo.ParameterInfo>();
        final java.util.List<zserio.runtime.typeinfo.FunctionInfo> functionList =
                new java.util.ArrayList<zserio.runtime.typeinfo.FunctionInfo>();

        return new zserio.runtime.typeinfo.TypeInfo.UnionTypeInfo(
                "test_object.WalkerUnion", WalkerUnion.class, templateName, templateArguments,
                fieldList, parameterList, functionList
        );
    }

    public int choiceTag()
    {
        return choiceTag;
    }

    public static void createPackingContext(zserio.runtime.array.PackingContextNode contextNode)
    {
        contextNode.createChild().createContext();

        contextNode.createChild().createContext();
        contextNode.createChild();
        contextNode.createChild();
    }

    @Override
    public void initPackingContext(zserio.runtime.array.PackingContextNode contextNode)
    {
        contextNode.getChildren().get(0).getContext().init(
                new zserio.runtime.array.ArrayTraits.VarSizeArrayTraits(),
                new zserio.runtime.array.ArrayElement.IntArrayElement(choiceTag));

        switch (choiceTag)
        {
        case CHOICE_value:
            contextNode.getChildren().get(1).getContext().init(
                    new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)),
                    new zserio.runtime.array.ArrayElement.LongArrayElement(getValue()));
            break;
        case CHOICE_text:
            break;
        case CHOICE_nestedArray:
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        }
    }

    @Override
    public int bitSizeOf()
    {
        return bitSizeOf(0);
    }

    @Override
    public int bitSizeOf(long bitPosition)
    {
        long endBitPosition = bitPosition;

        endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfVarSize(choiceTag);

        switch (choiceTag)
        {
        case CHOICE_value:
            endBitPosition += 32;
            break;
        case CHOICE_text:
            endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfString(getText());
            break;
        case CHOICE_nestedArray:
            endBitPosition += ((zserio.runtime.array.Array)objectChoice).bitSizeOf(endBitPosition);
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        }

        return (int)(endBitPosition - bitPosition);
    }

    @Override
    public int bitSizeOf(zserio.runtime.array.PackingContextNode contextNode, long bitPosition)
    {
        long endBitPosition = bitPosition;

        endBitPosition += contextNode.getChildren().get(0).getContext().bitSizeOf(
                new zserio.runtime.array.ArrayTraits.VarSizeArrayTraits(),
                new zserio.runtime.array.ArrayElement.IntArrayElement(choiceTag));

        switch (choiceTag)
        {
        case CHOICE_value:
            endBitPosition += contextNode.getChildren().get(1).getContext().bitSizeOf(
                    new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)),
                    new zserio.runtime.array.ArrayElement.LongArrayElement(getValue()));
            break;
        case CHOICE_text:
            endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfString(getText());
            break;
        case CHOICE_nestedArray:
            endBitPosition += ((zserio.runtime.array.Array)objectChoice).bitSizeOfPacked(endBitPosition);
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        }

        return (int)(endBitPosition - bitPosition);
    }

    public long getValue()
    {
        return (java.lang.Long)objectChoice;
    }

    public void setValue(long value_)
    {
        choiceTag = CHOICE_value;
        objectChoice = value_;
    }

    public java.lang.String getText()
    {
        return (java.lang.String)objectChoice;
    }

    public void setText(java.lang.String text_)
    {
        choiceTag = CHOICE_text;
        objectChoice = text_;
    }

    public test_object.WalkerNested[] getNestedArray()
    {
        return (objectChoice == null) ? null : ((zserio.runtime.array.Array)objectChoice).getRawArray();
    }

    public void setNestedArray(test_object.WalkerNested[] nestedArray_)
    {
        choiceTag = CHOICE_nestedArray;
        objectChoice = new zserio.runtime.array.Array(
                new zserio.runtime.array.RawArray.ObjectRawArray<>(test_object.WalkerNested.class, nestedArray_),
                new zserio.runtime.array.ArrayTraits.WriteObjectArrayTraits<test_object.WalkerNested>(new ZserioElementFactory_nestedArray()),
                zserio.runtime.array.ArrayType.AUTO);
    }

    @Override
    public boolean equals(java.lang.Object obj)
    {
        if (obj instanceof WalkerUnion)
        {
            final WalkerUnion that = (WalkerUnion)obj;

            return
                    choiceTag == that.choiceTag &&
                    (
                        (objectChoice == null && that.objectChoice == null) ||
                        (objectChoice != null && objectChoice.equals(that.objectChoice))
                    );
        }

        return false;
    }

    @Override
    public int hashCode()
    {
        int result = zserio.runtime.HashCodeUtil.HASH_SEED;

        result = zserio.runtime.HashCodeUtil.calcHashCode(result, choiceTag);
        if (objectChoice != null)
        {
            switch (choiceTag)
            {
            case CHOICE_value:
                result = zserio.runtime.HashCodeUtil.calcHashCode(result,
                        (java.lang.Long)objectChoice);
                break;
            case CHOICE_text:
                result = zserio.runtime.HashCodeUtil.calcHashCode(result,
                        (java.lang.String)objectChoice);
                break;
            case CHOICE_nestedArray:
                result = zserio.runtime.HashCodeUtil.calcHashCode(result,
                        (zserio.runtime.array.Array)objectChoice);
                break;
            default:
                break; // UNDEFINED_CHOICE
            }
        }

        return result;
    }

    public void read(zserio.runtime.io.BitStreamReader in) throws java.io.IOException
    {
        choiceTag = in.readVarSize();

        switch (choiceTag)
        {
        case CHOICE_value:
            objectChoice = in.readUnsignedInt();
            break;
        case CHOICE_text:
            objectChoice = in.readString();
            break;
        case CHOICE_nestedArray:
            objectChoice = new zserio.runtime.array.Array(
                    new zserio.runtime.array.RawArray.ObjectRawArray<>(test_object.WalkerNested.class),
                    new zserio.runtime.array.ArrayTraits.WriteObjectArrayTraits<test_object.WalkerNested>(new ZserioElementFactory_nestedArray()),
                    zserio.runtime.array.ArrayType.AUTO);
            ((zserio.runtime.array.Array)objectChoice).read(in);
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        }
    }

    public void read(zserio.runtime.array.PackingContextNode contextNode, zserio.runtime.io.BitStreamReader in)
            throws java.io.IOException
    {
        choiceTag = ((zserio.runtime.array.ArrayElement.IntArrayElement)
                contextNode.getChildren().get(0).getContext().read(
                        new zserio.runtime.array.ArrayTraits.VarSizeArrayTraits(), in)).get();

        switch (choiceTag)
        {
        case CHOICE_value:
            objectChoice = ((zserio.runtime.array.ArrayElement.LongArrayElement)
                    contextNode.getChildren().get(1).getContext().read(
                            new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)), in)).get();
            break;
        case CHOICE_text:
            objectChoice = in.readString();
            break;
        case CHOICE_nestedArray:
            objectChoice = new zserio.runtime.array.Array(
                    new zserio.runtime.array.RawArray.ObjectRawArray<>(test_object.WalkerNested.class),
                    new zserio.runtime.array.ArrayTraits.WriteObjectArrayTraits<test_object.WalkerNested>(new ZserioElementFactory_nestedArray()),
                    zserio.runtime.array.ArrayType.AUTO);
            ((zserio.runtime.array.Array)objectChoice).readPacked(in);
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        }
    }

    @Override
    public long initializeOffsets()
    {
        return initializeOffsets(0);
    }

    @Override
    public long initializeOffsets(long bitPosition)
    {
        long endBitPosition = bitPosition;

        endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfVarSize(choiceTag);

        switch (choiceTag)
        {
        case CHOICE_value:
            endBitPosition += 32;
            break;
        case CHOICE_text:
            endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfString(getText());
            break;
        case CHOICE_nestedArray:
            endBitPosition = ((zserio.runtime.array.Array)objectChoice).initializeOffsets(endBitPosition);
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        }

        return endBitPosition;
    }

    @Override
    public long initializeOffsets(zserio.runtime.array.PackingContextNode contextNode, long bitPosition)
    {
        long endBitPosition = bitPosition;

        endBitPosition += contextNode.getChildren().get(0).getContext().bitSizeOf(
                new zserio.runtime.array.ArrayTraits.VarSizeArrayTraits(),
                new zserio.runtime.array.ArrayElement.IntArrayElement(choiceTag));

        switch (choiceTag)
        {
        case CHOICE_value:
            endBitPosition += contextNode.getChildren().get(1).getContext().bitSizeOf(
                    new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)),
                    new zserio.runtime.array.ArrayElement.LongArrayElement(getValue()));
            break;
        case CHOICE_text:
            endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfString(getText());
            break;
        case CHOICE_nestedArray:
            endBitPosition = ((zserio.runtime.array.Array)objectChoice).initializeOffsetsPacked(endBitPosition);
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        }

        return endBitPosition;
    }

    @Override
    public void write(zserio.runtime.io.BitStreamWriter out) throws java.io.IOException
    {
        out.writeVarSize(choiceTag);

        switch (choiceTag)
        {
        case CHOICE_value:
            out.writeUnsignedInt(getValue());
            break;
        case CHOICE_text:
            out.writeString(getText());
            break;
        case CHOICE_nestedArray:
            ((zserio.runtime.array.Array)objectChoice).write(out);
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        };
    }

    @Override
    public void write(zserio.runtime.array.PackingContextNode contextNode,
            zserio.runtime.io.BitStreamWriter out) throws java.io.IOException
    {
        contextNode.getChildren().get(0).getContext().write(
                new zserio.runtime.array.ArrayTraits.VarSizeArrayTraits(), out,
                new zserio.runtime.array.ArrayElement.IntArrayElement(choiceTag));

        switch (choiceTag)
        {
        case CHOICE_value:
            contextNode.getChildren().get(1).getContext().write(
                    new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)), out,
                    new zserio.runtime.array.ArrayElement.LongArrayElement(getValue()));
            break;
        case CHOICE_text:
            out.writeString(getText());
            break;
        case CHOICE_nestedArray:
            ((zserio.runtime.array.Array)objectChoice).writePacked(out);
            break;
        default:
            throw new zserio.runtime.ZserioError("No match in union WalkerUnion!");
        };
    }

    public static final int CHOICE_value = 0;
    public static final int CHOICE_text = 1;
    public static final int CHOICE_nestedArray = 2;
    public static final int UNDEFINED_CHOICE = -1;

    private static final class ZserioElementFactory_nestedArray implements zserio.runtime.array.ElementFactory<test_object.WalkerNested>
    {
        @Override
        public test_object.WalkerNested create(zserio.runtime.io.BitStreamReader in, int index)
                throws java.io.IOException
        {
            return new test_object.WalkerNested(in);
        }

        @Override
        public void createPackingContext(zserio.runtime.array.PackingContextNode contextNode)
        {
            test_object.WalkerNested.createPackingContext(contextNode);
        }

        @Override
        public test_object.WalkerNested create(zserio.runtime.array.PackingContextNode contextNode,
                zserio.runtime.io.BitStreamReader in, int index) throws java.io.IOException
        {
            return new test_object.WalkerNested(contextNode, in);
        }
    }

    private java.lang.Object objectChoice;
    private int choiceTag = UNDEFINED_CHOICE;
}
