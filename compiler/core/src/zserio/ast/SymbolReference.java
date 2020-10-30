package zserio.ast;

/**
 * The class represents symbol reference.
 *
 * Symbol reference can be for example
 *
 * - reference to constant ('packageName.FooConstant')
 * - reference to enumeration item ('packageName.FooEnumeration.BAR_ENUM_ITEM')
 * - reference to compound field ('packageName.FooCompoundType.field')
 *
 * Symbol reference is not AST node because it is used by unparsed texts in the following situation:
 *
 * - documentation comment tag see token (@see)
 */
public class SymbolReference
{
    /**
     * Constructor from owner token and text.
     *
     * @param ownerNode           AST token which owns the symbol reference test.
     * @param symbolReferenceText Symbol reference in unparsed text format.
     */
    public SymbolReference(AstNode ownerNode, String symbolReferenceText)
    {
        this.ownerNode = ownerNode;

        final String[] referenceElementList = symbolReferenceText.split("\\" + SYMBOL_REFERENCE_SEPARATOR);
        for (String referenceElement : referenceElementList)
        {
            if (referencedName != null)
                referencedPackageNameBuilder.addId(referencedName);
            referencedName = referenceElement;
        }
    }

    /**
     * Gets referenced package symbol.
     *
     * @return Referenced package symbol.
     */
    public PackageSymbol getReferencedPackageSymbol()
    {
        return referencedPackageSymbol;
    }

    /**
     * Gets referenced scope symbol.
     *
     * @return Referenced scope symbol or null if the reference is a package symbol.
     */
    public ScopeSymbol getReferencedScopeSymbol()
    {
        return referencedScopeSymbol;
    }

    /**
     * Resolves the symbol reference.
     *
     * @param ownerPackage Zserio package in which the symbol reference is defined.
     * @param ownerType ZserioType which is owner of the symbol reference.
     */
    void resolve(Package ownerPackage, ZserioScopedType ownerType)
    {
        // try if the last link component was a package symbol
        PackageName referencedPackageName = getReferencedPackageName(ownerPackage);
        referencedPackageSymbol = ownerPackage.getVisibleSymbol(ownerNode, referencedPackageName,
                referencedName);
        if (referencedPackageSymbol == null)
        {
            // try if the last link component was not a package symbol (can be a field name or enumeration item)
            final String referencedScopeSymbolName = referencedName;
            referencedName = referencedPackageNameBuilder.removeLastId();
            if (referencedName == null)
            {
                // there is only symbol name, try to resolve it in owner scope
                referencedPackageSymbol = ownerType;
            }
            else
            {
                referencedPackageName = getReferencedPackageName(ownerPackage);
                referencedPackageSymbol = ownerPackage.getVisibleSymbol(ownerNode, referencedPackageName,
                        referencedName);

                // this was our last attempt to resolve symbol type
                if (!(referencedPackageSymbol instanceof ZserioScopedType))
                {
                    throw new ParserException(ownerNode, "Unresolved referenced symbol '" +
                            ZserioTypeUtil.getFullName(referencedPackageName, referencedName) + "'!");
                }
            }

            final Scope referencedScope = ((ZserioScopedType)referencedPackageSymbol).getScope();
            referencedScopeSymbol = referencedScope.getSymbol(referencedScopeSymbolName);
            if (referencedScopeSymbol == null)
            {
                throw new ParserException(ownerNode, "Unresolved referenced symbol '" +
                        referencedScopeSymbolName + "' for type '" + referencedPackageSymbol.getName() + "'!");
            }
        }
    }

    private PackageName getReferencedPackageName(Package ownerPackage)
    {
        final PackageName referencedPackageName = referencedPackageNameBuilder.get();
        if (referencedPackageName.isEmpty())
            return referencedPackageName;

        final PackageName.Builder packageNameBuilder = new PackageName.Builder();
        packageNameBuilder.append(ownerPackage.getTopLevelPackageName());
        packageNameBuilder.append(referencedPackageName);

        return packageNameBuilder.get();
    }

    private static final String SYMBOL_REFERENCE_SEPARATOR = ".";

    private final AstNode ownerNode;
    private final PackageName.Builder referencedPackageNameBuilder = new PackageName.Builder();

    private String referencedName = null;
    private PackageSymbol referencedPackageSymbol = null;
    private ScopeSymbol referencedScopeSymbol = null;
}
