package zserio.ast;

import zserio.tools.ZserioVersion;

/**
 * AST node for compatibility version.
 */
public class CompatibilityVersion extends AstNodeBase
{
    /**
     * Constructor.
     *
     * @param location AST node location.
     * @param versionStringLiteral Version string literal (including quotes!).
     */
    public CompatibilityVersion(AstLocation location, String versionStringLiteral)
    {
        super(location);

        try
        {
            this.version = Version.parseVersion(
                    versionStringLiteral.substring(1, versionStringLiteral.length() - 1)); // strip quotes
        }
        catch (RuntimeException e)
        {
            throw new ParserException(location, e.getMessage());
        }

        if (version.compareTo(CURRENT_ZSERIO_VERSION) > 0)
        {
            throw new ParserException(location,
                    "Root package specifies compatibility version '" + version + "' " +
                    "which is higher than current zserio version '" + CURRENT_ZSERIO_VERSION + "'!");
        }

        if (version.compareTo(MINIMUM_SUPPORTED_VERSION) < 0)
        {
            throw new ParserException(location,
                    "Root package specifies unsupported compatibility version '" + version +
                    "', minimum supported version is '" + MINIMUM_SUPPORTED_VERSION + "'!");
        }
    }

    @Override
    public void accept(ZserioAstVisitor visitor)
    {
        visitor.visitCompatibilityVersion(this);
    }

    /**
     * Gets parsed version.
     *
     * @return Version.
     */
    public Version getVersion()
    {
        return version;
    }

    private static final Version CURRENT_ZSERIO_VERSION = Version.parseVersion(ZserioVersion.VERSION_STRING);
    private static final Version MINIMUM_SUPPORTED_VERSION = new Version(2, 4, 0);

    private final Version version;
}
