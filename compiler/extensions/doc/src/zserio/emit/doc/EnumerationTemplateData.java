package zserio.emit.doc;

import java.util.ArrayList;
import java.util.List;
import java.util.SortedSet;
import java.util.TreeSet;

import zserio.ast.ChoiceType;
import zserio.ast.EnumItem;
import zserio.ast.EnumType;
import zserio.ast.Expression;
import zserio.emit.common.ExpressionFormatter;
import zserio.emit.common.ZserioEmitException;
import zserio.tools.HashUtil;
import zserio.tools.StringJoinUtil;

public class EnumerationTemplateData extends DocTemplateData
{
    public EnumerationTemplateData(TemplateDataContext context, EnumType enumType)
            throws ZserioEmitException
    {
        super(context, enumType, enumType.getName());

        linkedType = new LinkedType(enumType.getTypeInstantiation());

        for (EnumItem item: enumType.getItems())
        {
            items.add(new EnumItemTemplateData(enumType, item, context.getUsedByCollector(),
                    context.getExpressionFormatter()));
        }
    }

    public LinkedType getLinkedType()
    {
        return linkedType;
    }

    public Iterable<EnumItemTemplateData> getItems()
    {
        return items;
    }

    public static class EnumItemTemplateData
    {
        public EnumItemTemplateData(EnumType enumType, EnumItem enumItem, UsedByCollector usedByCollector,
                ExpressionFormatter docExpressionFormatter) throws ZserioEmitException
        {
            name = enumItem.getName();
            anchorName = DocEmitterTools.getAnchorName(enumType, name);

            final Expression valueExpression = enumItem.getValueExpression();
            value = (valueExpression == null) ? enumItem.getValue().toString() :
                docExpressionFormatter.formatGetter(valueExpression);

            docComment = new DocCommentTemplateData(enumItem.getDocComment());

            usageInfoList = new TreeSet<UsageInfoTemplateData>();
            for (ChoiceType choiceType : usedByCollector.getUsedByChoices(enumItem))
                usageInfoList.add(new UsageInfoTemplateData(enumItem, choiceType));
        }

        public String getName()
        {
            return name;
        }

        public String getAnchorName()
        {
            return anchorName;
        }

        public String getValue()
        {
            return value;
        }

        public DocCommentTemplateData getDocComment()
        {
            return docComment;
        }

        public Iterable<UsageInfoTemplateData> getUsageInfoList()
        {
            return usageInfoList;
        }

        public static class UsageInfoTemplateData implements Comparable<UsageInfoTemplateData>
        {
            public UsageInfoTemplateData(EnumItem enumItem, ChoiceType choiceType)
                    throws ZserioEmitException
            {
                this.choiceCaseLinkText = choiceType.getName() + "( " + enumItem.getName() + " )";
                final String urlName = DocEmitterTools.getUrlNameFromType(choiceType);
                final String anchorName = DocEmitterTools.getAnchorName(
                        choiceType, "casedef", enumItem.getName());
                this.choiceCaseLink = StringJoinUtil.joinStrings(urlName, anchorName, "#");
            }

            /* Don't change this ordering to have always the same generated HTML sources. */
            @Override
            public int compareTo(UsageInfoTemplateData other)
            {
                return getChoiceCaseLinkText().compareTo(other.getChoiceCaseLinkText());
            }

            @Override
            public boolean equals(Object other)
            {
                if ( !(other instanceof UsageInfoTemplateData) )
                    return false;

                return (this == other) || compareTo((UsageInfoTemplateData)other) == 0;
            }

            @Override
            public int hashCode()
            {
                int hash = HashUtil.HASH_SEED;
                hash = HashUtil.hash(hash, getChoiceCaseLinkText());
                return hash;
            }

            public String getChoiceCaseLinkText()
            {
                return choiceCaseLinkText;
            }

            public String getChoiceCaseLink()
            {
                return choiceCaseLink;
            }

            private final String choiceCaseLinkText;
            private final String choiceCaseLink;
        }

        private final String name;
        private final String anchorName;
        private final String value;
        private final DocCommentTemplateData docComment;
        private final SortedSet<UsageInfoTemplateData> usageInfoList;
    }

    private final LinkedType linkedType;
    private final List<EnumItemTemplateData> items = new ArrayList<EnumItemTemplateData>();
}