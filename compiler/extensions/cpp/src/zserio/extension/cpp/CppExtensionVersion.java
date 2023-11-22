package zserio.extension.cpp;

/**
 * C++ extension version information.
 *
 * C++ extension version will be reported to Zserio core and will be stored in MANIFEST.MF.
 *
 * Expected Zserio core version will be used to check if the extension can be safely loaded.
 */
public class CppExtensionVersion
{
    /** C++ extension version string. */
    public static final String CPP_EXTENSION_VERSION_STRING = "1.0.0";

    /** Expected Zserio core version string. */
    public static final String EXPECTED_ZSERIO_VERSION_STRING = "2.12.0";

    /** C++ extension version in integer value to allow version checking in generated code. */
    public static final long CPP_EXTENSION_VERSION_NUMBER = 1000000;
}
