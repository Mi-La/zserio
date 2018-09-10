package zserio.ast;

import java.util.ArrayList;
import java.util.List;
import java.util.SortedSet;
import java.util.TreeSet;

import zserio.antlr.ZserioParserTokenTypes;
import zserio.antlr.util.BaseTokenAST;
import zserio.antlr.util.ParserException;
import zserio.ast.doc.DocCommentToken;

/**
 * AST node for subtypes.
 *
 * Subtypes are Zserio types as well.
 */
public class Subtype extends TokenAST implements ZserioType
{
    /**
     * Default constructor.
     */
    public Subtype()
    {
        usedByConstList = new ArrayList<ConstType>();
        usedByCompoundList = new TreeSet<CompoundType>();
        usedByServiceList = new TreeSet<ServiceType>();
        usedTypeList = new ArrayList<ZserioType>();
        ZserioTypeContainer.add(this);
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

    @Override
    public Iterable<ZserioType> getUsedTypeList()
    {
        return usedTypeList;
    }

    @Override
    public void callVisitor(ZserioTypeVisitor visitor)
    {
        visitor.visitSubtype(this);
    }

    /**
     * Sets package for the subtype.
     *
     * This method is called by code generated by ANTLR using TypeEvaluator.g.
     *
     * @param pkg Package to set.
     */
    public void setPackage(Package pkg)
    {
        this.pkg = pkg;
    }

    /**
     * Sets const type which uses this subtype.
     *
     * @param usedByConst Const type to set.
     */
    public void setUsedByConst(ConstType usedByConst)
    {
        usedByConstList.add(usedByConst);
    }

    /**
     * Sets compound type which uses this subtype.
     *
     * @param usedByCompound Compound type to set.
     */
    public void setUsedByCompound(CompoundType usedByCompound)
    {
        usedByCompoundList.add(usedByCompound);
    }

    /**
     * Sets service type which uses this compound type.
     *
     * @param serviceType Service type to set.
     */
    public void setUsedByServiceType(ServiceType serviceType)
    {
        usedByServiceList.add(serviceType);
    }

    /**
     * Gets the target type.
     *
     * @return Type referenced by this subtype.
     */
    public ZserioType getTargetType()
    {
        return targetType;
    }

    /**
     * Gets target base type.
     *
     * @return Resolved base type of the target type.
     */
    public ZserioType getTargetBaseType()
    {
        return targetBaseType;
    }

    /**
     * Gets list of const types which use this subtype.
     *
     * @return List of const types which use this subtype.
     */
    public Iterable<ConstType> getUsedByConstList()
    {
        return usedByConstList;
    }

    /**
     * Gets list of compound types which use this subtype.
     *
     * @return List of compound types which use this subtype.
     */
    public Iterable<CompoundType> getUsedByCompoundList()
    {
        return usedByCompoundList;
    }

    /**
     * Gets list of service types which use this compound type.
     *
     * @return List of service types using this compound type.
     */
    public Iterable<ServiceType> getUsedByServiceList()
    {
        return usedByServiceList;
    }

    /**
     * Gets documentation comment associated to this constant type.
     *
     * @return Documentation comment token associated to this constant type.
     */
    public DocCommentToken getDocComment()
    {
        return getHiddenDocComment();
    }

    @Override
    protected boolean evaluateChild(BaseTokenAST child) throws ParserException
    {
        switch (child.getType())
        {
        case ZserioParserTokenTypes.ID:
            name = child.getText();
            break;

        default:
            if (targetType != null || !(child instanceof ZserioType))
                return false;
            targetType = (ZserioType)child;
            break;
        }

        return true;
    }

    @Override
    protected void evaluate() throws ParserException
    {
        evaluateHiddenDocComment(this);
    }

    @Override
    protected void check() throws ParserException
    {
        // fill used type list
        final ZserioType resolvedTypeReference = TypeReference.resolveType(targetType);
        if (!ZserioTypeUtil.isBuiltIn(resolvedTypeReference))
            usedTypeList.add(resolvedTypeReference);
    }

    /**
     * Resolves the subtype to a defined type.
     * Called at the end of linking phase.
     *
     * @return Resolved base type of this subtype.
     *
     * @throws ParserException When cyclic definition is detected.
     */
    protected ZserioType resolve() throws ParserException
    {
        if (resolvingState == ResolvingState.RESOLVED)
            return targetBaseType;

        // detect cycles in subtype definitions
        if (resolvingState == ResolvingState.RESOLVING)
            throw new ParserException(this, "Cyclic dependency detected in subtype '" +
                    getName() + "' definition!");

        resolvingState = ResolvingState.RESOLVING;

        // base type can be only type reference or a defined type.
        if (targetType instanceof TypeReference)
            targetBaseType = ((TypeReference)targetType).resolve();
        else // built-in type
            targetBaseType = targetType;

        resolvingState = ResolvingState.RESOLVED;

        return targetBaseType;
    }

    private static final long serialVersionUID = -1039702375311967109L;

    private Package pkg;

    private enum ResolvingState
    {
        UNRESOLVED,
        RESOLVING,
        RESOLVED
    };

    private ZserioType targetType;
    private ResolvingState resolvingState = ResolvingState.UNRESOLVED;
    private ZserioType targetBaseType;
    private String name;

    private List<ConstType> usedByConstList;
    private SortedSet<CompoundType> usedByCompoundList;
    private SortedSet<ServiceType> usedByServiceList;
    private List<ZserioType> usedTypeList;
}
