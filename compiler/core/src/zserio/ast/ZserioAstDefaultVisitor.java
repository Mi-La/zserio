package zserio.ast;

/**
 * The class provide default implementation of ZserioAstVisitor.
 *
 * The default implementation does nothing. This can be useful for one-level visiting without any tree walking.
 */
public class ZserioAstDefaultVisitor implements ZserioAstVisitor
{
    @Override
    public void visitRoot(Root root)
    {}

    @Override
    public void visitPackage(Package unitPackage)
    {}

    @Override
    public void visitCompatibilityVersion(CompatibilityVersion compatibilityVersion)
    {}

    @Override
    public void visitImport(Import unitImport)
    {}

    @Override
    public void visitConstant(Constant constant)
    {}

    @Override
    public void visitRuleGroup(RuleGroup ruleGroup)
    {}

    @Override
    public void visitSubtype(Subtype subtype)
    {}

    @Override
    public void visitStructureType(StructureType structureType)
    {}

    @Override
    public void visitChoiceType(ChoiceType choiceType)
    {}

    @Override
    public void visitUnionType(UnionType unionType)
    {}

    @Override
    public void visitEnumType(EnumType enumType)
    {}

    @Override
    public void visitBitmaskType(BitmaskType bitmaskType)
    {}

    @Override
    public void visitSqlTableType(SqlTableType sqlTableType)
    {}

    @Override
    public void visitSqlDatabaseType(SqlDatabaseType sqlDatabaseType)
    {}

    @Override
    public void visitServiceType(ServiceType serviceType)
    {}

    @Override
    public void visitPubsubType(PubsubType pubsubType)
    {}

    @Override
    public void visitField(Field field)
    {}

    @Override
    public void visitChoiceCase(ChoiceCase choiceCase)
    {}

    @Override
    public void visitChoiceCaseExpression(ChoiceCaseExpression choiceCaseExpression)
    {}

    @Override
    public void visitChoiceDefault(ChoiceDefault choiceDefault)
    {}

    @Override
    public void visitEnumItem(EnumItem enumItem)
    {}

    @Override
    public void visitBitmaskValue(BitmaskValue bitmaskValue)
    {}

    @Override
    public void visitSqlConstraint(SqlConstraint sqlConstraint)
    {}

    @Override
    public void visitServiceMethod(ServiceMethod serviceMethod)
    {}

    @Override
    public void visitPubsubMessage(PubsubMessage pubsubMessage)
    {}

    @Override
    public void visitRule(Rule rule)
    {}

    @Override
    public void visitFunction(Function function)
    {}

    @Override
    public void visitParameter(Parameter parameter)
    {}

    @Override
    public void visitExpression(Expression expresssion)
    {}

    @Override
    public void visitTypeReference(TypeReference typeReference)
    {}

    @Override
    public void visitTypeInstantiation(TypeInstantiation typeInstantiation)
    {}

    @Override
    public void visitArrayType(ArrayType arrayType)
    {}

    @Override
    public void visitStdIntegerType(StdIntegerType stdIntegerType)
    {}

    @Override
    public void visitVarIntegerType(VarIntegerType varIntegerType)
    {}

    @Override
    public void visitFixedBitFieldType(FixedBitFieldType fixedFieldTypeType)
    {}

    @Override
    public void visitDynamicBitFieldType(DynamicBitFieldType dynamicBitFieldType)
    {}

    @Override
    public void visitBooleanType(BooleanType booleanType)
    {}

    @Override
    public void visitBytesType(BytesType bytesType)
    {}

    @Override
    public void visitStringType(StringType stringType)
    {}

    @Override
    public void visitFloatType(FloatType floatType)
    {}

    @Override
    public void visitExternType(ExternType externType)
    {}

    @Override
    public void visitTemplateParameter(TemplateParameter templateParameter)
    {}

    @Override
    public void visitTemplateArgument(TemplateArgument templateArgument)
    {}

    @Override
    public void visitInstantiateType(InstantiateType templateInstantiation)
    {
        templateInstantiation.visitChildren(this);
    }

    @Override
    public void visitDocCommentClassic(DocCommentClassic docComment)
    {}

    @Override
    public void visitDocCommentMarkdown(DocCommentMarkdown docComment)
    {}

    @Override
    public void visitDocParagraph(DocParagraph docParagraph)
    {}

    @Override
    public void visitDocElement(DocElement docElement)
    {}

    @Override
    public void visitDocMultiline(DocMultiline docMultiline)
    {}

    @Override
    public void visitDocTagSee(DocTagSee docTagSee)
    {}

    @Override
    public void visitDocTagTodo(DocTagTodo docTagTodo)
    {}

    @Override
    public void visitDocTagParam(DocTagParam docTagParam)
    {}

    @Override
    public void visitDocTagDeprecated(DocTagDeprecated docTagDeprecated)
    {}

    @Override
    public void visitDocLine(DocLine docLine)
    {}

    @Override
    public void visitDocLineElement(DocLineElement docLineElement)
    {}

    @Override
    public void visitDocText(DocText docText)
    {}
}
