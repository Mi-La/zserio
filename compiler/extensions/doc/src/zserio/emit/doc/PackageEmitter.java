package zserio.emit.doc;

import java.io.File;
import java.io.PrintWriter;

import zserio.ast.BitmaskType;
import zserio.ast.ChoiceType;
import zserio.ast.Constant;
import zserio.ast.EnumType;
import zserio.ast.Package;
import zserio.ast.PubsubType;
import zserio.ast.ServiceType;
import zserio.ast.SqlDatabaseType;
import zserio.ast.SqlTableType;
import zserio.ast.StructureType;
import zserio.ast.Subtype;
import zserio.ast.UnionType;
import zserio.emit.common.FileUtil;
import zserio.emit.common.ZserioEmitException;
import zserio.tools.Parameters;

public class PackageEmitter extends HtmlDefaultEmitter
{
    public PackageEmitter(String outputPathName, Parameters extensionParameters, boolean withSvgDiagrams,
            UsedByCollector usedByCollector)
    {
        super(extensionParameters, withSvgDiagrams, usedByCollector);

        this.outputPathName = outputPathName;
        this.context = new TemplateDataContext(outputPathName, withSvgDiagrams, usedByCollector);
    }

    @Override
    public void beginPackage(Package pkg) throws ZserioEmitException
    {
        final File outputDirectory = new File(outputPathName, PACKAGE_HTML_DIRECTORY);
        ResourceManager.getInstance().setCurrentOutputDir(outputDirectory.toString());

        final File outputFile = new File(outputDirectory,
                pkg.getPackageName().toString() + HTML_FILE_EXTENSION);
        FileUtil.createOutputDirectory(outputFile);
        writer = FileUtil.createWriter(outputFile);

        final BeginPackageTemplateData templateData = new BeginPackageTemplateData(pkg);
        processHtmlTemplate("begin_package.html.ftl", templateData, writer);
    }

    @Override
    public void endPackage(Package pkg) throws ZserioEmitException
    {
        processHtmlTemplate("end_package.html.ftl", null, writer);
        writer.close();
    }

    @Override
    public void beginConst(Constant constant) throws ZserioEmitException
    {
        final ConstantTemplateData templateData = new ConstantTemplateData(context, constant);
        processHtmlTemplate("constant.html.ftl", templateData, writer);
    }

    @Override
    public void beginSubtype(Subtype subtype) throws ZserioEmitException
    {
        final SubtypeTemplateData templateData = new SubtypeTemplateData(context, subtype);
        processHtmlTemplate("subtype.html.ftl", templateData, writer);
    }

    @Override
    public void beginEnumeration(EnumType enumType) throws ZserioEmitException
    {
        final EnumerationTemplateData templateData = new EnumerationTemplateData(context, enumType);
        processHtmlTemplate("enumeration.html.ftl", templateData, writer);
    }

    @Override
    public void beginBitmask(BitmaskType bitmaskType) throws ZserioEmitException
    {
        final BitmaskTemplateData templateData = new BitmaskTemplateData(context, bitmaskType);
        processHtmlTemplate("bitmask.html.ftl", templateData, writer);
    }

    @Override
    public void beginStructure(StructureType structureType) throws ZserioEmitException
    {
        final CompoundTypeTemplateData templateData = new CompoundTypeTemplateData(context, structureType);
        processHtmlTemplate("structure.html.ftl", templateData, writer);
    }

    @Override
    public void beginUnion(UnionType unionType) throws ZserioEmitException
    {
        final CompoundTypeTemplateData templateData = new CompoundTypeTemplateData(context, unionType);
        processHtmlTemplate("union.html.ftl", templateData, writer);
    }

    @Override
    public void beginChoice(ChoiceType choiceType) throws ZserioEmitException
    {
        final ChoiceTemplateData templateData = new ChoiceTemplateData(context, choiceType);
        processHtmlTemplate("choice.html.ftl", templateData, writer);
    }

    @Override
    public void beginSqlDatabase(SqlDatabaseType sqlDatabaseType) throws ZserioEmitException
    {
        final CompoundTypeTemplateData templateData = new CompoundTypeTemplateData(context, sqlDatabaseType);
        processHtmlTemplate("sql_database.html.ftl", templateData, writer);
    }

    @Override
    public void beginSqlTable(SqlTableType sqlTableType) throws ZserioEmitException
    {
        final SqlTableTemplateData templateData = new SqlTableTemplateData(context, sqlTableType);
        processHtmlTemplate("sql_table.html.ftl", templateData, writer);
    }

    @Override
    public void beginService(ServiceType serviceType) throws ZserioEmitException
    {
        final ServiceTemplateData templateData = new ServiceTemplateData(context, serviceType);
        processHtmlTemplate("service.html.ftl", templateData, writer);
    }

    @Override
    public void beginPubsub(PubsubType pubsubType) throws ZserioEmitException
    {
        final PubsubTemplateData templateData = new PubsubTemplateData(context, pubsubType);
        processHtmlTemplate("pubsub.html.ftl", templateData, writer);
    }

    private static final String PACKAGE_HTML_DIRECTORY = "content";

    private final String outputPathName;
    private final TemplateDataContext context;

    private PrintWriter writer = null;
}
