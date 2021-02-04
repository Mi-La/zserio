package zserio.extension.java;

import zserio.ast.ServiceType;
import zserio.extension.common.ZserioExtensionException;

class ServiceEmitter extends JavaDefaultEmitter
{
    public ServiceEmitter(JavaExtensionParameters javaParameters)
    {
        super(javaParameters);
    }

    @Override
    public void beginService(ServiceType serviceType) throws ZserioExtensionException
    {
        if (!getWithServiceCode())
            return;

        final ServiceEmitterTemplateData templateData = new ServiceEmitterTemplateData(
                getTemplateDataContext(), serviceType);
        processTemplate(TEMPLATE_NAME, templateData, serviceType);
    }

    private static final String TEMPLATE_NAME = "Service.java.ftl";
}
