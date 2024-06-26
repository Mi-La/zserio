package zserio.ast;

import java.util.List;

/**
 * AST node for explicit template instantiation.
 */
public final class InstantiateType extends DocumentableAstNode implements ZserioType
{
    /**
     * Constructor.
     *
     * @param location      AST node location.
     * @param pkg           Package to which belongs the instantiation.
     * @param typeReference Reference to a template instantiation.
     * @param name          Name to be assigned to the instantiated template.
     * @param docComments   List of documentation comments belonging to this node.
     */
    public InstantiateType(AstLocation location, Package pkg, TypeReference typeReference, String name,
            List<DocComment> docComments)
    {
        super(location, docComments);

        this.pkg = pkg;
        this.typeReference = typeReference;
        this.name = name;
    }

    @Override
    public void accept(ZserioAstVisitor visitor)
    {
        visitor.visitInstantiateType(this);
    }

    @Override
    public void visitChildren(ZserioAstVisitor visitor)
    {
        typeReference.accept(visitor);
    }

    @Override
    public Package getPackage()
    {
        return pkg;
    }

    @Override
    public String getName()
    {
        return name;
    }

    /**
     * Gets reference to the template instantiation.
     *
     * @return Type reference.
     */
    public TypeReference getTypeReference()
    {
        return typeReference;
    }

    /**
     * Resolves the instantiate type.
     */
    void resolve()
    {
        if (isResolved)
            return;

        // don't use base type reference since instantiate type can be defined only for a template instantiation
        final ZserioType type = typeReference.getType();
        if (!(type instanceof TemplatableType) || ((TemplatableType)type).getTemplateParameters().isEmpty())
        {
            throw new ParserException(
                    type, "'" + ZserioTypeUtil.getReferencedFullName(typeReference) + "' is not a template!");
        }

        template = (TemplatableType)type;
        isResolved = true;
    }

    /**
     * Gets template which will be instantiated.
     *
     * @return Templatable type.
     */
    TemplatableType getTemplate()
    {
        return template;
    }

    private final Package pkg;
    private final TypeReference typeReference;
    private final String name;

    private TemplatableType template = null;
    private boolean isResolved = false;
}
