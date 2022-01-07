package zserio.extension.java;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

import zserio.ast.BitmaskType;
import zserio.ast.BitmaskValue;
import zserio.ast.DynamicBitFieldInstantiation;
import zserio.ast.IntegerType;
import zserio.ast.TypeInstantiation;
import zserio.ast.ZserioType;
import zserio.extension.common.ExpressionFormatter;
import zserio.extension.common.ZserioExtensionException;
import zserio.extension.java.types.NativeIntegralType;
import zserio.extension.java.types.NativeLongType;

/**
 * FreeMarker template data for BitmaskEmitter.
 */
public final class BitmaskEmitterTemplateData extends UserTypeTemplateData
{
    public BitmaskEmitterTemplateData(TemplateDataContext context, BitmaskType bitmaskType)
            throws ZserioExtensionException
    {
        super(context, bitmaskType);

        final TypeInstantiation bitmaskTypeInstantiation = bitmaskType.getTypeInstantiation();
        final JavaNativeMapper javaNativeMapper = context.getJavaNativeMapper();
        final ExpressionFormatter javaExpressionFormatter = context.getJavaExpressionFormatter();
        final NativeIntegralType nativeIntegralType =
                javaNativeMapper.getJavaIntegralType(bitmaskTypeInstantiation);
        baseJavaTypeName = nativeIntegralType.getFullName();

        underlyingTypeInfo = new TypeInfoTemplateData(bitmaskTypeInstantiation, nativeIntegralType);

        isLong = nativeIntegralType instanceof NativeLongType;
        isSimpleType = nativeIntegralType.isSimple();

        arrayableInfo = new ArrayableInfoTemplateData(nativeIntegralType);
        bitSize = BitSizeTemplateData.create(bitmaskTypeInstantiation, javaExpressionFormatter);

        runtimeFunction = JavaRuntimeFunctionDataCreator.createData(bitmaskTypeInstantiation,
                javaExpressionFormatter, javaNativeMapper);

        final BigInteger lowerBound = getLowerBound(bitmaskTypeInstantiation);
        this.lowerBound = lowerBound.equals(nativeIntegralType.getLowerBound()) ? null :
                nativeIntegralType.formatLiteral(lowerBound);
        // upper bound is needed for negation since java uses signed types!
        final BigInteger upperBound = getUpperBound(bitmaskTypeInstantiation);
        this.upperBound = nativeIntegralType.formatLiteral(upperBound);
        this.checkUpperBound = !upperBound.equals(nativeIntegralType.getUpperBound());

        values = new ArrayList<BitmaskValueData>();
        for (BitmaskValue bitmaskValue: bitmaskType.getValues())
            values.add(new BitmaskValueData(nativeIntegralType, bitmaskValue));
    }

    public String getBaseJavaTypeName()
    {
        return baseJavaTypeName;
    }

    public TypeInfoTemplateData getUnderlyingTypeInfo()
    {
        return underlyingTypeInfo;
    }

    public boolean getIsSimpleType()
    {
        return isSimpleType;
    }

    public boolean getIsLong()
    {
        return isLong;
    }

    public ArrayableInfoTemplateData getArrayableInfo()
    {
        return arrayableInfo;
    }

    public BitSizeTemplateData getBitSize()
    {
        return bitSize;
    }

    public RuntimeFunctionTemplateData getRuntimeFunction()
    {
        return runtimeFunction;
    }

    public String getLowerBound()
    {
        return lowerBound;
    }

    public String getUpperBound()
    {
        return upperBound;
    }

    public boolean getCheckUpperBound()
    {
        return checkUpperBound;
    }

    public Iterable<BitmaskValueData> getValues()
    {
        return values;
    }

    private static BigInteger getUpperBound(TypeInstantiation typeInstantiation) throws ZserioExtensionException
    {
        final ZserioType baseType = typeInstantiation.getBaseType();

        if (typeInstantiation instanceof DynamicBitFieldInstantiation)
            return ((DynamicBitFieldInstantiation)typeInstantiation).getUpperBound();
        else if (baseType instanceof IntegerType)
            return ((IntegerType)baseType).getUpperBound();
        throw new ZserioExtensionException("Unexpected bitmask type instantiation!");
    }

    private static BigInteger getLowerBound(TypeInstantiation typeInstantiation) throws ZserioExtensionException
    {
        final ZserioType baseType = typeInstantiation.getBaseType();

        if (typeInstantiation instanceof DynamicBitFieldInstantiation)
            return ((DynamicBitFieldInstantiation)typeInstantiation).getLowerBound();
        else if (baseType instanceof IntegerType)
            return ((IntegerType)baseType).getLowerBound();
        throw new ZserioExtensionException("Unexpected bitmask type instantiation!");
    }

    public static class BitmaskValueData
    {
        public BitmaskValueData(NativeIntegralType nativeBaseType, BitmaskValue bitmaskValue)
                throws ZserioExtensionException
        {
            name = bitmaskValue.getName();
            value = nativeBaseType.formatLiteral(bitmaskValue.getValue());
            isZero = bitmaskValue.getValue().equals(BigInteger.ZERO);
        }

        public String getName()
        {
            return name;
        }

        public String getValue()
        {
            return value;
        }

        public boolean getIsZero()
        {
            return isZero;
        }

        private final String name;
        private final String value;
        private final boolean isZero;
    }

    private final String baseJavaTypeName;
    private final TypeInfoTemplateData underlyingTypeInfo;
    private final boolean isSimpleType;
    private final boolean isLong;
    private final ArrayableInfoTemplateData arrayableInfo;
    private final BitSizeTemplateData bitSize;
    private final RuntimeFunctionTemplateData runtimeFunction;
    private final String lowerBound;
    private final String upperBound;
    private final boolean checkUpperBound;
    private final List<BitmaskValueData> values;
}
