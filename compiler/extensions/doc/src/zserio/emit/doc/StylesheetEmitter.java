package zserio.emit.doc;

import java.io.File;

import zserio.emit.common.FreeMarkerUtil;
import zserio.emit.common.ZserioEmitException;

/**
 * Emits CSS styles file.
 */
class StylesheetEmitter
{
    static void emit(String outputPathName) throws ZserioEmitException
    {
        final File outputDirectory = new File(outputPathName, DocDefaultEmitter.CSS_DIRECTORY);
        processTemplate(STYLESHEET_TEMPLATE_SOURCE_NAME, new File(outputDirectory, STYLESHEET_FILE_NAME));
    }

    static void processTemplate(String templateName, File outputFile) throws ZserioEmitException
    {
        FreeMarkerUtil.processTemplate(DotDefaultEmitter.DOC_TEMPLATE_LOCATION + templateName, null, outputFile,
                false);
    }

    static final String STYLESHEET_FILE_NAME = "stylesheet.css";

    private static final String STYLESHEET_TEMPLATE_SOURCE_NAME = "stylesheet.css.ftl";
}