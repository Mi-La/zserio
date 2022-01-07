package zserio.extension.java;

import java.util.Locale;

import zserio.ast.Field;
import zserio.ast.Function;
import zserio.ast.Parameter;

/**
 * The class handles formatting of Java names for member accessors.
 */
final class AccessorNameFormatter
{
    public static String getIndicatorName(Field field)
    {
        return getAccessorName(INDICATOR_NAME_PREFIX, field.getName(), INDICATOR_NAME_SUFFIX);
    }

    public static String getGetterName(Field field)
    {
        return getAccessorName(GETTER_NAME_PREFIX, field.getName());
    }

    public static String getGetterName(Parameter param)
    {
        return getAccessorName(GETTER_NAME_PREFIX, param.getName());
    }

    public static String getSetterName(Field field)
    {
        return getAccessorName(SETTER_NAME_PREFIX, field.getName());
    }

    public static String getFunctionName(Function function)
    {
        return getAccessorName(FUNCTION_NAME_PREFIX, function.getName());
    }

    private static String getAccessorName(String accessorNamePrefix, String memberName)
    {
        return getAccessorName(accessorNamePrefix, memberName, "");
    }

    private static String getAccessorName(String accessorNamePrefix, String memberName,
            String accessorNameSuffix)
    {
        StringBuilder accessorName = new StringBuilder(accessorNamePrefix);
        if (!memberName.isEmpty())
        {
            final String firstMemberNameChar = String.valueOf(memberName.charAt(0));
            final String restMemberNameChars = memberName.substring(1, memberName.length());
            accessorName.append(firstMemberNameChar.toUpperCase(Locale.ENGLISH));
            accessorName.append(restMemberNameChars);
        }
        if (!accessorNameSuffix.isEmpty())
            accessorName.append(accessorNameSuffix);

        return accessorName.toString();
    }

    private static final String INDICATOR_NAME_PREFIX = "is";
    private static final String INDICATOR_NAME_SUFFIX = "Used";
    private static final String GETTER_NAME_PREFIX = "get";
    private static final String SETTER_NAME_PREFIX = "set";
    private static final String FUNCTION_NAME_PREFIX = "func";
}
