package generated_symbols.structure_indicator_function_clash_error;

struct TestStructure
{
    optional uint32 field;

    function bool isFieldUsed() // clashes with generated indicator method
    {
        return false;
    }
};
