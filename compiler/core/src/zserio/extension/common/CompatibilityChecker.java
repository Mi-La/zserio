package zserio.extension.common;

import zserio.ast.ArrayInstantiation;
import zserio.ast.ChoiceType;
import zserio.ast.CompatibilityVersion;
import zserio.ast.CompoundType;
import zserio.ast.Field;
import zserio.ast.Root;
import zserio.ast.StructureType;
import zserio.ast.TypeInstantiation;
import zserio.ast.UnionType;
import zserio.ast.Version;
import zserio.tools.ZserioToolPrinter;

/**
 * Checks whether specified zserio_compatibility_version is compatible with current zserio generator.
 *
 * This mainly checks that code generated by current zserio generators provides binary compatible BLOBs
 * with BLOBs provided by the specified version.
 */
public class CompatibilityChecker extends DefaultTreeWalker
{
    @Override
    public boolean traverseTemplateInstantiations()
    {
        return false; // we can check packed arrays directly in templates
    }

    @Override
    public void beginRoot(Root root) throws ZserioExtensionException
    {
        compatibilityVersion = root.getRootPackage().getCompatibilityVersion();
        if (compatibilityVersion == null)
            return;
    }

    @Override
    public void beginStructure(StructureType structureType) throws ZserioExtensionException
    {
        checkCompoundPackedArrays(structureType);
    }

    @Override
    public void beginChoice(ChoiceType choiceType) throws ZserioExtensionException
    {
        checkCompoundPackedArrays(choiceType);
    }

    @Override
    public void beginUnion(UnionType unionType) throws ZserioExtensionException
    {
        checkCompoundPackedArrays(unionType);
    }

    private void checkCompoundPackedArrays(CompoundType compoundType) throws ZserioExtensionException
    {
        if (compatibilityVersion == null)
            return;

        if (compatibilityVersion.getVersion().compareTo(PACKED_ARRAY_CHANGE_VERSION) < 0)
        {
            for (Field field : compoundType.getFields())
            {
                final TypeInstantiation typeInstantiation = field.getTypeInstantiation();
                if (typeInstantiation instanceof ArrayInstantiation)
                {
                    final ArrayInstantiation arrayInstantiation = (ArrayInstantiation)typeInstantiation;
                    if (arrayInstantiation.isPacked())
                    {
                        ZserioToolPrinter.printError(compatibilityVersion.getLocation(),
                                "Root package requires compatibility with version '" +
                                compatibilityVersion.getVersion() + "'!");
                        ZserioToolPrinter.printError(field.getLocation(),
                                "Packed arrays binary encoding has been changed in version '" +
                                PACKED_ARRAY_CHANGE_VERSION + "'!");
                        throw new ZserioExtensionException("Compatibility check failed!");
                    }
                }
            }
        }
    }

    private static final Version PACKED_ARRAY_CHANGE_VERSION = new Version(2, 5, 0);

    private CompatibilityVersion compatibilityVersion = null;
}
