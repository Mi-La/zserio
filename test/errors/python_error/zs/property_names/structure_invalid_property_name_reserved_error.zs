package property_names.structure_invalid_property_name_reserved_error;

struct TestStructure
{
    uint32 __eq__; // starts with '_'
};
