package zserio.ast;

import java.util.List;

import zserio.tools.ZserioToolPrinter;

/**
 * AST node for array type instantiation.
 */
public class ArrayInstantiation extends TypeInstantiation
{
    /**
     * Constructor.
     *
     * @param location                 AST node location.
     * @param typeReference            Reference to the instantiated type definition.
     * @param elementTypeInstantiation Element type instantiation.
     * @param isPacked                 Whether this array is packed.
     * @param isImplicit               Whether this is an implicit array.
     * @param lengthExpression         Array length expression.
     */
    public ArrayInstantiation(AstLocation location, TypeReference typeReference,
            TypeInstantiation elementTypeInstantiation, boolean isPacked,
            boolean isImplicit, Expression lengthExpression)
    {
        super(location, typeReference);

        this.elementTypeInstantiation = elementTypeInstantiation;
        this.isPacked = isPacked;
        this.isImplicit = isImplicit;
        this.lengthExpression = lengthExpression;
    }

    @Override
    public void visitChildren(ZserioAstVisitor visitor)
    {
        super.visitChildren(visitor);

        elementTypeInstantiation.accept(visitor);
        if (lengthExpression != null)
            lengthExpression.accept(visitor);
    }

    /**
     * Gets type instantiation for array elements.
     *
     * @return Type instantiation.
     */
    public TypeInstantiation getElementTypeInstantiation()
    {
        return elementTypeInstantiation;
    }

    /**
     * Gets whether the array is a packed array.
     *
     * @note Packed arrays can be defined only for integral types or
     *       for structures which contain packable fields.
     *
     * @return True if the array is packed, false otherwise.
     */
    public boolean isPacked()
    {
        return isPacked;
    }

    /**
     * Gets whether the array is an implicit array.
     *
     * \note Implicit arrays have no length expression.
     *
     * @return True if the array is implicit, false otherwise.
     */
    public boolean isImplicit()
    {
        return isImplicit;
    }

    /**
     * Gets length expression.
     *
     * @return Array length expression or null when this is an implicit or auto array.
     */
    public Expression getLengthExpression()
    {
        return lengthExpression;
    }

    @Override
    public ArrayType getBaseType()
    {
        return (ArrayType)super.getBaseType();
    }

    @Override
    ArrayInstantiation instantiateImpl(List<TemplateParameter> templateParameters,
            List<TemplateArgument> templateArguments, TypeReference instantiatedTypeReference)
    {
        final TypeInstantiation instantiatedElementTypeInstantiation =
                elementTypeInstantiation.instantiate(templateParameters, templateArguments);
        final Expression instantiatedLengthExpression = getLengthExpression() == null ? null :
                getLengthExpression().instantiate(templateParameters, templateArguments);

        return new ArrayInstantiation(getLocation(), instantiatedTypeReference,
                instantiatedElementTypeInstantiation, isPacked, isImplicit, instantiatedLengthExpression);
    }

    @Override
    void resolve()
    {
        if (!(super.getBaseType() instanceof ArrayType))
        {
            throw new ParserException(getTypeReference(), "Referenced type '" +
                    ZserioTypeUtil.getReferencedFullName(getTypeReference()) + "' is not an array type!");
        }
    }

    @Override
    void evaluate()
    {
        if (!isEvaluated)
        {
            // expression needs BigInteger but Zserio type must be integer => cast expression to long
            if (lengthExpression != null && lengthExpression.needsBigInteger())
                lengthExpression.setNeedsBigIntegerCastingNative();

            isEvaluated = true;
        }
    }

    @Override
    void check(ZserioTemplatableType currentTemplateInstantiation)
    {
        checkPackedArrayElementType(currentTemplateInstantiation);

        if (!checkImplicitArrayElementType())
        {
            throw new ParserException(elementTypeInstantiation,
                    "Implicit arrays are allowed only for types which have fixed size rounded to bytes!");
        }

        // check length expression
        if (lengthExpression != null)
        {
            if (lengthExpression.getExprType() != Expression.ExpressionType.INTEGER)
            {
                throw new ParserException(lengthExpression,
                        "Invalid length expression for array. Length must be integer!");
            }
        }
    }

    /**
     * Check whether the baseType is packable.
     *
     * @param baseType Base type to check.
     *
     * @return True when the base type is packable, false otherwise.
     */
    static boolean isSimpleTypePackable(ZserioType baseType)
    {
        return baseType instanceof IntegerType ||
                baseType instanceof EnumType || baseType instanceof BitmaskType;
    }

    private void checkPackedArrayElementType(ZserioTemplatableType currentTemplateInstantiation)
    {
        if (isPacked)
        {
            final ZserioType elementBaseType = getElementTypeInstantiation().getBaseType();

            if (elementBaseType instanceof CompoundType)
            {
                if (!((CompoundType)elementBaseType).hasPackableField())
                {
                    printInstantiationWarning(currentTemplateInstantiation,
                            "'" + elementBaseType.getName() + "' doesn't contain any packable field!");
                }
            }
            else if (!(isSimpleTypePackable(elementBaseType)))
            {
                printInstantiationWarning(currentTemplateInstantiation,
                        "'" + elementBaseType.getName() + "' is not packable element type!");
            }
        }
    }

    private void printInstantiationWarning(ZserioTemplatableType currentTemplateInstantiation, String message)
    {
        if (currentTemplateInstantiation != null)
        {
            for (TypeReference instantiationReference :
                    currentTemplateInstantiation.getReversedInstantiationReferenceStack())
            {
                ZserioToolPrinter.printWarning(instantiationReference.getLocation(),
                        "In instantiation of '" + instantiationReference.getReferencedTypeName() +
                        "' required from here");
            }
        }
        ZserioToolPrinter.printWarning(getElementTypeInstantiation(), message);
    }

    private boolean checkImplicitArrayElementType()
    {
        if (!isImplicit)
            return true;

        final ZserioType elementBaseType = getElementTypeInstantiation().getBaseType();
        if (elementBaseType instanceof FixedSizeType)
        {
            final int bitSize = ((FixedSizeType)elementBaseType).getBitSize();
            if ((bitSize % 8) == 0)
                return true;
        }

        return false;
    }

    private final TypeInstantiation elementTypeInstantiation;
    private final boolean isPacked;
    private final boolean isImplicit;
    private final Expression lengthExpression;

    private boolean isEvaluated = false;
}