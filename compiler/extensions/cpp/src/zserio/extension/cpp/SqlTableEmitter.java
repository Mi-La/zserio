package zserio.extension.cpp;

import zserio.ast.SqlTableType;
import zserio.extension.common.ZserioExtensionException;

public class SqlTableEmitter extends CppDefaultEmitter
{
    public SqlTableEmitter(CppExtensionParameters cppParameters)
    {
        super(cppParameters);
    }

    @Override
    public void beginSqlTable(SqlTableType sqlTableType) throws ZserioExtensionException
    {
        if (getWithSqlCode())
        {
            final Object tableTemplateData = new SqlTableEmitterTemplateData(getTemplateDataContext(),
                    sqlTableType);
            processHeaderTemplate(TABLE_TEMPLATE_HEADER_NAME, tableTemplateData, sqlTableType);
            processSourceTemplate(TABLE_TEMPLATE_SOURCE_NAME, tableTemplateData, sqlTableType);
        }
    }

    private static final String TABLE_TEMPLATE_SOURCE_NAME = "SqlTable.cpp.ftl";
    private static final String TABLE_TEMPLATE_HEADER_NAME = "SqlTable.h.ftl";
}
