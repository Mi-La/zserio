package zserio.emit.doc;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import zserio.ast.AstNode;
import zserio.ast.Package;

public class SymbolOverviewTemplateData
{
    public SymbolOverviewTemplateData(TemplateDataContext context,  Map<Package, List<AstNode>> nodesMap)
    {
        packageNames = new TreeSet<String>();
        packageSymbols = new TreeSet<PackageSymbol>();

        for (Map.Entry<Package, List<AstNode>> nodesEntry : nodesMap.entrySet())
        {
            final Package pkg = nodesEntry.getKey();
            final String packageName = context.getPackageMapper().getPackageName(pkg).toString();
            packageNames.add(packageName);
            for (AstNode node : nodesEntry.getValue())
            {
                final SymbolTemplateData symbol = SymbolTemplateDataCreator.createData(context, node);
                packageSymbols.add(new PackageSymbol(packageName, symbol));
            }
        }
    }

    public Set<String> getPackageNames()
    {
        return packageNames;
    }

    public Set<PackageSymbol> getPackageSymbols()
    {
        return packageSymbols;
    }

    public static class PackageSymbol implements Comparable<PackageSymbol>
    {
        public PackageSymbol(String packageName, SymbolTemplateData symbol)
        {
            this.packageName = packageName;
            this.symbol = symbol;
        }

        @Override
        public int compareTo(PackageSymbol other)
        {
            int result = symbol.getName().compareTo(other.symbol.getName());
            if (result == 0)
                result = packageName.compareTo(other.packageName);

            return result;
        }

        @Override
        public boolean equals(Object other)
        {
            if ( !(other instanceof PackageSymbol) )
                return false;

            return (this == other) || compareTo((PackageSymbol)other) == 0;
        }

        @Override
        public int hashCode()
        {
            final String hashString = symbol.getName() + packageName;

            return hashString.hashCode();
        }

        public String getPackageName()
        {
            return packageName;
        }

        public SymbolTemplateData getSymbol()
        {
            return symbol;
        }

        private final String packageName;
        private final SymbolTemplateData symbol;
    }

    private final Set<String> packageNames;
    private final Set<PackageSymbol> packageSymbols;
}
