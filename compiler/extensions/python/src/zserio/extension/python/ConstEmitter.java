package zserio.extension.python;

import zserio.ast.Constant;
import zserio.extension.common.OutputFileManager;
import zserio.extension.common.PackedTypesCollector;
import zserio.extension.common.ZserioExtensionException;

/**
 * Emitter for constants.
 */
final class ConstEmitter extends PythonDefaultEmitter
{
    public ConstEmitter(OutputFileManager outputFileManager, PythonExtensionParameters pythonParameters,
            PackedTypesCollector packedTypesCollector)
    {
        super(outputFileManager, pythonParameters, packedTypesCollector);
    }

    @Override
    public void beginConst(Constant constant) throws ZserioExtensionException
    {
        final ConstEmitterTemplateData templateData =
                new ConstEmitterTemplateData(getTemplateDataContext(), constant);
        processSourceTemplate(TEMPLATE_SOURCE_NAME, templateData, constant);
    }

    private static final String TEMPLATE_SOURCE_NAME = "Constant.py.ftl";
}
