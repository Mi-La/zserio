package zserio.ast;

import zserio.antlr.util.ParserException;
import zserio.tools.ZserioToolPrinter;

/**
 * Implementation of ZserioAstVisitor which handles templates instantiation.
 */
public class ZserioAstTemplator extends ZserioAstWalker
{
    public ZserioAstTemplator(ZserioAstTypeResolver typeResolver)
    {
        this.typeResolver = typeResolver;
    }

    @Override
    public void visitStructureType(StructureType structureType)
    {
        if (structureType.getTemplateParameters().isEmpty())
            structureType.visitChildren(this);
    }

    @Override
    public void visitChoiceType(ChoiceType choiceType)
    {
        if (choiceType.getTemplateParameters().isEmpty())
            choiceType.visitChildren(this);
    }

    @Override
    public void visitUnionType(UnionType unionType)
    {
        if (unionType.getTemplateParameters().isEmpty())
            unionType.visitChildren(this);
    }

    @Override
    public void visitSqlTableType(SqlTableType sqlTableType)
    {
        if (sqlTableType.getTemplateParameters().isEmpty())
            sqlTableType.visitChildren(this);
    }

    @Override
    public void visitTypeReference(TypeReference typeReference)
    {
        if (!typeReference.getTemplateArguments().isEmpty()) // if is a template instantiation
        {
            // instantiate instantiations in template arguments
            for (ZserioType templateArgument : typeReference.getTemplateArguments())
                templateArgument.accept(this);

            final ZserioType type = typeReference.getReferencedType();
            if (!(type instanceof TemplatableType) ||
                    ((TemplatableType)type).getTemplateParameters().isEmpty())
            {
                throw new ParserException(typeReference,
                        "'" + ZserioTypeUtil.getReferencedFullName(typeReference) + "' is not a template!");
            }

            final TemplatableType template = (TemplatableType)type;
            final TemplatableType.InstantiationResult instantiationResult = template.instantiate(typeReference);
            final ZserioTemplatableType instantiation = instantiationResult.getInstantiation();
            typeReference.resolveInstantiation(instantiation);

            if (instantiationResult.isNewInstance())
            {
                try
                {
                    instantiation.accept(typeResolver);
                    instantiation.accept(this);
                }
                catch (ParserException e)
                {
                    ZserioToolPrinter.printError(instantiation.getInstantiationLocation(),
                            "In instantiation of '" + template.getName() + "' required from here");
                    throw e;
                }
            }
        }
    }

    private final ZserioAstTypeResolver typeResolver;
}
