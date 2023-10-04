/**
 * Automatically generated by Zserio Java extension version 2.12.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode.
 */

package test_object;

public class CreatorObject implements zserio.runtime.io.PackableWriter, zserio.runtime.PackableSizeOf
{
    public static final class ZserioPackingContext extends zserio.runtime.array.PackingContext
    {
        public ZserioPackingContext()
        {
            value_ = new zserio.runtime.array.DeltaContext();
            nested_ = new test_object.CreatorNested.ZserioPackingContext();
            optionalNested_ = new test_object.CreatorNested.ZserioPackingContext();
        }

        public zserio.runtime.array.DeltaContext getValue()
        {
            return value_;
        }

        public test_object.CreatorNested.ZserioPackingContext getNested()
        {
            return nested_;
        }

        public test_object.CreatorNested.ZserioPackingContext getOptionalNested()
        {
            return optionalNested_;
        }

        private zserio.runtime.array.DeltaContext value_;
        private test_object.CreatorNested.ZserioPackingContext nested_;
        private test_object.CreatorNested.ZserioPackingContext optionalNested_;
    };

    public CreatorObject()
    {
    }

    public CreatorObject(zserio.runtime.io.BitStreamReader in)
            throws java.io.IOException
    {
        read(in);
    }

    public CreatorObject(zserio.runtime.array.PackingContext context, zserio.runtime.io.BitStreamReader in)
            throws java.io.IOException
    {
        read(context, in);
    }

    public CreatorObject(
            long value_,
            test_object.CreatorNested nested_,
            java.lang.String text_,
            test_object.CreatorNested[] nestedArray_,
            java.lang.String[] textArray_,
            zserio.runtime.io.BitBuffer[] externArray_,
            byte[][] bytesArray_,
            java.lang.Boolean optionalBool_,
            test_object.CreatorNested optionalNested_)
    {
        setValue(value_);
        setNested(nested_);
        setText(text_);
        setNestedArray(nestedArray_);
        setTextArray(textArray_);
        setExternArray(externArray_);
        setBytesArray(bytesArray_);
        setOptionalBool(optionalBool_);
        setOptionalNested(optionalNested_);
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
                                "nested", // schemaName
                                "getNested", // getterName
                                "setNested", // setterName
                                test_object.CreatorNested.typeInfo(), // typeInfo
                                java.util.Arrays.asList((obj, index) -> ((CreatorObject)obj).getValue()), // typeArguments
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
                                test_object.CreatorNested.typeInfo(), // typeInfo
                                java.util.Arrays.asList((obj, index) -> ((CreatorObject)obj).getValue()), // typeArguments
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
                        ),
                        new zserio.runtime.typeinfo.FieldInfo(
                                "textArray", // schemaName
                                "getTextArray", // getterName
                                "setTextArray", // setterName
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
                                true, // isArray
                                null, // arrayLength
                                false, // isPacked
                                false // isImplicit
                        ),
                        new zserio.runtime.typeinfo.FieldInfo(
                                "externArray", // schemaName
                                "getExternArray", // getterName
                                "setExternArray", // setterName
                                zserio.runtime.typeinfo.TypeInfo.BuiltinTypeInfo.getBitBuffer(), // typeInfo
                                new java.util.ArrayList<java.util.function.BiFunction<java.lang.Object, java.lang.Integer, java.lang.Object>>(), // typeArguments
                                false, // isExtended
                                null, // alignment
                                null, // offset
                                null, // initializer
                                true, // isOptional
                                null, // optionalCondition
                                "isExternArrayUsed", // isUsedIndicatorName
                                "isExternArraySet", // isSetIndicatorName
                                null, // constraint
                                true, // isArray
                                null, // arrayLength
                                false, // isPacked
                                false // isImplicit
                        ),
                        new zserio.runtime.typeinfo.FieldInfo(
                                "bytesArray", // schemaName
                                "getBytesArray", // getterName
                                "setBytesArray", // setterName
                                zserio.runtime.typeinfo.TypeInfo.BuiltinTypeInfo.getBytes(), // typeInfo
                                new java.util.ArrayList<java.util.function.BiFunction<java.lang.Object, java.lang.Integer, java.lang.Object>>(), // typeArguments
                                false, // isExtended
                                null, // alignment
                                null, // offset
                                null, // initializer
                                true, // isOptional
                                null, // optionalCondition
                                "isBytesArrayUsed", // isUsedIndicatorName
                                "isBytesArraySet", // isSetIndicatorName
                                null, // constraint
                                true, // isArray
                                null, // arrayLength
                                false, // isPacked
                                false // isImplicit
                        ),
                        new zserio.runtime.typeinfo.FieldInfo(
                                "optionalBool", // schemaName
                                "getOptionalBool", // getterName
                                "setOptionalBool", // setterName
                                zserio.runtime.typeinfo.TypeInfo.BuiltinTypeInfo.getBool(), // typeInfo
                                new java.util.ArrayList<java.util.function.BiFunction<java.lang.Object, java.lang.Integer, java.lang.Object>>(), // typeArguments
                                false, // isExtended
                                null, // alignment
                                null, // offset
                                null, // initializer
                                true, // isOptional
                                null, // optionalCondition
                                "isOptionalBoolUsed", // isUsedIndicatorName
                                "isOptionalBoolSet", // isSetIndicatorName
                                null, // constraint
                                false, // isArray
                                null, // arrayLength
                                false, // isPacked
                                false // isImplicit
                        ),
                        new zserio.runtime.typeinfo.FieldInfo(
                                "optionalNested", // schemaName
                                "getOptionalNested", // getterName
                                "setOptionalNested", // setterName
                                test_object.CreatorNested.typeInfo(), // typeInfo
                                java.util.Arrays.asList((obj, index) -> ((CreatorObject)obj).getValue()), // typeArguments
                                false, // isExtended
                                null, // alignment
                                null, // offset
                                null, // initializer
                                true, // isOptional
                                null, // optionalCondition
                                "isOptionalNestedUsed", // isUsedIndicatorName
                                "isOptionalNestedSet", // isSetIndicatorName
                                null, // constraint
                                false, // isArray
                                null, // arrayLength
                                false, // isPacked
                                false // isImplicit
                        )
                );
        final java.util.List<zserio.runtime.typeinfo.ParameterInfo> parameterList =
                new java.util.ArrayList<zserio.runtime.typeinfo.ParameterInfo>();
        final java.util.List<zserio.runtime.typeinfo.FunctionInfo> functionList =
                new java.util.ArrayList<zserio.runtime.typeinfo.FunctionInfo>();

        return new zserio.runtime.typeinfo.TypeInfo.StructTypeInfo(
                "test_object.CreatorObject", CreatorObject.class, templateName, templateArguments,
                fieldList, parameterList, functionList
        );
    }

    @Override
    public void initPackingContext(zserio.runtime.array.PackingContext context)
    {
        final ZserioPackingContext zserioContext = context.cast();
        zserioContext.getValue().init(new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)),
                new zserio.runtime.array.ArrayElement.LongArrayElement(value_));
        nested_.initPackingContext(zserioContext.getNested());
        if (isOptionalNestedUsed())
        {
            optionalNested_.initPackingContext(zserioContext.getOptionalNested());
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

        endBitPosition += 32;
        endBitPosition += nested_.bitSizeOf(endBitPosition);
        endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfString(text_);
        endBitPosition += nestedArray_.bitSizeOf(endBitPosition);
        endBitPosition += textArray_.bitSizeOf(endBitPosition);
        endBitPosition += 1;
        if (isExternArrayUsed())
        {
            endBitPosition += externArray_.bitSizeOf(endBitPosition);
        }
        endBitPosition += 1;
        if (isBytesArrayUsed())
        {
            endBitPosition += bytesArray_.bitSizeOf(endBitPosition);
        }
        endBitPosition += 1;
        if (isOptionalBoolUsed())
        {
            endBitPosition += 1;
        }
        endBitPosition += 1;
        if (isOptionalNestedUsed())
        {
            endBitPosition += optionalNested_.bitSizeOf(endBitPosition);
        }

        return (int)(endBitPosition - bitPosition);
    }

    @Override
    public int bitSizeOf(zserio.runtime.array.PackingContext context, long bitPosition)
    {
        final ZserioPackingContext zserioContext = context.cast();
        long endBitPosition = bitPosition;

        endBitPosition += zserioContext.getValue().bitSizeOf(new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)),
                new zserio.runtime.array.ArrayElement.LongArrayElement(value_));
        endBitPosition += nested_.bitSizeOf(zserioContext.getNested(), endBitPosition);
        endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfString(text_);
        endBitPosition += nestedArray_.bitSizeOfPacked(endBitPosition);
        endBitPosition += textArray_.bitSizeOf(endBitPosition);
        endBitPosition += 1;
        if (isExternArrayUsed())
        {
            endBitPosition += externArray_.bitSizeOf(endBitPosition);
        }
        endBitPosition += 1;
        if (isBytesArrayUsed())
        {
            endBitPosition += bytesArray_.bitSizeOf(endBitPosition);
        }
        endBitPosition += 1;
        if (isOptionalBoolUsed())
        {
            endBitPosition += 1;
        }
        endBitPosition += 1;
        if (isOptionalNestedUsed())
        {
            endBitPosition += optionalNested_.bitSizeOf(zserioContext.getOptionalNested(), endBitPosition);
        }

        return (int)(endBitPosition - bitPosition);
    }

    public long getValue()
    {
        return value_;
    }

    public void setValue(long value_)
    {
        this.value_ = value_;
    }

    public test_object.CreatorNested getNested()
    {
        return nested_;
    }

    public void setNested(test_object.CreatorNested nested_)
    {
        this.nested_ = nested_;
    }

    public java.lang.String getText()
    {
        return text_;
    }

    public void setText(java.lang.String text_)
    {
        this.text_ = text_;
    }

    public test_object.CreatorNested[] getNestedArray()
    {
        return (nestedArray_ == null) ? null : nestedArray_.getRawArray();
    }

    public void setNestedArray(test_object.CreatorNested[] nestedArray_)
    {
        this.nestedArray_ = new zserio.runtime.array.Array(
                new zserio.runtime.array.RawArray.ObjectRawArray<>(test_object.CreatorNested.class, nestedArray_),
                new zserio.runtime.array.ArrayTraits.WritePackableObjectArrayTraits<test_object.CreatorNested>(new ZserioElementFactory_nestedArray()),
                zserio.runtime.array.ArrayType.AUTO);
    }

    public java.lang.String[] getTextArray()
    {
        return (textArray_ == null) ? null : textArray_.getRawArray();
    }

    public void setTextArray(java.lang.String[] textArray_)
    {
        this.textArray_ = new zserio.runtime.array.Array(
                new zserio.runtime.array.RawArray.StringRawArray(textArray_),
                new zserio.runtime.array.ArrayTraits.StringArrayTraits(),
                zserio.runtime.array.ArrayType.AUTO);
    }

    public zserio.runtime.io.BitBuffer[] getExternArray()
    {
        return (externArray_ == null) ? null : externArray_.getRawArray();
    }

    public void setExternArray(zserio.runtime.io.BitBuffer[] externArray_)
    {
        if (externArray_ == null)
        {
            this.externArray_ = null;
        }
        else
        {
            this.externArray_ = new zserio.runtime.array.Array(
                    new zserio.runtime.array.RawArray.BitBufferRawArray(externArray_),
                    new zserio.runtime.array.ArrayTraits.BitBufferArrayTraits(),
                    zserio.runtime.array.ArrayType.AUTO);
        }
    }

    public boolean isExternArrayUsed()
    {
        return isExternArraySet();
    }

    public boolean isExternArraySet()
    {
        return (externArray_ != null);
    }

    public void resetExternArray()
    {
        this.externArray_ = null;
    }

    public byte[][] getBytesArray()
    {
        return (bytesArray_ == null) ? null : bytesArray_.getRawArray();
    }

    public void setBytesArray(byte[][] bytesArray_)
    {
        if (bytesArray_ == null)
        {
            this.bytesArray_ = null;
        }
        else
        {
            this.bytesArray_ = new zserio.runtime.array.Array(
                    new zserio.runtime.array.RawArray.BytesRawArray(bytesArray_),
                    new zserio.runtime.array.ArrayTraits.BytesArrayTraits(),
                    zserio.runtime.array.ArrayType.AUTO);
        }
    }

    public boolean isBytesArrayUsed()
    {
        return isBytesArraySet();
    }

    public boolean isBytesArraySet()
    {
        return (bytesArray_ != null);
    }

    public void resetBytesArray()
    {
        this.bytesArray_ = null;
    }

    public java.lang.Boolean getOptionalBool()
    {
        return optionalBool_;
    }

    public void setOptionalBool(java.lang.Boolean optionalBool_)
    {
        this.optionalBool_ = optionalBool_;
    }

    public boolean isOptionalBoolUsed()
    {
        return isOptionalBoolSet();
    }

    public boolean isOptionalBoolSet()
    {
        return (optionalBool_ != null);
    }

    public void resetOptionalBool()
    {
        this.optionalBool_ = null;
    }

    public test_object.CreatorNested getOptionalNested()
    {
        return optionalNested_;
    }

    public void setOptionalNested(test_object.CreatorNested optionalNested_)
    {
        this.optionalNested_ = optionalNested_;
    }

    public boolean isOptionalNestedUsed()
    {
        return isOptionalNestedSet();
    }

    public boolean isOptionalNestedSet()
    {
        return (optionalNested_ != null);
    }

    public void resetOptionalNested()
    {
        this.optionalNested_ = null;
    }

    @Override
    public boolean equals(java.lang.Object obj)
    {
        if (obj instanceof CreatorObject)
        {
            final CreatorObject that = (CreatorObject)obj;

            return
                    value_ == that.value_ &&
                    ((nested_ == null) ? that.nested_ == null : nested_.equals(that.nested_)) &&
                    ((text_ == null) ? that.text_ == null : text_.equals(that.text_)) &&
                    ((nestedArray_ == null) ? that.nestedArray_ == null : nestedArray_.equals(that.nestedArray_)) &&
                    ((textArray_ == null) ? that.textArray_ == null : textArray_.equals(that.textArray_)) &&
                    ((!isExternArrayUsed()) ? !that.isExternArrayUsed() :
                        ((externArray_ == null) ? that.externArray_ == null : externArray_.equals(that.externArray_))) &&
                    ((!isBytesArrayUsed()) ? !that.isBytesArrayUsed() :
                        ((bytesArray_ == null) ? that.bytesArray_ == null : bytesArray_.equals(that.bytesArray_))) &&
                    ((!isOptionalBoolUsed()) ? !that.isOptionalBoolUsed() :
                        ((optionalBool_ == null) ? that.optionalBool_ == null : optionalBool_.equals(that.optionalBool_))) &&
                    ((!isOptionalNestedUsed()) ? !that.isOptionalNestedUsed() :
                        ((optionalNested_ == null) ? that.optionalNested_ == null : optionalNested_.equals(that.optionalNested_)));
        }

        return false;
    }

    @Override
    public int hashCode()
    {
        int result = zserio.runtime.HashCodeUtil.HASH_SEED;

        result = zserio.runtime.HashCodeUtil.calcHashCode(result, value_);
        result = zserio.runtime.HashCodeUtil.calcHashCode(result, nested_);
        result = zserio.runtime.HashCodeUtil.calcHashCode(result, text_);
        result = zserio.runtime.HashCodeUtil.calcHashCode(result, nestedArray_);
        result = zserio.runtime.HashCodeUtil.calcHashCode(result, textArray_);
        if (isExternArrayUsed())
            result = zserio.runtime.HashCodeUtil.calcHashCode(result, externArray_);
        if (isBytesArrayUsed())
            result = zserio.runtime.HashCodeUtil.calcHashCode(result, bytesArray_);
        if (isOptionalBoolUsed())
            result = zserio.runtime.HashCodeUtil.calcHashCode(result, optionalBool_);
        if (isOptionalNestedUsed())
            result = zserio.runtime.HashCodeUtil.calcHashCode(result, optionalNested_);

        return result;
    }

    public void read(zserio.runtime.io.BitStreamReader in)
            throws java.io.IOException
    {
        value_ = in.readUnsignedInt();

        nested_ = new test_object.CreatorNested(in, (long)(getValue()));

        text_ = in.readString();

        nestedArray_ = new zserio.runtime.array.Array(
                new zserio.runtime.array.RawArray.ObjectRawArray<>(test_object.CreatorNested.class),
                new zserio.runtime.array.ArrayTraits.WritePackableObjectArrayTraits<test_object.CreatorNested>(new ZserioElementFactory_nestedArray()),
                zserio.runtime.array.ArrayType.AUTO);
        nestedArray_.read(in);

        textArray_ = new zserio.runtime.array.Array(
                new zserio.runtime.array.RawArray.StringRawArray(),
                new zserio.runtime.array.ArrayTraits.StringArrayTraits(),
                zserio.runtime.array.ArrayType.AUTO);
        textArray_.read(in);

        if (in.readBool())
        {
            externArray_ = new zserio.runtime.array.Array(
                    new zserio.runtime.array.RawArray.BitBufferRawArray(),
                    new zserio.runtime.array.ArrayTraits.BitBufferArrayTraits(),
                    zserio.runtime.array.ArrayType.AUTO);
            externArray_.read(in);
        }

        if (in.readBool())
        {
            bytesArray_ = new zserio.runtime.array.Array(
                    new zserio.runtime.array.RawArray.BytesRawArray(),
                    new zserio.runtime.array.ArrayTraits.BytesArrayTraits(),
                    zserio.runtime.array.ArrayType.AUTO);
            bytesArray_.read(in);
        }

        if (in.readBool())
        {
            optionalBool_ = in.readBool();
        }

        if (in.readBool())
        {
            optionalNested_ = new test_object.CreatorNested(in, (long)(getValue()));
        }
    }

    public void read(zserio.runtime.array.PackingContext context, zserio.runtime.io.BitStreamReader in)
            throws java.io.IOException
    {
        final ZserioPackingContext zserioContext = context.cast();
        value_ = ((zserio.runtime.array.ArrayElement.LongArrayElement)
                zserioContext.getValue().read(new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)), in)).get();

        nested_ = new test_object.CreatorNested(zserioContext.getNested(), in, (long)(getValue()));

        text_ = in.readString();

        nestedArray_ = new zserio.runtime.array.Array(
                new zserio.runtime.array.RawArray.ObjectRawArray<>(test_object.CreatorNested.class),
                new zserio.runtime.array.ArrayTraits.WritePackableObjectArrayTraits<test_object.CreatorNested>(new ZserioElementFactory_nestedArray()),
                zserio.runtime.array.ArrayType.AUTO);
        nestedArray_.readPacked(in);

        textArray_ = new zserio.runtime.array.Array(
                new zserio.runtime.array.RawArray.StringRawArray(),
                new zserio.runtime.array.ArrayTraits.StringArrayTraits(),
                zserio.runtime.array.ArrayType.AUTO);
        textArray_.read(in);

        if (in.readBool())
        {
            externArray_ = new zserio.runtime.array.Array(
                    new zserio.runtime.array.RawArray.BitBufferRawArray(),
                    new zserio.runtime.array.ArrayTraits.BitBufferArrayTraits(),
                    zserio.runtime.array.ArrayType.AUTO);
            externArray_.read(in);
        }

        if (in.readBool())
        {
            bytesArray_ = new zserio.runtime.array.Array(
                    new zserio.runtime.array.RawArray.BytesRawArray(),
                    new zserio.runtime.array.ArrayTraits.BytesArrayTraits(),
                    zserio.runtime.array.ArrayType.AUTO);
            bytesArray_.read(in);
        }

        if (in.readBool())
        {
            optionalBool_ = in.readBool();
        }

        if (in.readBool())
        {
            optionalNested_ = new test_object.CreatorNested(zserioContext.getOptionalNested(), in, (long)(getValue()));
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

        endBitPosition += 32;
        endBitPosition = nested_.initializeOffsets(endBitPosition);
        endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfString(text_);
        endBitPosition = nestedArray_.initializeOffsets(endBitPosition);
        endBitPosition = textArray_.initializeOffsets(endBitPosition);
        endBitPosition += 1;
        if (isExternArrayUsed())
        {
            endBitPosition = externArray_.initializeOffsets(endBitPosition);
        }
        endBitPosition += 1;
        if (isBytesArrayUsed())
        {
            endBitPosition = bytesArray_.initializeOffsets(endBitPosition);
        }
        endBitPosition += 1;
        if (isOptionalBoolUsed())
        {
            endBitPosition += 1;
        }
        endBitPosition += 1;
        if (isOptionalNestedUsed())
        {
            endBitPosition = optionalNested_.initializeOffsets(endBitPosition);
        }

        return endBitPosition;
    }

    @Override
    public long initializeOffsets(zserio.runtime.array.PackingContext context, long bitPosition)
    {
        final ZserioPackingContext zserioContext = context.cast();
        long endBitPosition = bitPosition;

        endBitPosition += zserioContext.getValue().bitSizeOf(new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)),
                new zserio.runtime.array.ArrayElement.LongArrayElement(value_));
        endBitPosition = nested_.initializeOffsets(zserioContext.getNested(), endBitPosition);
        endBitPosition += zserio.runtime.BitSizeOfCalculator.getBitSizeOfString(text_);
        endBitPosition = nestedArray_.initializeOffsetsPacked(endBitPosition);
        endBitPosition = textArray_.initializeOffsets(endBitPosition);
        endBitPosition += 1;
        if (isExternArrayUsed())
        {
            endBitPosition = externArray_.initializeOffsets(endBitPosition);
        }
        endBitPosition += 1;
        if (isBytesArrayUsed())
        {
            endBitPosition = bytesArray_.initializeOffsets(endBitPosition);
        }
        endBitPosition += 1;
        if (isOptionalBoolUsed())
        {
            endBitPosition += 1;
        }
        endBitPosition += 1;
        if (isOptionalNestedUsed())
        {
            endBitPosition = optionalNested_.initializeOffsets(zserioContext.getOptionalNested(), endBitPosition);
        }

        return endBitPosition;
    }

    @Override
    public void write(zserio.runtime.io.BitStreamWriter out) throws java.io.IOException
    {
        out.writeUnsignedInt(value_);

        // check parameters
        if (nested_.getParam() != (long)(getValue()))
        {
            throw new zserio.runtime.ZserioError("Write: Wrong parameter param for field CreatorObject.nested: " +
                    nested_.getParam() + " != " + (long)(getValue()) + "!");
        }
        nested_.write(out);

        out.writeString(text_);

        nestedArray_.write(out);

        textArray_.write(out);

        if (isExternArrayUsed())
        {
            out.writeBool(true);
            externArray_.write(out);
        }
        else
        {
            out.writeBool(false);
        }

        if (isBytesArrayUsed())
        {
            out.writeBool(true);
            bytesArray_.write(out);
        }
        else
        {
            out.writeBool(false);
        }

        if (isOptionalBoolUsed())
        {
            out.writeBool(true);
            out.writeBool(optionalBool_);
        }
        else
        {
            out.writeBool(false);
        }

        if (isOptionalNestedUsed())
        {
            out.writeBool(true);
            // check parameters
            if (optionalNested_.getParam() != (long)(getValue()))
            {
                throw new zserio.runtime.ZserioError("Write: Wrong parameter param for field CreatorObject.optionalNested: " +
                        optionalNested_.getParam() + " != " + (long)(getValue()) + "!");
            }
            optionalNested_.write(out);
        }
        else
        {
            out.writeBool(false);
        }
    }

    @Override
    public void write(zserio.runtime.array.PackingContext context, zserio.runtime.io.BitStreamWriter out)
            throws java.io.IOException
    {
        final ZserioPackingContext zserioContext = context.cast();
        zserioContext.getValue().write(new zserio.runtime.array.ArrayTraits.BitFieldLongArrayTraits((int)(32)), out,
                new zserio.runtime.array.ArrayElement.LongArrayElement(value_));

        nested_.write(zserioContext.getNested(), out);

        out.writeString(text_);

        nestedArray_.writePacked(out);

        textArray_.write(out);

        if (isExternArrayUsed())
        {
            out.writeBool(true);
            externArray_.write(out);
        }
        else
        {
            out.writeBool(false);
        }

        if (isBytesArrayUsed())
        {
            out.writeBool(true);
            bytesArray_.write(out);
        }
        else
        {
            out.writeBool(false);
        }

        if (isOptionalBoolUsed())
        {
            out.writeBool(true);
            out.writeBool(optionalBool_);
        }
        else
        {
            out.writeBool(false);
        }

        if (isOptionalNestedUsed())
        {
            out.writeBool(true);
            optionalNested_.write(zserioContext.getOptionalNested(), out);
        }
        else
        {
            out.writeBool(false);
        }
    }

    private final class ZserioElementFactory_nestedArray implements zserio.runtime.array.PackableElementFactory<test_object.CreatorNested>
    {
        @Override
        public test_object.CreatorNested create(zserio.runtime.io.BitStreamReader in, int index)
                throws java.io.IOException
        {
            return new test_object.CreatorNested(in, (long)(getValue()));
        }

        @Override
        public zserio.runtime.array.PackingContext createPackingContext()
        {
            return new test_object.CreatorNested.ZserioPackingContext();
        }

        @Override
        public test_object.CreatorNested create(zserio.runtime.array.PackingContext context,
                zserio.runtime.io.BitStreamReader in, int index) throws java.io.IOException
        {
            return new test_object.CreatorNested(context, in, (long)(getValue()));
        }
    }

    private long value_;
    private test_object.CreatorNested nested_;
    private java.lang.String text_;
    private zserio.runtime.array.Array nestedArray_;
    private zserio.runtime.array.Array textArray_;
    private zserio.runtime.array.Array externArray_;
    private zserio.runtime.array.Array bytesArray_;
    private java.lang.Boolean optionalBool_;
    private test_object.CreatorNested optionalNested_;
}
