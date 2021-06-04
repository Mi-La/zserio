package zserio.extension.python.types;

/**
 * Native Python array traits mapping for fixed size integral types.
 */
public class NativeFixedSizeIntArrayTraits extends NativeArrayTraits
{
    public NativeFixedSizeIntArrayTraits(String name)
    {
        super(name, true, false);
    }
}