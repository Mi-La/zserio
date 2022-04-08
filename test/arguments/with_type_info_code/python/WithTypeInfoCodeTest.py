import unittest
import os
import json
import zserio

from zserio.typeinfo import TypeAttribute, MemberAttribute, TypeInfo

from testutils import getZserioApi, getApiDir

class WithTypeInfoCodeTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.api = getZserioApi(__file__, "with_type_info_code.zs",
                               extraArgs=["-withTypeInfoCode", "-allowImplicitArrays"])

    def testSqlDatabase(self):
        self._checkSqlDatabase(self.api.SqlDatabase.type_info())

    def testSimplePubsub(self):
        self._checkSimplePubsub(self.api.SimplePubsub.type_info())

    def testSimpleService(self):
        self._checkSimpleService(self.api.SimpleService.type_info())

    def testWriteReadFileWithOptionals(self):
        withTypeInfoCode = self._createWithTypeInfoCode(createOptionals=True)
        zserio.serialize_to_file(withTypeInfoCode, self.BLOB_NAME_WITH_OPTIONALS)

        readWithTypeInfoCode = zserio.deserialize_from_file(self.api.WithTypeInfoCode,
                                                            self.BLOB_NAME_WITH_OPTIONALS)
        self.assertEqual(withTypeInfoCode, readWithTypeInfoCode)

    def testWriteReadFileWithoutOptionals(self):
        withTypeInfoCode = self._createWithTypeInfoCode(createOptionals=False)
        zserio.serialize_to_file(withTypeInfoCode, self.BLOB_NAME_WITHOUT_OPTIONALS)

        readWithTypeInfoCode = zserio.deserialize_from_file(self.api.WithTypeInfoCode,
                                                            self.BLOB_NAME_WITHOUT_OPTIONALS)
        self.assertEqual(withTypeInfoCode, readWithTypeInfoCode)

    def testJsonWriterWithOptionals(self):
        withTypeInfoCode = self._createWithTypeInfoCode(createOptionals=True)
        withTypeInfoCode.initialize_offsets(0)
        with open(self.JSON_NAME_WITH_OPTIONALS, "w", encoding="utf-8") as jsonFile:
            walker = zserio.Walker(zserio.JsonWriter(text_io=jsonFile, indent=4))
            walker.walk(withTypeInfoCode)
        self._checkWithTypeInfoCodeJson(self.JSON_NAME_WITH_OPTIONALS, createdOptionals=True)

    def testJsonWriterWithoutOptionals(self):
        withTypeInfoCode = self._createWithTypeInfoCode(createOptionals=False)
        withTypeInfoCode.initialize_offsets(0)
        with open(self.JSON_NAME_WITHOUT_OPTIONALS, "w", encoding="utf-8") as jsonFile:
            walker = zserio.Walker(zserio.JsonWriter(text_io=jsonFile, indent=4))
            walker.walk(withTypeInfoCode)
        self._checkWithTypeInfoCodeJson(self.JSON_NAME_WITHOUT_OPTIONALS, createdOptionals=False)

    def _checkSimpleStruct(self, type_info):
        self.assertEqual("with_type_info_code.SimpleStruct", type_info.schema_name)
        self.assertEqual(self.api.SimpleStruct, type_info.py_type)
        self.assertEqual(1, len(type_info.attributes))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(7, len(fields))

        # fieldU32
        member_info = fields[0]
        self.assertEqual("fieldU32", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(3, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_u32", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.ALIGN, member_info.attributes)
        self.assertEqual("8", member_info.attributes[MemberAttribute.ALIGN])
        self.assertIn(MemberAttribute.INITIALIZER, member_info.attributes)
        self.assertEqual("10", member_info.attributes[MemberAttribute.INITIALIZER])

        # fieldOffset
        member_info = fields[1]
        self.assertEqual("fieldOffset", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_offset", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # fieldString
        member_info = fields[2]
        self.assertEqual("fieldString", member_info.schema_name)
        self.assertEqual("string", member_info.type_info.schema_name)
        self.assertEqual(str, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(3, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_string", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.OFFSET, member_info.attributes)
        self.assertEqual("self.field_offset", member_info.attributes[MemberAttribute.OFFSET])
        self.assertIn(MemberAttribute.INITIALIZER, member_info.attributes)
        self.assertEqual("\"My\" + \"String\"", member_info.attributes[MemberAttribute.INITIALIZER])

        # fieldBool
        member_info = fields[3]
        self.assertEqual("fieldBool", member_info.schema_name)
        self.assertEqual("bool", member_info.type_info.schema_name)
        self.assertEqual(bool, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_bool", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.INITIALIZER, member_info.attributes)
        self.assertEqual("False", member_info.attributes[MemberAttribute.INITIALIZER])

        # fieldFloat16
        member_info = fields[4]
        self.assertEqual("fieldFloat16", member_info.schema_name)
        self.assertEqual("float16", member_info.type_info.schema_name)
        self.assertEqual(float, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_float16", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.INITIALIZER, member_info.attributes)
        self.assertEqual("1.0", member_info.attributes[MemberAttribute.INITIALIZER])

        # fieldFloat32
        member_info = fields[5]
        self.assertEqual("fieldFloat32", member_info.schema_name)
        self.assertEqual("float32", member_info.type_info.schema_name)
        self.assertEqual(float, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_float32", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # fieldFloat64
        member_info = fields[6]
        self.assertEqual("fieldFloat64", member_info.schema_name)
        self.assertEqual("float64", member_info.type_info.schema_name)
        self.assertEqual(float, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_float64", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.INITIALIZER, member_info.attributes)
        self.assertEqual("2.0", member_info.attributes[MemberAttribute.INITIALIZER])

    def _checkComplexStruct(self, type_info):
        self.assertEqual("with_type_info_code.ComplexStruct", type_info.schema_name)
        self.assertEqual(self.api.ComplexStruct, type_info.py_type)
        self.assertEqual(2, len(type_info.attributes))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(7, len(fields))
        self.assertIn(TypeAttribute.FUNCTIONS, type_info.attributes)
        functions = type_info.attributes[TypeAttribute.FUNCTIONS]
        self.assertEqual(1, len(functions))

        # simpleStruct
        member_info = fields[0]
        self.assertEqual("simpleStruct", member_info.schema_name)
        self._checkSimpleStruct(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("simple_struct", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # optionalSimpleStruct
        member_info = fields[1]
        self.assertEqual("optionalSimpleStruct", member_info.schema_name)
        self._checkSimpleStruct(member_info.type_info)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("optional_simple_struct", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.OPTIONAL, member_info.attributes)
        self.assertIsNone(member_info.attributes[MemberAttribute.OPTIONAL])

        # array
        member_info = fields[2]
        self.assertEqual("array", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(3, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("array", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertIsNone(member_info.attributes[MemberAttribute.ARRAY_LENGTH])
        self.assertIn(MemberAttribute.CONSTRAINT, member_info.attributes)
        self.assertEqual("len(self.array) > 0", member_info.attributes[MemberAttribute.CONSTRAINT])

        # arrayWithLen
        member_info = fields[3]
        self.assertEqual("arrayWithLen", member_info.schema_name)
        self.assertEqual("int:5", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(3, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("array_with_len", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertEqual("self.array[0]", member_info.attributes[MemberAttribute.ARRAY_LENGTH])
        self.assertIn(MemberAttribute.OPTIONAL, member_info.attributes)
        self.assertEqual("self.array[0] > 0", member_info.attributes[MemberAttribute.OPTIONAL])

        # paramStructArray
        member_info = fields[4]
        self.assertEqual("paramStructArray", member_info.schema_name)
        self._checkParameterizedStruct(member_info.type_info)
        self.assertEqual(4, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("param_struct_array", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.OPTIONAL, member_info.attributes)
        self.assertEqual(None, member_info.attributes[MemberAttribute.OPTIONAL])
        self.assertIn(MemberAttribute.TYPE_ARGUMENTS, member_info.attributes)
        self.assertEqual(["self.simple_struct"], member_info.attributes[MemberAttribute.TYPE_ARGUMENTS])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertEqual(None, member_info.attributes[MemberAttribute.ARRAY_LENGTH])

        # dynamicBitField
        member_info = fields[5]
        self.assertEqual("dynamicBitField", member_info.schema_name)
        self.assertEqual("bit", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("dynamic_bit_field", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.TYPE_ARGUMENTS, member_info.attributes)
        self.assertEqual(["self.simple_struct.field_u32"],
                         member_info.attributes[MemberAttribute.TYPE_ARGUMENTS])

        # dynamicBitFieldArray
        member_info = fields[6]
        self.assertEqual("dynamicBitFieldArray", member_info.schema_name)
        self.assertEqual("bit", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(4, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("dynamic_bit_field_array", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.PACKED, member_info.attributes)
        self.assertIsNone(member_info.attributes[MemberAttribute.PACKED])
        self.assertIn(MemberAttribute.TYPE_ARGUMENTS, member_info.attributes)
        self.assertEqual(["self.dynamic_bit_field * 2"],
                         member_info.attributes[MemberAttribute.TYPE_ARGUMENTS])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertEqual(None, member_info.attributes[MemberAttribute.ARRAY_LENGTH])

        # firstArrayElement
        member_info = functions[0]
        self.assertEqual("firstArrayElement", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.FUNCTION_NAME, member_info.attributes)
        self.assertEqual("first_array_element", member_info.attributes[MemberAttribute.FUNCTION_NAME])
        self.assertIn(MemberAttribute.FUNCTION_RESULT, member_info.attributes)
        self.assertEqual("(self.array[0]) if (len(self.array) > 0) else (0)",
                         member_info.attributes[MemberAttribute.FUNCTION_RESULT])


    def _checkParameterizedStruct(self, type_info):
        self.assertEqual("with_type_info_code.ParameterizedStruct", type_info.schema_name)
        self.assertEqual(self.api.ParameterizedStruct, type_info.py_type)
        self.assertEqual(2, len(type_info.attributes))
        self.assertIn(TypeAttribute.PARAMETERS, type_info.attributes)
        parameters = type_info.attributes[TypeAttribute.PARAMETERS]
        self.assertEqual(1, len(parameters))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(1, len(fields))

        # simple
        member_info = parameters[0]
        self.assertEqual("simple", member_info.schema_name)
        self._checkSimpleStruct(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("simple", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # array
        member_info = fields[0]
        self.assertEqual("array", member_info.schema_name)
        self.assertEqual("uint8", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("array", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertEqual("self.simple.field_u32", member_info.attributes[MemberAttribute.ARRAY_LENGTH])

    def _checkRecursiveStruct(self, type_info):
        self.assertEqual("with_type_info_code.RecursiveStruct", type_info.schema_name)
        self.assertEqual(self.api.RecursiveStruct, type_info.py_type)
        self.assertEqual(1, len(type_info.attributes))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(3, len(fields))

        # fieldU32
        member_info = fields[0]
        self.assertEqual("fieldU32", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_u32", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # fieldRecursion
        member_info = fields[1]
        self.assertEqual("fieldRecursion", member_info.schema_name)
        self.assertEqual(type_info.schema_name, member_info.type_info.schema_name)
        self.assertEqual(type_info.py_type, member_info.type_info.py_type)
        self.assertEqual(len(type_info.attributes[TypeAttribute.FIELDS]),
                         len(member_info.type_info.attributes[TypeAttribute.FIELDS]))
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_recursion", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.OPTIONAL, member_info.attributes)
        self.assertIsNone(member_info.attributes[MemberAttribute.OPTIONAL])

        # arrayRecursion
        member_info = fields[2]
        self.assertEqual("arrayRecursion", member_info.schema_name)
        self.assertEqual(type_info.schema_name, member_info.type_info.schema_name)
        self.assertEqual(type_info.py_type, member_info.type_info.py_type)
        self.assertEqual(len(type_info.attributes[TypeAttribute.FIELDS]),
                         len(member_info.type_info.attributes[TypeAttribute.FIELDS]))
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("array_recursion", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertIsNone(member_info.attributes[MemberAttribute.ARRAY_LENGTH])

    def _checkRecursiveUnion(self, type_info):
        self.assertEqual("with_type_info_code.RecursiveUnion", type_info.schema_name)
        self.assertEqual(self.api.RecursiveUnion, type_info.py_type)
        self.assertEqual(2, len(type_info.attributes))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertIn(TypeAttribute.SELECTOR, type_info.attributes)
        self.assertEqual(None, type_info.attributes[TypeAttribute.SELECTOR])
        self.assertEqual(2, len(fields))

        # fieldU32
        member_info = fields[0]
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_u32", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # recursive
        member_info = fields[1]
        self.assertEqual("recursive", member_info.schema_name)
        self.assertEqual(type_info.schema_name, member_info.type_info.schema_name)
        self.assertEqual(type_info.py_type, member_info.type_info.py_type)
        self.assertEqual(len(type_info.attributes[TypeAttribute.FIELDS]),
                         len(member_info.type_info.attributes[TypeAttribute.FIELDS]))
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("recursive", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertEqual(None, member_info.attributes[MemberAttribute.ARRAY_LENGTH])

    def _checkRecursiveChoice(self, type_info):
        self.assertEqual("with_type_info_code.RecursiveChoice", type_info.schema_name)
        self.assertEqual(self.api.RecursiveChoice, type_info.py_type)
        self.assertEqual(4, len(type_info.attributes))
        self.assertIn(TypeAttribute.PARAMETERS, type_info.attributes)
        parameters = type_info.attributes[TypeAttribute.PARAMETERS]
        self.assertEqual(2, len(parameters))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(2, len(fields))
        self.assertIn(TypeAttribute.SELECTOR, type_info.attributes)
        self.assertEqual("self.param1", type_info.attributes[TypeAttribute.SELECTOR])
        self.assertIn(TypeAttribute.CASES, type_info.attributes)
        cases = type_info.attributes[TypeAttribute.CASES]
        self.assertEqual(2, len(cases))

        # param1
        member_info = parameters[0]
        self.assertEqual("param1", member_info.schema_name)
        self.assertEqual("bool", member_info.type_info.schema_name)
        self.assertEqual(bool, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("param1", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # param2
        member_info = parameters[1]
        self.assertEqual("param2", member_info.schema_name)
        self.assertEqual("bool", member_info.type_info.schema_name)
        self.assertEqual(bool, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("param2", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # case true
        case_info = cases[0]
        self.assertEqual(["True"], case_info.case_expressions)
        self.assertEqual(fields[0].schema_name, case_info.field.schema_name)

        # case false
        case_info = cases[1]
        self.assertEqual(["False"], case_info.case_expressions)
        self.assertEqual(fields[1].schema_name, case_info.field.schema_name)

        # recursive
        member_info = fields[0]
        self.assertEqual("recursive", member_info.schema_name)
        self.assertEqual(type_info.schema_name, member_info.type_info.schema_name)
        self.assertEqual(type_info.py_type, member_info.type_info.py_type)
        self.assertEqual(len(type_info.attributes[TypeAttribute.FIELDS]),
                         len(member_info.type_info.attributes[TypeAttribute.FIELDS]))
        self.assertEqual(3, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("recursive", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertEqual(None, member_info.attributes[MemberAttribute.ARRAY_LENGTH])
        self.assertIn(MemberAttribute.TYPE_ARGUMENTS, member_info.attributes)
        self.assertEqual(["self.param2", "False"], member_info.attributes[MemberAttribute.TYPE_ARGUMENTS])

        # fieldU32
        member_info = fields[1]
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_u32", member_info.attributes[MemberAttribute.PROPERTY_NAME])

    def _checkTestEnum(self, type_info):
        self.assertEqual("with_type_info_code.TestEnum", type_info.schema_name)
        self.assertEqual(self.api.TestEnum, type_info.py_type)
        self.assertEqual(2, len(type_info.attributes))
        self.assertIn(TypeAttribute.UNDERLYING_TYPE, type_info.attributes)
        underlying_info = type_info.attributes[TypeAttribute.UNDERLYING_TYPE]
        self.assertEqual("with_type_info_code.EnumUnderlyingType", underlying_info.schema_name)
        self.assertEqual(int, underlying_info.py_type)
        self.assertFalse(underlying_info.attributes)
        self.assertIn(TypeAttribute.ENUM_ITEMS, type_info.attributes)
        items = type_info.attributes[TypeAttribute.ENUM_ITEMS]
        self.assertEqual(3, len(items))

        # One
        item_info = items[0]
        self.assertEqual("One", item_info.schema_name)
        self.assertEqual(self.api.TestEnum.ONE, item_info.py_item)

        # TWO
        item_info = items[1]
        self.assertEqual("TWO", item_info.schema_name)
        self.assertEqual(self.api.TestEnum.TWO, item_info.py_item)

        # ThreeItem
        item_info = items[2]
        self.assertEqual("ItemThree", item_info.schema_name)
        self.assertEqual(self.api.TestEnum.ITEM_THREE, item_info.py_item)

    def _checkTestBitmask(self, type_info):
        self.assertEqual("with_type_info_code.TestBitmask", type_info.schema_name)
        self.assertEqual(self.api.TestBitmask, type_info.py_type)
        self.assertEqual(3, len(type_info.attributes))
        self.assertIn(TypeAttribute.UNDERLYING_TYPE, type_info.attributes)
        underlying_info = type_info.attributes[TypeAttribute.UNDERLYING_TYPE]
        self.assertEqual("bit", underlying_info.schema_name)
        self.assertEqual(int, underlying_info.py_type)
        self.assertFalse(underlying_info.attributes)
        self.assertIn(TypeAttribute.UNDERLYING_TYPE_ARGUMENTS, type_info.attributes)
        underlying_args = type_info.attributes[TypeAttribute.UNDERLYING_TYPE_ARGUMENTS]
        self.assertEqual(["10"], underlying_args)
        self.assertIn(TypeAttribute.BITMASK_VALUES, type_info.attributes)
        items = type_info.attributes[TypeAttribute.BITMASK_VALUES]
        self.assertEqual(3, len(items))

        # RED
        item_info = items[0]
        self.assertEqual("RED", item_info.schema_name)
        self.assertEqual(self.api.TestBitmask.Values.RED, item_info.py_item)

        # Green
        item_info = items[1]
        self.assertEqual("Green", item_info.schema_name)
        self.assertEqual(self.api.TestBitmask.Values.GREEN, item_info.py_item)

        # Color Blue
        item_info = items[2]
        self.assertEqual("ColorBlue", item_info.schema_name)
        self.assertEqual(self.api.TestBitmask.Values.COLOR_BLUE, item_info.py_item)

    def _checkSimpleUnion(self, type_info):
        self.assertEqual("with_type_info_code.SimpleUnion", type_info.schema_name)
        self.assertEqual(self.api.SimpleUnion, type_info.py_type)
        self.assertEqual(3, len(type_info.attributes))
        self.assertIn(TypeAttribute.SELECTOR, type_info.attributes)
        self.assertIsNone(type_info.attributes[TypeAttribute.SELECTOR])
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(2, len(fields))
        self.assertIn(TypeAttribute.FUNCTIONS, type_info.attributes)
        functions = type_info.attributes[TypeAttribute.FUNCTIONS]
        self.assertEqual(1, len(functions))

        # testBitmask
        member_info = fields[0]
        self.assertEqual("testBitmask", member_info.schema_name)
        self._checkTestBitmask(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("test_bitmask", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # simpleStruct
        member_info = fields[1]
        self.assertEqual("simpleStruct", member_info.schema_name)
        self._checkSimpleStruct(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("simple_struct", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # simpleStructFieldU32
        member_info = functions[0]
        self.assertEqual("simpleStructFieldU32", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.FUNCTION_NAME, member_info.attributes)
        self.assertEqual("simple_struct_field_u32", member_info.attributes[MemberAttribute.FUNCTION_NAME])
        self.assertIn(MemberAttribute.FUNCTION_RESULT, member_info.attributes)
        self.assertEqual("self.simple_struct.field_u32",
                         member_info.attributes[MemberAttribute.FUNCTION_RESULT])

    def _checkSimpleChoice(self, type_info):
        self.assertEqual("with_type_info_code.SimpleChoice", type_info.schema_name)
        self.assertEqual(self.api.SimpleChoice, type_info.py_type)
        self.assertEqual(5, len(type_info.attributes))
        self.assertIn(TypeAttribute.PARAMETERS, type_info.attributes)
        parameters = type_info.attributes[TypeAttribute.PARAMETERS]
        self.assertEqual(1, len(parameters))
        self.assertIn(TypeAttribute.SELECTOR, type_info.attributes)
        self.assertEqual("self.selector", type_info.attributes[TypeAttribute.SELECTOR])
        self.assertIn(TypeAttribute.CASES, type_info.attributes)
        cases = type_info.attributes[TypeAttribute.CASES]
        self.assertEqual(3, len(cases))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(2, len(fields))
        self.assertIn(TypeAttribute.FUNCTIONS, type_info.attributes)
        functions = type_info.attributes[TypeAttribute.FUNCTIONS]
        self.assertEqual(1, len(functions))

        # selector
        member_info = parameters[0]
        self.assertEqual("selector", member_info.schema_name)
        self._checkTestEnum(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("selector", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # case One
        case_info = cases[0]
        self.assertEqual(["with_type_info_code.test_enum.TestEnum.ONE"], case_info.case_expressions)
        self.assertIsNone(case_info.field)

        # case TWO
        case_info = cases[1]
        self.assertEqual(["with_type_info_code.test_enum.TestEnum.TWO"], case_info.case_expressions)
        self.assertIsNotNone(case_info.field)
        self.assertEqual("fieldTwo", case_info.field.schema_name)
        self._checkSimpleUnion(case_info.field.type_info)
        self.assertEqual(1, len(case_info.field.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, case_info.field.attributes)
        self.assertEqual("field_two", case_info.field.attributes[MemberAttribute.PROPERTY_NAME])

        # default
        case_info = cases[2]
        self.assertEqual(0, len(case_info.case_expressions))
        self.assertIsNotNone(case_info.field)
        self.assertEqual("fieldDefault", case_info.field.schema_name)
        self.assertEqual("string", case_info.field.type_info.schema_name)
        self.assertEqual(str, case_info.field.type_info.py_type)
        self.assertFalse(case_info.field.type_info.attributes)
        self.assertEqual(1, len(case_info.field.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, case_info.field.attributes)
        self.assertEqual("field_default", case_info.field.attributes[MemberAttribute.PROPERTY_NAME])

        # fieldTwo
        member_info = fields[0]
        self.assertEqual("fieldTwo", member_info.schema_name)
        self._checkSimpleUnion(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_two", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # fieldDefault
        member_info = fields[1]
        self.assertEqual("fieldDefault", member_info.schema_name)
        self.assertEqual("string", member_info.type_info.schema_name)
        self.assertEqual(str, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field_default", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # fieldTwoFuncCall
        member_info = functions[0]
        self.assertEqual("fieldTwoFuncCall", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.FUNCTION_NAME, member_info.attributes)
        self.assertEqual("field_two_func_call", member_info.attributes[MemberAttribute.FUNCTION_NAME])
        self.assertIn(MemberAttribute.FUNCTION_RESULT, member_info.attributes)
        self.assertEqual("self.field_two.simple_struct_field_u32()",
                         member_info.attributes[MemberAttribute.FUNCTION_RESULT])

    def _checkTS32(self, type_info):
        self.assertEqual("with_type_info_code.TS32", type_info.schema_name)
        self.assertEqual(self.api.TS32, type_info.py_type)
        self.assertEqual(3, len(type_info.attributes))
        self.assertIn(TypeAttribute.TEMPLATE_NAME, type_info.attributes)
        self.assertEqual("with_type_info_code.TemplatedStruct",
                         type_info.attributes[TypeAttribute.TEMPLATE_NAME])
        self.assertIn(TypeAttribute.TEMPLATE_ARGUMENTS, type_info.attributes)
        template_args = type_info.attributes[TypeAttribute.TEMPLATE_ARGUMENTS]
        self.assertEqual(1, len(template_args))
        arg = template_args[0]
        self.assertIsInstance(arg, TypeInfo)
        self.assertEqual("uint32", arg.schema_name)
        self.assertEqual(int, arg.py_type)
        self.assertFalse(arg.attributes)
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(1, len(fields))

        # field
        member_info = fields[0]
        self.assertEqual("field", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("field", member_info.attributes[MemberAttribute.PROPERTY_NAME])

    def _checkTemplatedParameterizedStruct_TS32(self, type_info):
        self.assertEqual("with_type_info_code.TemplatedParameterizedStruct_TS32",
                         type_info.schema_name)
        self.assertEqual(self.api.TemplatedParameterizedStruct_TS32, type_info.py_type)
        self.assertEqual(4, len(type_info.attributes))
        self.assertIn(TypeAttribute.TEMPLATE_NAME, type_info.attributes)
        self.assertEqual("with_type_info_code.TemplatedParameterizedStruct",
                         type_info.attributes[TypeAttribute.TEMPLATE_NAME])
        self.assertIn(TypeAttribute.TEMPLATE_ARGUMENTS, type_info.attributes)
        template_args = type_info.attributes[TypeAttribute.TEMPLATE_ARGUMENTS]
        self.assertEqual(1, len(template_args))
        arg = template_args[0]
        self.assertIsInstance(arg, TypeInfo)
        self._checkTS32(arg)
        self.assertIn(TypeAttribute.PARAMETERS, type_info.attributes)
        parameters = type_info.attributes[TypeAttribute.PARAMETERS]
        self.assertEqual(1, len(parameters))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(1, len(fields))

        # param
        member_info = parameters[0]
        self.assertEqual("param", member_info.schema_name)
        self._checkTS32(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("param", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # array
        member_info = fields[0]
        self.assertEqual("array", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("array", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertEqual("self.param.field", member_info.attributes[MemberAttribute.ARRAY_LENGTH])

    def _checkWithTypeInfoCode(self, type_info):
        self.assertEqual("with_type_info_code.WithTypeInfoCode", type_info.schema_name)
        self.assertEqual(self.api.WithTypeInfoCode, type_info.py_type)
        self.assertEqual(1, len(type_info.attributes))
        self.assertIn(TypeAttribute.FIELDS, type_info.attributes)
        fields = type_info.attributes[TypeAttribute.FIELDS]
        self.assertEqual(12, len(fields))

        # simpleStruct
        member_info = fields[0]
        self.assertEqual("simpleStruct", member_info.schema_name)
        self._checkSimpleStruct(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("simple_struct", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # complexStruct
        member_info = fields[1]
        self.assertEqual("complexStruct", member_info.schema_name)
        self._checkComplexStruct(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("complex_struct", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # parameterizedStruct
        member_info = fields[2]
        self.assertEqual("parameterizedStruct", member_info.schema_name)
        self._checkParameterizedStruct(member_info.type_info)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("parameterized_struct", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.TYPE_ARGUMENTS, member_info.attributes)
        self.assertEqual(["self.simple_struct"], member_info.attributes[MemberAttribute.TYPE_ARGUMENTS])

        # recursiveStruct
        member_info = fields[3]
        self.assertEqual("recursiveStruct", member_info.schema_name)
        self._checkRecursiveStruct(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("recursive_struct", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # recursiveUnion
        member_info = fields[4]
        self.assertEqual("recursiveUnion", member_info.schema_name)
        self._checkRecursiveUnion(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("recursive_union", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # recursiveChoice
        member_info = fields[5]
        self.assertEqual("recursiveChoice", member_info.schema_name)
        self._checkRecursiveChoice(member_info.type_info)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("recursive_choice", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.TYPE_ARGUMENTS, member_info.attributes)
        self.assertEqual(["True", "False"], member_info.attributes[MemberAttribute.TYPE_ARGUMENTS])

        # selector
        member_info = fields[6]
        self.assertEqual("selector", member_info.schema_name)
        self._checkTestEnum(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("selector", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # simpleChoice
        member_info = fields[7]
        self.assertEqual("simpleChoice", member_info.schema_name)
        self._checkSimpleChoice(member_info.type_info)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("simple_choice", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.TYPE_ARGUMENTS, member_info.attributes)
        self.assertEqual(["self.selector"], member_info.attributes[MemberAttribute.TYPE_ARGUMENTS])

        # templatedStruct
        member_info = fields[8]
        self.assertEqual("templatedStruct", member_info.schema_name)
        self._checkTS32(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("templated_struct", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # templatedParameterizedStruct
        member_info = fields[9]
        self.assertEqual("templatedParameterizedStruct", member_info.schema_name)
        self._checkTemplatedParameterizedStruct_TS32(member_info.type_info)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("templated_parameterized_struct",
                         member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.TYPE_ARGUMENTS, member_info.attributes)
        self.assertEqual(["self.templated_struct"], member_info.attributes[MemberAttribute.TYPE_ARGUMENTS])

        # externData
        member_info = fields[10]
        self.assertEqual("externData", member_info.schema_name)
        self.assertEqual("extern", member_info.type_info.schema_name)
        self.assertEqual(zserio.BitBuffer, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("extern_data", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # implicitArray
        member_info = fields[11]
        self.assertEqual("implicitArray", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(3, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("implicit_array", member_info.attributes[MemberAttribute.PROPERTY_NAME])
        self.assertIn(MemberAttribute.IMPLICIT, member_info.attributes)
        self.assertIsNone(member_info.attributes[MemberAttribute.IMPLICIT])
        self.assertIn(MemberAttribute.ARRAY_LENGTH, member_info.attributes)
        self.assertIsNone(member_info.attributes[MemberAttribute.ARRAY_LENGTH])

    def _checkSqlTable(self, type_info):
        self.assertEqual("with_type_info_code.SqlTable", type_info.schema_name)
        self.assertEqual(self.api.SqlTable, type_info.py_type)
        self.assertEqual(1, len(type_info.attributes))
        self.assertIn(TypeAttribute.COLUMNS, type_info.attributes)
        columns = type_info.attributes[TypeAttribute.COLUMNS]
        self.assertEqual(2, len(columns))

        # pk
        member_info = columns[0]
        self.assertEqual("pk", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("INTEGER", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])
        self.assertIn(MemberAttribute.SQL_CONSTRAINT, member_info.attributes)
        self.assertEqual("PRIMARY KEY NOT NULL", member_info.attributes[MemberAttribute.SQL_CONSTRAINT])

        # text
        member_info = columns[1]
        self.assertEqual("text", member_info.schema_name)
        self.assertEqual("string", member_info.type_info.schema_name)
        self.assertEqual(str, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("TEXT", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])

    def _checkTemplatedSqlTable_uint32(self, type_info):
        self.assertEqual("with_type_info_code.TemplatedSqlTable_uint32", type_info.schema_name)
        self.assertEqual(self.api.TemplatedSqlTable_uint32, type_info.py_type)
        self.assertEqual(4, len(type_info.attributes))
        self.assertIn(TypeAttribute.TEMPLATE_NAME, type_info.attributes)
        self.assertEqual("with_type_info_code.TemplatedSqlTable",
                         type_info.attributes[TypeAttribute.TEMPLATE_NAME])
        self.assertIn(TypeAttribute.TEMPLATE_ARGUMENTS, type_info.attributes)
        template_args = type_info.attributes[TypeAttribute.TEMPLATE_ARGUMENTS]
        self.assertEqual(1, len(template_args))
        arg = template_args[0]
        self.assertIsInstance(arg, TypeInfo)
        self.assertEqual("uint32", arg.schema_name)
        self.assertEqual(int, arg.py_type)
        self.assertFalse(arg.attributes)
        self.assertIn(TypeAttribute.COLUMNS, type_info.attributes)
        columns = type_info.attributes[TypeAttribute.COLUMNS]
        self.assertEqual(2, len(columns))
        self.assertIn(TypeAttribute.SQL_CONSTRAINT, type_info.attributes)
        self.assertEqual("PRIMARY KEY(pk)", type_info.attributes[TypeAttribute.SQL_CONSTRAINT])

        # pk
        member_info = columns[0]
        self.assertEqual("pk", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("INTEGER", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])
        self.assertIn(MemberAttribute.SQL_CONSTRAINT, member_info.attributes)
        self.assertEqual("NOT NULL", member_info.attributes[MemberAttribute.SQL_CONSTRAINT])

        # withTypeInfoCode
        member_info = columns[1]
        self.assertEqual("withTypeInfoCode", member_info.schema_name)
        self._checkWithTypeInfoCode(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("BLOB", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])

    def _checkTemplatedSqlTableU8(self, type_info):
        self.assertEqual("with_type_info_code.TemplatedSqlTableU8", type_info.schema_name)
        self.assertEqual(self.api.TemplatedSqlTableU8, type_info.py_type)
        self.assertEqual(4, len(type_info.attributes))
        self.assertIn(TypeAttribute.TEMPLATE_NAME, type_info.attributes)
        self.assertEqual("with_type_info_code.TemplatedSqlTable",
                         type_info.attributes[TypeAttribute.TEMPLATE_NAME])
        self.assertIn(TypeAttribute.TEMPLATE_ARGUMENTS, type_info.attributes)
        template_args = type_info.attributes[TypeAttribute.TEMPLATE_ARGUMENTS]
        self.assertEqual(1, len(template_args))
        arg = template_args[0]
        self.assertIsInstance(arg, TypeInfo)
        self.assertEqual("uint8", arg.schema_name)
        self.assertEqual(int, arg.py_type)
        self.assertFalse(arg.attributes)
        self.assertIn(TypeAttribute.COLUMNS, type_info.attributes)
        columns = type_info.attributes[TypeAttribute.COLUMNS]
        self.assertEqual(2, len(columns))
        self.assertIn(TypeAttribute.SQL_CONSTRAINT, type_info.attributes)
        self.assertEqual("PRIMARY KEY(pk)", type_info.attributes[TypeAttribute.SQL_CONSTRAINT])

        # pk
        member_info = columns[0]
        self.assertEqual("pk", member_info.schema_name)
        self.assertEqual("uint8", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("INTEGER", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])
        self.assertIn(MemberAttribute.SQL_CONSTRAINT, member_info.attributes)
        self.assertEqual("NOT NULL", member_info.attributes[MemberAttribute.SQL_CONSTRAINT])

        # withTypeInfoCode
        member_info = columns[1]
        self.assertEqual("withTypeInfoCode", member_info.schema_name)
        self._checkWithTypeInfoCode(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("BLOB", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])

    def _checkFts4Table(self, type_info):
        self.assertEqual("with_type_info_code.Fts4Table", type_info.schema_name)
        self.assertEqual(self.api.Fts4Table, type_info.py_type)
        self.assertEqual(2, len(type_info.attributes))
        self.assertIn(TypeAttribute.VIRTUAL_TABLE_USING, type_info.attributes)
        self.assertEqual("fts4", type_info.attributes[TypeAttribute.VIRTUAL_TABLE_USING])
        self.assertIn(TypeAttribute.COLUMNS, type_info.attributes)
        columns = type_info.attributes[TypeAttribute.COLUMNS]
        self.assertEqual(2, len(columns))

        # docId
        member_info = columns[0]
        self.assertEqual("docId", member_info.schema_name)
        self.assertEqual("int64", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("INTEGER", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])
        self.assertIn(MemberAttribute.VIRTUAL, member_info.attributes)
        self.assertIsNone(member_info.attributes[MemberAttribute.VIRTUAL])

        # searchTags
        member_info = columns[1]
        self.assertEqual("searchTags", member_info.schema_name)
        self.assertEqual("string", member_info.type_info.schema_name)
        self.assertEqual(str, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("TEXT", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])

    def _checkWithoutRowIdTable(self, type_info):
        self.assertEqual("with_type_info_code.WithoutRowIdTable", type_info.schema_name)
        self.assertEqual(self.api.WithoutRowIdTable, type_info.py_type)
        self.assertEqual(3, len(type_info.attributes))
        self.assertIn(TypeAttribute.WITHOUT_ROWID, type_info.attributes)
        self.assertIsNone(type_info.attributes[TypeAttribute.WITHOUT_ROWID])
        self.assertIn(TypeAttribute.COLUMNS, type_info.attributes)
        columns = type_info.attributes[TypeAttribute.COLUMNS]
        self.assertEqual(2, len(columns))
        self.assertIn(TypeAttribute.SQL_CONSTRAINT, type_info.attributes)
        self.assertEqual("PRIMARY KEY(pk1, pk2)", type_info.attributes[TypeAttribute.SQL_CONSTRAINT])

        # pk1
        member_info = columns[0]
        self.assertEqual("pk1", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("INTEGER", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])
        self.assertIn(MemberAttribute.SQL_CONSTRAINT, member_info.attributes)
        self.assertEqual("NOT NULL", member_info.attributes[MemberAttribute.SQL_CONSTRAINT])

        # pk2
        member_info = columns[1]
        self.assertEqual("pk2", member_info.schema_name)
        self.assertEqual("uint32", member_info.type_info.schema_name)
        self.assertEqual(int, member_info.type_info.py_type)
        self.assertFalse(member_info.type_info.attributes)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.SQL_TYPE_NAME, member_info.attributes)
        self.assertEqual("INTEGER", member_info.attributes[MemberAttribute.SQL_TYPE_NAME])
        self.assertIn(MemberAttribute.SQL_CONSTRAINT, member_info.attributes)
        self.assertEqual("NOT NULL", member_info.attributes[MemberAttribute.SQL_CONSTRAINT])

    def _checkSqlDatabase(self, type_info):
        self.assertEqual("with_type_info_code.SqlDatabase", type_info.schema_name)
        self.assertEqual(self.api.SqlDatabase, type_info.py_type)
        self.assertEqual(1, len(type_info.attributes))
        self.assertIn(TypeAttribute.TABLES, type_info.attributes)
        tables = type_info.attributes[TypeAttribute.TABLES]
        self.assertEqual(5, len(tables))

        # sqlTable
        member_info = tables[0]
        self.assertEqual("sqlTable", member_info.schema_name)
        self._checkSqlTable(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("sql_table", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # templatedSqlTableU32
        member_info = tables[1]
        self.assertEqual("templatedSqlTableU32", member_info.schema_name)
        self._checkTemplatedSqlTable_uint32(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("templated_sql_table_u32", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # templatedSqlTableU8
        member_info = tables[2]
        self.assertEqual("templatedSqlTableU8", member_info.schema_name)
        self._checkTemplatedSqlTableU8(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("templated_sql_table_u8", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # fts4Table
        member_info = tables[3]
        self.assertEqual("fts4Table", member_info.schema_name)
        self._checkFts4Table(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("fts4_table", member_info.attributes[MemberAttribute.PROPERTY_NAME])

        # withoutRowIdTable
        member_info = tables[4]
        self.assertEqual("withoutRowIdTable", member_info.schema_name)
        self._checkWithoutRowIdTable(member_info.type_info)
        self.assertEqual(1, len(member_info.attributes))
        self.assertIn(MemberAttribute.PROPERTY_NAME, member_info.attributes)
        self.assertEqual("without_row_id_table", member_info.attributes[MemberAttribute.PROPERTY_NAME])

    def _checkSimplePubsub(self, type_info):
        self.assertEqual("with_type_info_code.SimplePubsub", type_info.schema_name)
        self.assertEqual(self.api.SimplePubsub, type_info.py_type)
        self.assertEqual(1, len(type_info.attributes))
        self.assertIn(TypeAttribute.MESSAGES, type_info.attributes)
        messages = type_info.attributes[TypeAttribute.MESSAGES]
        self.assertEqual(2, len(messages))

        # pubSimpleStruct
        member_info = messages[0]
        self.assertEqual("pubSimpleStruct", member_info.schema_name)
        self._checkSimpleStruct(member_info.type_info)
        self.assertEqual(2, len(member_info.attributes), member_info.attributes)
        self.assertIn(MemberAttribute.TOPIC, member_info.attributes)
        self.assertEqual("simpleStruct", member_info.attributes[MemberAttribute.TOPIC])
        self.assertIn(MemberAttribute.PUBLISH, member_info.attributes)
        self.assertEqual("publish_pub_simple_struct", member_info.attributes[MemberAttribute.PUBLISH])

        # subSimpleStruct
        member_info = messages[1]
        self.assertEqual("subSimpleStruct", member_info.schema_name)
        self._checkSimpleStruct(member_info.type_info)
        self.assertEqual(2, len(member_info.attributes), member_info.attributes)
        self.assertIn(MemberAttribute.TOPIC, member_info.attributes)
        self.assertEqual("simpleStruct", member_info.attributes[MemberAttribute.TOPIC])
        self.assertIn(MemberAttribute.SUBSCRIBE, member_info.attributes)
        self.assertEqual("subscribe_sub_simple_struct", member_info.attributes[MemberAttribute.SUBSCRIBE])

    def _checkSimpleService(self, type_info):
        self.assertEqual("with_type_info_code.SimpleService", type_info.schema_name)
        self.assertEqual(self.api.SimpleService, type_info.py_type)
        self.assertEqual(1, len(type_info.attributes))
        self.assertIn(TypeAttribute.METHODS, type_info.attributes)
        methods = type_info.attributes[TypeAttribute.METHODS]
        self.assertEqual(1, len(methods))

        # getSimpleStruct
        member_info = methods[0]
        self.assertEqual("getSimpleStruct", member_info.schema_name)
        self._checkSimpleStruct(member_info.type_info)
        self.assertEqual(2, len(member_info.attributes))
        self.assertIn(MemberAttribute.CLIENT_METHOD_NAME, member_info.attributes)
        self.assertEqual("get_simple_struct", member_info.attributes[MemberAttribute.CLIENT_METHOD_NAME])
        self.assertIn(MemberAttribute.REQUEST_TYPE, member_info.attributes)
        self._checkSimpleUnion(member_info.attributes[MemberAttribute.REQUEST_TYPE])

    def _createWithTypeInfoCode(self, *, createOptionals):
        simpleStruct = self._createSimpleStruct()
        testEnum = self.api.TestEnum.TWO
        ts32 = self._createTS32()
        withTypeInfoCode = self.api.WithTypeInfoCode(
            simpleStruct,
            self._createComplexStruct(createOptionals),
            self._createParameterizedStruct(simpleStruct),
            self._createRecursiveStruct(),
            self._createRecursiveUnion(),
            self._createRecursiveChoice(True, False),
            testEnum,
            self._createSimpleChoice(testEnum),
            ts32,
            self._createTemplatedParameterizedStruct_TS32(ts32),
            zserio.BitBuffer(bytes([0xCA, 0xFE]), 15),
            [1, 4, 6, 4, 6, 1])

        return withTypeInfoCode

    def _checkWithTypeInfoCodeJson(self, jsonFileName, *, createdOptionals):
        with open(jsonFileName, 'r', encoding="utf-8") as jsonFile:
            jsonData = json.load(jsonFile)

        testEnum = self.api.TestEnum.TWO
        ts32 = self._createTS32()
        self._checkSimpleStructJson(jsonData["simpleStruct"], 8)
        self._checkComplexStructJson(jsonData["complexStruct"], createdOptionals)
        self._checkParameterizedStructJson(jsonData["parameterizedStruct"], 10)
        self._checkRecursiveStructJson(jsonData["recursiveStruct"])
        self._checkRecursiveUnionJson(jsonData["recursiveUnion"])
        self._checkRecursiveChoiceJson(jsonData["recursiveChoice"], True, False)
        self.assertEqual(testEnum.value, jsonData["selector"])
        self._checkSimpleChoiceJson(jsonData["simpleChoice"], testEnum)
        self._checkTS32Json(jsonData["templatedStruct"])
        self._checkTemplatedParameterizedStruct_TS32Json(jsonData["templatedParameterizedStruct"], ts32)
        self.assertEqual("b'\\xca\\xfe'", jsonData["externData"]["buffer"])
        self.assertEqual(15, jsonData["externData"]["bitSize"])
        implicitArray = [1, 4, 6, 4, 6, 1]
        self.assertEqual(len(implicitArray), len(jsonData["implicitArray"]))
        for i, implicitArrayElement in enumerate(implicitArray):
            self.assertEqual(implicitArrayElement, jsonData["implicitArray"][i])

    def _createSimpleStruct(self):
        simpleStruct = self.api.SimpleStruct()
        simpleStruct.field_offset = 0
        simpleStruct.field_float32 = 4.0

        return simpleStruct

    def _checkSimpleStructJson(self, simpleStruct, fieldOffset):
        self.assertEqual(10, simpleStruct["fieldU32"])
        self.assertEqual(fieldOffset, simpleStruct["fieldOffset"])
        self.assertEqual("MyString", simpleStruct["fieldString"])
        self.assertEqual(False, simpleStruct["fieldBool"])
        self.assertEqual(1.0, simpleStruct["fieldFloat16"])
        self.assertEqual(4.0, simpleStruct["fieldFloat32"])
        self.assertEqual(2.0, simpleStruct["fieldFloat64"])

    def _createComplexStruct(self, createOptionals):
        simpleStruct = self._createSimpleStruct()
        complexStruct = self.api.ComplexStruct(
            simpleStruct,
            self._createSimpleStruct() if createOptionals else None,
            [3, 0xABCD2, 0xABCD3, 0xABCD4, 0xABCD5],
            [3, 2, 1],
            [self._createParameterizedStruct(simpleStruct),
             self._createParameterizedStruct(simpleStruct)] if createOptionals else None,
            7,
            list(range(1, 65536, 2)))

        return complexStruct

    def _checkComplexStructJson(self, complexStruct, createdOptionals):
        self._checkSimpleStructJson(complexStruct["simpleStruct"], 40)
        if createdOptionals:
            self._checkSimpleStructJson(complexStruct["optionalSimpleStruct"], 72)
        else:
            self.assertEqual(None, complexStruct["optionalSimpleStruct"])
        self.assertEqual([3, 0xABCD2, 0xABCD3, 0xABCD4, 0xABCD5], complexStruct["array"])
        self.assertEqual([3, 2, 1], complexStruct["arrayWithLen"])
        if createdOptionals:
            self._checkParameterizedStructJson(complexStruct["paramStructArray"][0], 10)
            self._checkParameterizedStructJson(complexStruct["paramStructArray"][1], 10)
        else:
            self.assertEqual(None, complexStruct["paramStructArray"])
        self.assertEqual(7, complexStruct["dynamicBitField"])
        self.assertEqual(list(range(1, 65536, 2)), complexStruct["dynamicBitFieldArray"])

    def _createParameterizedStruct(self, simpleStruct):
        parameterizedStruct = self.api.ParameterizedStruct(
            simpleStruct,
            list(range(simpleStruct.field_u32)))

        return parameterizedStruct

    def _checkParameterizedStructJson(self, parameterizedStruct, fieldU32):
        self.assertEqual(list(range(fieldU32)), parameterizedStruct["array"])

    def _createRecursiveStruct(self):
        recursiveStruct = self.api.RecursiveStruct(
            0xDEAD1,
            self.api.RecursiveStruct(0xDEAD2, None, []),
            [self.api.RecursiveStruct(0xDEAD3, None, []), self.api.RecursiveStruct(0xDEAD4, None, []) ])

        return recursiveStruct

    def _checkRecursiveStructJson(self, recursiveStruct):
        self.assertEqual(0xDEAD1, recursiveStruct["fieldU32"])
        self.assertEqual(0xDEAD2, recursiveStruct["fieldRecursion"]["fieldU32"])
        self.assertEqual(None, recursiveStruct["fieldRecursion"]["fieldRecursion"])
        self.assertEqual([], recursiveStruct["fieldRecursion"]["arrayRecursion"])
        self.assertEqual(0xDEAD3, recursiveStruct["arrayRecursion"][0]["fieldU32"])
        self.assertEqual(None, recursiveStruct["arrayRecursion"][0]["fieldRecursion"])
        self.assertEqual([], recursiveStruct["arrayRecursion"][0]["arrayRecursion"])
        self.assertEqual(0xDEAD4, recursiveStruct["arrayRecursion"][1]["fieldU32"])
        self.assertEqual(None, recursiveStruct["arrayRecursion"][1]["fieldRecursion"])
        self.assertEqual([], recursiveStruct["arrayRecursion"][1]["arrayRecursion"])

    def _createRecursiveUnion(self):
        recursiveUnion = self.api.RecursiveUnion()
        recursiveUnion.recursive = [self.api.RecursiveUnion(field_u32_ = 0xDEAD)]

        return recursiveUnion

    def _checkRecursiveUnionJson(self, recursiveUnion):
        self.assertEqual(0xDEAD, recursiveUnion["recursive"][0]["fieldU32"])

    def _createRecursiveChoice(self, param1, param2):
        recursiveChoice = self.api.RecursiveChoice(param1, param2)
        if param1:
            recursiveChoice.recursive = [self._createRecursiveChoice(param2, False)]
        else:
            recursiveChoice.field_u32 = 0xDEAD

        return recursiveChoice

    def _checkRecursiveChoiceJson(self, recursiveChoice, param1, param2):
        if param1:
            for i in range(len(recursiveChoice["recursive"])):
                self._checkRecursiveChoiceJson(recursiveChoice["recursive"][i], param2, False)
        else:
            self.assertEqual(0xDEAD, recursiveChoice["fieldU32"])

    def _createSimpleUnion(self):
        simpleUnion = self.api.SimpleUnion()
        simpleUnion.test_bitmask = self.api.TestBitmask.Values.GREEN

        return simpleUnion

    def _checkSimpleUnionJson(self, simpleUnion):
        self.assertEqual(self.api.TestBitmask.Values.GREEN.value, simpleUnion["testBitmask"])

    def _createSimpleChoice(self, testEnum):
        simpleChoice = self.api.SimpleChoice(testEnum)
        if testEnum == self.api.TestEnum.TWO:
            simpleChoice.field_two = self._createSimpleUnion()
        else:
            simpleChoice.field_default = "text"

        return simpleChoice

    def _checkSimpleChoiceJson(self, simpleChoice, testEnum):
        if testEnum == self.api.TestEnum.TWO:
            self._checkSimpleUnionJson(simpleChoice["fieldTwo"])
        else:
            self.assertEqual("text", simpleChoice["fieldDefault"])

    def _createTS32(self):
        ts32 = self.api.TS32(
            0xDEAD
            )

        return ts32

    def _checkTS32Json(self, ts32):
        self.assertEqual(0xDEAD, ts32["field"])

    def _createTemplatedParameterizedStruct_TS32(self, ts32):
        templatedParameterizedStruct_TS32 = self.api.TemplatedParameterizedStruct_TS32(
            ts32,
            list(range(ts32.field, 0, -1)))

        return templatedParameterizedStruct_TS32

    def _checkTemplatedParameterizedStruct_TS32Json(self, templatedParameterizedStruct_TS32, ts32):
        for i in range(ts32.field, 0, -1):
            self.assertEqual(i, templatedParameterizedStruct_TS32["array"][ts32.field - i])

    BLOB_NAME_WITH_OPTIONALS = os.path.join(getApiDir(os.path.dirname(__file__)),
                                            "with_type_info_code_optionals.blob")
    BLOB_NAME_WITHOUT_OPTIONALS = os.path.join(getApiDir(os.path.dirname(__file__)),
                                               "with_type_info_code.blob")
    JSON_NAME_WITH_OPTIONALS = os.path.join(getApiDir(os.path.dirname(__file__)),
                                            "with_type_info_code_optionals.json")
    JSON_NAME_WITHOUT_OPTIONALS = os.path.join(getApiDir(os.path.dirname(__file__)),
                                               "with_type_info_code.json")
