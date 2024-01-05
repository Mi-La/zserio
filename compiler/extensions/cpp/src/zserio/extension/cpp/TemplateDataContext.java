package zserio.extension.cpp;

import zserio.extension.common.ExpressionFormatter;
import zserio.extension.common.ExpressionFormattingPolicy;
import zserio.extension.common.PackedTypesCollector;

/**
 * FreeMarker template data context for all emitters.
 *
 * Holds all parameters used by FreeMarker template data.
 */
final class TemplateDataContext
{
    public TemplateDataContext(CppExtensionParameters cppParameters, PackedTypesCollector packedTypesCollector)
    {
        this.packedTypesCollector = packedTypesCollector;

        typesContext = new TypesContext(cppParameters.getAllocatorDefinition());
        cppNativeMapper = new CppNativeMapper(typesContext);

        withWriterCode = cppParameters.getWithWriterCode();
        withRangeCheckCode = cppParameters.getWithRangeCheckCode();
        withValidationCode = cppParameters.getWithValidationCode();
        withTypeInfoCode = cppParameters.getWithTypeInfoCode();
        withReflectionCode = cppParameters.getWithReflectionCode();
        withCodeComments = cppParameters.getWithCodeComments();

        generatorDescription = "/**\n"
                + " * Automatically generated by Zserio C++ generator version " +
                CppExtensionVersion.CPP_EXTENSION_VERSION_STRING + " using Zserio core " +
                cppParameters.getZserioVersion() + ".\n"
                + " * Generator setup: " + cppParameters.getParametersDescription() + ".\n"
                + " */";
        generatorVersionString = CppExtensionVersion.CPP_EXTENSION_VERSION_STRING;
        generatorVersionNumber = CppExtensionVersion.CPP_EXTENSION_VERSION_NUMBER;
    }

    public PackedTypesCollector getPackedTypesCollector()
    {
        return packedTypesCollector;
    }

    public CppNativeMapper getCppNativeMapper()
    {
        return cppNativeMapper;
    }

    public ExpressionFormatter getExpressionFormatter(IncludeCollector includeCollector)
    {
        final ExpressionFormattingPolicy expressionFormattingPolicy =
                new CppExpressionFormattingPolicy(cppNativeMapper, includeCollector);

        return new ExpressionFormatter(expressionFormattingPolicy);
    }

    public ExpressionFormatter getIndirectExpressionFormatter(
            IncludeCollector includeCollector, String compoundTypeAccessPrefix)
    {
        final ExpressionFormattingPolicy expressionFormattingPolicy = new CppIndirectExpressionFormattingPolicy(
                cppNativeMapper, includeCollector, compoundTypeAccessPrefix);

        return new ExpressionFormatter(expressionFormattingPolicy);
    }

    public boolean getWithWriterCode()
    {
        return withWriterCode;
    }

    public boolean getWithRangeCheckCode()
    {
        return withRangeCheckCode;
    }

    public boolean getWithTypeInfoCode()
    {
        return withTypeInfoCode;
    }

    public boolean getWithReflectionCode()
    {
        return withReflectionCode;
    }

    public boolean getWithValidationCode()
    {
        return withValidationCode;
    }

    public boolean getWithCodeComments()
    {
        return withCodeComments;
    }

    public TypesContext getTypesContext()
    {
        return typesContext;
    }

    public String getGeneratorDescription()
    {
        return generatorDescription;
    }

    public String getGeneratorVersionString()
    {
        return generatorVersionString;
    }

    public long getGeneratorVersionNumber()
    {
        return generatorVersionNumber;
    }

    private final PackedTypesCollector packedTypesCollector;

    private final TypesContext typesContext;

    private final CppNativeMapper cppNativeMapper;

    private final boolean withWriterCode;
    private final boolean withRangeCheckCode;
    private final boolean withValidationCode;
    private final boolean withTypeInfoCode;
    private final boolean withReflectionCode;
    private final boolean withCodeComments;
    private final String generatorDescription;
    private final String generatorVersionString;
    private final long generatorVersionNumber;
}
