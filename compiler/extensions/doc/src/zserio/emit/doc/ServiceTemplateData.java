package zserio.emit.doc;

import java.util.ArrayList;
import java.util.List;

import zserio.ast.ServiceMethod;
import zserio.ast.ServiceType;
import zserio.emit.common.ZserioEmitException;

public class ServiceTemplateData
{
    public ServiceTemplateData(TemplateDataContext context, ServiceType serviceType) throws ZserioEmitException
    {
        name = serviceType.getName();
        packageName = serviceType.getPackage().getPackageName().toString();
        linkedType = new LinkedType(serviceType);
        ResourceManager.getInstance().setCurrentOutputDir(
                DocEmitterTools.getDirectoryNameFromType(serviceType));
        docComment = new DocCommentTemplateData(serviceType.getDocComment());
        for (ServiceMethod method : serviceType.getMethodList())
        {
            methodList.add(new MethodTemplateData(method));
        }
        collaborationDiagramSvgFileName = context.getWithSvgDiagrams()
                ? DocEmitterTools.getTypeCollaborationSvgUrl(context.getOutputPath(), serviceType) : null;
    }

    public String getName()
    {
        return name;
    }

    public String getPackageName()
    {
        return packageName;
    }

    public LinkedType getLinkedType()
    {
        return linkedType;
    }

    public DocCommentTemplateData getDocComment()
    {
        return docComment;
    }

    public Iterable<MethodTemplateData> getMethodList()
    {
        return methodList;
    }

    public String getCollaborationDiagramSvgFileName()
    {
        return collaborationDiagramSvgFileName;
    }

    public static class MethodTemplateData
    {
        public MethodTemplateData(ServiceMethod serviceMethod) throws ZserioEmitException
        {
            name = serviceMethod.getName();
            requestType = new LinkedType(serviceMethod.getRequestType());
            responseType = new LinkedType(serviceMethod.getResponseType());
            docComment = new DocCommentTemplateData(serviceMethod.getDocComment());
        }

        public String getName()
        {
            return name;
        }

        public LinkedType getRequestType()
        {
            return requestType;
        }

        public LinkedType getResponseType()
        {
            return responseType;
        }

        public DocCommentTemplateData getDocComment()
        {
            return docComment;
        }

        private final String name;
        private final LinkedType requestType;
        private final LinkedType responseType;
        private final DocCommentTemplateData docComment;
    }

    private final String name;
    private final String packageName;
    private final LinkedType linkedType;
    private final DocCommentTemplateData docComment;
    private final List<MethodTemplateData> methodList = new ArrayList<MethodTemplateData>();
    private final String collaborationDiagramSvgFileName;
}