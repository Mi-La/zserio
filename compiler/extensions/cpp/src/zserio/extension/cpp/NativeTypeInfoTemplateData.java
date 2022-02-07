package zserio.extension.cpp;

import zserio.ast.ArrayType;
import zserio.ast.BitmaskType;
import zserio.ast.BooleanType;
import zserio.ast.CompoundType;
import zserio.ast.EnumType;
import zserio.ast.TypeInstantiation;
import zserio.ast.TypeReference;
import zserio.ast.ZserioType;
import zserio.extension.common.ZserioExtensionException;
import zserio.extension.cpp.types.CppNativeArrayableType;
import zserio.extension.cpp.types.CppNativeType;

/**
 * FreeMarker template data with info about types.
 */
public class NativeTypeInfoTemplateData
{
    public NativeTypeInfoTemplateData(CppNativeType cppNativeType, TypeInstantiation typeInstantiation)
            throws ZserioExtensionException
    {
        this(cppNativeType, typeInstantiation.getTypeReference().getBaseTypeReference().getType(),
                typeInstantiation, null);
    }

    public NativeTypeInfoTemplateData(CppNativeType cppNativeType, TypeReference typeReference)
            throws ZserioExtensionException
    {
        this(cppNativeType, typeReference.getBaseTypeReference().getType(), null, typeReference);
    }

    public NativeTypeInfoTemplateData(CppNativeType cppNativeType, ZserioType baseType)
            throws ZserioExtensionException
    {
        this(cppNativeType, baseType, null, null);
    }

    public String getTypeFullName()
    {
        return typeFullName;
    }

    public boolean getIsSimple()
    {
        return isSimple;
    }

    public boolean getIsEnum()
    {
        return isEnum;
    }

    public boolean getIsBitmask()
    {
        return isBitmask;
    }

    public boolean getIsBoolean()
    {
        return isBoolean;
    }

    public ArrayTraitsTemplateData getArrayTraits()
    {
        return arrayTraits;
    }

    public RuntimeFunctionTemplateData getTypeInfoGetter()
    {
        return typeInfoGetter;
    }

    private NativeTypeInfoTemplateData(CppNativeType cppNativeType, ZserioType baseType,
            TypeInstantiation typeInstantiation, TypeReference typeReference) throws ZserioExtensionException
    {
        typeFullName = cppNativeType.getFullName();
        isSimple = cppNativeType.isSimple();

        // we suppose that zserio enum, bitmask, etc. are mapped to C++ native enum, bitmask, etc.
        // normally, we should consult native type here (in this case we should solve subtypes as well)
        isEnum = baseType instanceof EnumType;
        isBitmask = baseType instanceof BitmaskType;
        isBoolean = baseType instanceof BooleanType;

        if (cppNativeType instanceof CppNativeArrayableType)
            arrayTraits = new ArrayTraitsTemplateData(((CppNativeArrayableType)cppNativeType).getArrayTraits());
        else
            arrayTraits = null;

        final boolean isCompound = baseType instanceof CompoundType;
        final boolean isArray = baseType instanceof ArrayType;
        final boolean hasTypeInfo = isCompound || isEnum || isBitmask || isArray;
        if (hasTypeInfo || (typeInstantiation == null && typeReference == null))
        {
            typeInfoGetter = null;
        }
        else
        {
            typeInfoGetter = (typeInstantiation != null) ?
                    CppRuntimeFunctionDataCreator.createTypeInfoData(typeInstantiation) :
                    CppRuntimeFunctionDataCreator.createTypeInfoData(typeReference);
        }
    }

    private final String typeFullName;
    private final boolean isSimple;
    private final boolean isEnum;
    private final boolean isBitmask;
    private final boolean isBoolean;
    private final ArrayTraitsTemplateData arrayTraits;
    private final RuntimeFunctionTemplateData typeInfoGetter;
}