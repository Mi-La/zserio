package array_types_error;

import static org.junit.Assert.*;

import java.io.IOException;

import org.junit.BeforeClass;
import org.junit.Test;

import test_utils.ZserioErrors;

public class ArrayTypesErrorTest
{
    @BeforeClass
    public static void readZserioErrors() throws IOException
    {
        zserioErrors = new ZserioErrors();
    }

    @Test
    public void arrayLengthNotAvailable()
    {
        final String error = "array_length_field_not_available_error.zs:7:18: " +
                "Unresolved symbol 'array2Size' within expression scope!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void implicitArrayBitfieldWithWrongLength()
    {
        final String error = "implicit_array_bitfield_with_wrong_length_error.zs:5:14: " +
                "Implicit arrays are allowed only for types which have fixed size rounded to bytes!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void implicitArrayBool()
    {
        final String error = "implicit_array_bool_error.zs:5:14: " +
                "Implicit arrays are allowed only for types which have fixed size rounded to bytes!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void implicitArrayComplexWithFieldBehind()
    {
        final String errors[] =
        {
            "implicit_array_complex_with_field_behind_error.zs:6:21:     implicit array is used here",
            "implicit_array_complex_with_field_behind_error.zs:12:24:     implicit array is used here",
            "implicit_array_complex_with_field_behind_error.zs:19:37:     implicit array is used here",
            "implicit_array_complex_with_field_behind_error.zs:41:40:     implicit array is used here",
            "implicit_array_complex_with_field_behind_error.zs:44:12: Field 'field' follows an implicit array!"
        };
        assertTrue(zserioErrors.isPresent(errors));
    }

    @Test
    public void implicitArrayCompound()
    {
        final String error = "implicit_array_compound_error.zs:10:14: " +
                "Implicit arrays are allowed only for types which have fixed size rounded to bytes!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void implicitArrayDynamicBitfield()
    {
        final String error = "implicit_array_dynamic_bitfield_error.zs:6:14: " +
                "Implicit arrays are allowed only for types which have fixed size rounded to bytes!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void implicitArrayNotLast()
    {
        final String errors[] =
        {
            "implicit_array_not_last_error.zs:5:21:     implicit array is used here",
            "implicit_array_not_last_error.zs:6:21: Field 'wrong' follows an implicit array!"
        };
        assertTrue(zserioErrors.isPresent(errors));
    }

    @Test
    public void implicitArrayString()
    {
        final String error = "implicit_array_string_error.zs:5:14: " +
                "Implicit arrays are allowed only for types which have fixed size rounded to bytes!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void implicitArrayStructNotLast()
    {
        final String errors[] =
        {
            "implicit_array_struct_not_last_error.zs:6:20:     implicit array is used here",
            "implicit_array_struct_not_last_error.zs:11:24:     implicit array is used here",
            "implicit_array_struct_not_last_error.zs:12:12: Field 'anotherField' follows an implicit array!"
        };
        assertTrue(zserioErrors.isPresent(errors));
    }

    @Test
    public void implicitArrayVarint()
    {
        final String error = "implicit_array_varint_error.zs:5:14: " +
                "Implicit arrays are allowed only for types which have fixed size rounded to bytes!";
        assertTrue(zserioErrors.isPresent(error));
    }


    @Test
    public void implicitArrayWithAutoArrayBehind()
    {
        final String errors[] =
        {
            "implicit_array_with_auto_array_behind_error.zs:5:21:     implicit array is used here",
            "implicit_array_with_auto_array_behind_error.zs:10:24:     implicit array is used here",
            "implicit_array_with_auto_array_behind_error.zs:11:12: Field 'array' follows an implicit array!"
        };
        assertTrue(zserioErrors.isPresent(errors));
    }

    @Test
    public void implicitArrayWithAutoOptionalBehind()
    {
        final String errors[] =
        {
            "implicit_array_with_auto_optional_behind_error.zs:5:21:     implicit array is used here",
            "implicit_array_with_auto_optional_behind_error.zs:10:24:     implicit array is used here",
            "implicit_array_with_auto_optional_behind_error.zs:11:21: " +
                    "Field 'autoOptional' follows an implicit array!"
        };
        assertTrue(zserioErrors.isPresent(errors));
    }

    @Test
    public void implicitArrayWithLength()
    {
        final String error = "implicit_array_with_length_error.zs:6:27: Length expression is not allowed " +
                "for implicit arrays!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void implicitArrayWithIndexedOffsets()
    {
        final String error = "implicit_array_with_indexed_offsets_error.zs:22:9: " +
                "Implicit arrays cannot have indexed offsets!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void implicitArrayWithPackedArrayBehind()
    {
        final String errors[] =
        {
            "implicit_array_with_packed_array_behind_error.zs:5:21:     implicit array is used here",
            "implicit_array_with_packed_array_behind_error.zs:19:24:     implicit array is used here",
            "implicit_array_with_packed_array_behind_error.zs:22:29: " +
                    "Field 'packedArray2' follows an implicit array!"
        };
        assertTrue(zserioErrors.isPresent(errors));
    };

    @Test
    public void nonEmptyArrayRecursion()
    {
        final String error = "non_empty_array_recursion_error.zs:9:33: " +
                "Field 'array3' is recursive and neither optional nor array which can be empty!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void packedArrayChoiceHasNoPackableField()
    {
        final String error = "packed_array_choice_has_no_packable_field_error.zs:40:12: " +
                "'ChoiceWithoutPackableField' doesn't contain any packable field!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void packedArrayStructHasNoPackableField()
    {
        final String error = "packed_array_struct_has_no_packable_field_error.zs:44:12: " +
                "'StructWithoutPackable' doesn't contain any packable field!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void packedArrayUnpackableBoolElement()
    {
        final String error =
                "packed_array_unpackable_bool_element_error.zs:23:12: 'bool' is not packable element type!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void packedArrayUnpackableExternElement()
    {
        final String error =
                "packed_array_unpackable_extern_element_error.zs:6:12: 'extern' is not packable element type!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void packedArrayUnpackableFloatElement()
    {
        final String error =
                "packed_array_unpackable_float_element_error.zs:6:12: 'float64' is not packable element type!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void packedArrayUnpackableStringElement()
    {
        final String error =
                "packed_array_unpackable_string_element_error.zs:6:12: 'string' is not packable element type!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void packedImplicitArray()
    {
        final String error = "packed_implicit_array_error.zs:5:12: Implicit arrays cannot be packed!";
        assertTrue(zserioErrors.isPresent(error));
    }

    @Test
    public void wrongArrayLengthType()
    {
        final String error = "wrong_array_length_type_error.zs:6:21: Invalid length expression for array. " +
                "Length must be integer!";
        assertTrue(zserioErrors.isPresent(error));
    }

    private static ZserioErrors zserioErrors;
}
