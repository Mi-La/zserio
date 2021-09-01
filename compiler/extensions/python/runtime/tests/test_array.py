import unittest

from zserio.array import (Array, BitFieldArrayTraits, SignedBitFieldArrayTraits,
                          VarUInt16ArrayTraits, VarUInt32ArrayTraits, VarUInt64ArrayTraits, VarUIntArrayTraits,
                          VarSizeArrayTraits, VarInt16ArrayTraits, VarInt32ArrayTraits, VarInt64ArrayTraits,
                          VarIntArrayTraits, Float16ArrayTraits, Float32ArrayTraits, Float64ArrayTraits,
                          StringArrayTraits, BoolArrayTraits, BitBufferArrayTraits, ObjectArrayTraits,
                          PackingContextNode)
from zserio.bitposition import alignto
from zserio.bitbuffer import BitBuffer
from zserio.bitreader import BitStreamReader
from zserio.bitsizeof import bitsizeof_varsize
from zserio.bitwriter import BitStreamWriter
from zserio import PythonRuntimeException
from zserio.limits import UINT64_MIN, UINT64_MAX, INT64_MIN, INT64_MAX

class ArrayTest(unittest.TestCase):

    def test_bitfield_array(self):
        array_traits = BitFieldArrayTraits(5)
        array1_values = [1, 2]
        array1_bitsizeof = 2 * 5
        array1_aligned_bitsizeof = 5 + 3 + 5
        array2_values = [3, 4]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_signed_bitfield_array(self):
        array_traits = SignedBitFieldArrayTraits(5)
        array1_values = [-1, 1]
        array1_bitsizeof = 2 * 5
        array1_aligned_bitsizeof = 5 + 3 + 5
        array2_values = [-2, 2]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varuint16_array(self):
        array_traits = VarUInt16ArrayTraits()
        array1_values = [1, 1024]
        array1_bitsizeof = 8 + 16
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [1, 8192]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varuint32_array(self):
        array_traits = VarUInt32ArrayTraits()
        array1_values = [1, 16384]
        array1_bitsizeof = 8 + 24
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [1, 32768]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varuint64_array(self):
        array_traits = VarUInt64ArrayTraits()
        array1_values = [1, 16384]
        array1_bitsizeof = 8 + 24
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [1, 65536]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varuint_array(self):
        array_traits = VarUIntArrayTraits()
        array1_values = [1, 1024]
        array1_bitsizeof = 8 + 16
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [1, 8192]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varsize_array(self):
        array_traits = VarSizeArrayTraits()
        array1_values = [1, 16384]
        array1_bitsizeof = 8 + 24
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [1, 32768]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varint16_array(self):
        array_traits = VarInt16ArrayTraits()
        array1_values = [-1, 1024]
        array1_bitsizeof = 8 + 16
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [-1, 8192]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varint32_array(self):
        array_traits = VarInt32ArrayTraits()
        array1_values = [-1, 16384]
        array1_bitsizeof = 8 + 24
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [-1, 32768]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varint64_array(self):
        array_traits = VarInt64ArrayTraits()
        array1_values = [-1, 16384]
        array1_bitsizeof = 8 + 24
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [-1, 65536]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_varint_array(self):
        array_traits = VarIntArrayTraits()
        array1_values = [-1, 1024]
        array1_bitsizeof = 8 + 16
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [-1, 8192]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_float16_array(self):
        array_traits = Float16ArrayTraits()
        array1_values = [-1.0, 1.0]
        array1_bitsizeof = 2 * 16
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [-3.5, 3.5]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_float32_array(self):
        array_traits = Float32ArrayTraits()
        array1_values = [-1.0, 1.0]
        array1_bitsizeof = 2 * 32
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [-3.5, 3.5]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_float64_array(self):
        array_traits = Float64ArrayTraits()
        array1_values = [-1.0, 1.0]
        array1_bitsizeof = 2 * 64
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = [-3.5, 3.5]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_string_array(self):
        array_traits = StringArrayTraits()
        array1_values = ["Text1", "Text2"]
        array1_bitsizeof = 2 * (1 + len("TextN")) * 8
        array1_aligned_bitsizeof = array1_bitsizeof
        array2_values = ["Text3", "Text4"]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_bool_array(self):
        array_traits = BoolArrayTraits()
        array1_values = [True, False]
        array1_bitsizeof = 2 * 1
        array1_aligned_bitsizeof = 1 + 7 + 1
        array2_values = [True, True]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_bitbuffer_array(self):
        array_traits = BitBufferArrayTraits()
        array1_values = [BitBuffer(bytes([0xAB, 0xE0]), 11), BitBuffer(bytes([0xAB, 0xCD, 0xFE]), 23)]
        array1_bitsizeof = 8 + 11 + 8 + 23
        array1_aligned_bitsizeof = 8 + 11 + 5 + 8 + 23
        array2_values = [BitBuffer(bytes([0xBA, 0xE0]), 11), BitBuffer(bytes([0xBA, 0xDC, 0xFE]), 23)]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    class DummyObject:
        def __init__(self, value = int()):
            self._value = value

        @classmethod
        def create(cls, reader, _index):
            instance = cls()
            instance.read(reader)

            return instance

        @classmethod
        def create_packed(cls, context_node, reader, _index):
            instance = cls()
            instance.read_packed(context_node, reader)

            return instance

        def __eq__(self, other):
            return self._value == other._value

        def __hash__(self):
            return hash(self._value)

        @staticmethod
        def create_packing_context(context_node):
            context_node.create_child().create_context()

        def init_packing_context(self, context_node):
            context = context_node.children[0].context
            context.init(self._value)

        @staticmethod
        def bitsizeof(_bitposition):
            return 31 # to make an unaligned type

        def bitsizeof_packed(self, context_node, bitposition):
            end_bitposition = bitposition

            context = context_node.children[0].context
            end_bitposition += context.bitsizeof(BitFieldArrayTraits(31), end_bitposition, self._value)

            return end_bitposition - bitposition

        def initialize_offsets(self, bitposition):
            return bitposition + self.bitsizeof(bitposition)

        def initialize_offsets_packed(self, context_node, bitposition):
            end_bitposition = bitposition

            context = context_node.children[0].context
            end_bitposition += context.bitsizeof(BitFieldArrayTraits(31), end_bitposition, self._value)

            return end_bitposition

        def read(self, reader):
            self._value = reader.read_bits(self.bitsizeof(0))

        def read_packed(self, context_node, reader):
            context = context_node.children[0].context
            self._value = context.read(BitFieldArrayTraits(31), reader)

        def write(self, writer, *, zserio_call_initialize_offsets=True):
            del zserio_call_initialize_offsets
            writer.write_bits(self._value, self.bitsizeof(0))

        def write_packed(self, context_node, writer):
            context = context_node.children[0].context
            context.write(BitFieldArrayTraits(31), writer, self._value)

    def test_object_array(self):
        array_traits = ObjectArrayTraits(ArrayTest.DummyObject.create,
                                         ArrayTest.DummyObject.create_packed,
                                         ArrayTest.DummyObject.create_packing_context)
        array1_values = [ArrayTest.DummyObject(1), ArrayTest.DummyObject(2)]
        array1_bitsizeof = 2 * 31
        array1_aligned_bitsizeof = 31 + 1 + 31
        array2_values = [ArrayTest.DummyObject(3), ArrayTest.DummyObject(4)]
        self._test_array(array_traits, array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values)

    def test_bitfield_packed_array(self):
        array_traits = BitFieldArrayTraits(64)

        self._test_packed_array(array_traits, [10, 11, 12])
        self._test_packed_array(array_traits, [10, 10, 10]) # zero delta
        self._test_packed_array(array_traits, []) # empty
        self._test_packed_array(array_traits, [10]) # single element

        # packing not applied, delta is too big
        self._test_packed_array(array_traits, [UINT64_MIN, UINT64_MAX])
        self._test_packed_array(array_traits, [UINT64_MAX, UINT64_MAX // 2, UINT64_MIN])

        # will have maxBitNumber 62 bits
        self._test_packed_array(array_traits, [0, INT64_MAX // 2, 100, 200, 300, 400, 500, 600, 700])

    def test_signed_bitfield_packed_array(self):
        array_traits = SignedBitFieldArrayTraits(64)
        self._test_packed_array(array_traits, [-10, 11, -12])
        self._test_packed_array(array_traits, [-10, -10, -10]) # zero delta

        self._test_packed_array(array_traits, []) # empty
        self._test_packed_array(array_traits, [-10]) # single element

        # packing not applied, delta is too big
        self._test_packed_array(array_traits, [INT64_MIN, INT64_MAX])
        self._test_packed_array(array_traits, [INT64_MIN, 0, INT64_MAX])

    def test_varuint_packed_array(self):
        array_traits = VarUIntArrayTraits()
        self._test_packed_array(array_traits, [100, 200, 300])
        self._test_packed_array(array_traits, [300, 200, 100])

        self._test_packed_array(array_traits, [UINT64_MIN, UINT64_MAX])
        self._test_packed_array(array_traits, [UINT64_MAX, UINT64_MAX // 2, UINT64_MIN])

    def test_object_packed_array(self):
        array_traits = ObjectArrayTraits(ArrayTest.DummyObject.create,
                                         ArrayTest.DummyObject.create_packed,
                                         ArrayTest.DummyObject.create_packing_context)
        self._test_packed_array(array_traits, [ArrayTest.DummyObject(1), ArrayTest.DummyObject(2)])
        self._test_packed_array(array_traits, [ArrayTest.DummyObject(3), ArrayTest.DummyObject(4)])

    def test_packing_context_node(self):
        with self.assertRaises(PythonRuntimeException):
            self.assertIsNotNone(PackingContextNode().context)

    @staticmethod
    def _set_offset_method(_index, _bitoffset):
        pass

    @staticmethod
    def _check_offset_method(_index, _bitoffset):
        pass

    def _test_array(self, array_traits,
                    array1_values, array1_bitsizeof, array1_aligned_bitsizeof, array2_values):
        self._test_eq(array_traits, array1_values, array2_values)
        self._test_hashcode(array_traits, array1_values, array2_values)
        self._test_len(array_traits, array1_values)
        self._test_get_item(array_traits, array1_values)
        self._test_set_item(array_traits, array1_values)
        self._test_raw_array(array_traits, array1_values, array2_values)

        auto_bitsize = bitsizeof_varsize(len(array1_values))

        self._test_array_normal(array_traits, array1_values, array1_bitsizeof)
        self._test_array_auto(array_traits, array1_values, auto_bitsize + array1_bitsizeof)
        self._test_array_aligned(array_traits, array1_values, array1_aligned_bitsizeof)
        self._test_array_aligned_auto(array_traits, array1_values, auto_bitsize + array1_aligned_bitsizeof)
        self._test_array_implicit(array_traits, array1_values, array1_bitsizeof)

    def _test_packed_array(self, array_traits, array_values):
        self._test_packed_array_normal(array_traits, array_values)
        self._test_packed_array_auto(array_traits, array_values)
        self._test_packed_array_aligned(array_traits, array_values)
        self._test_packed_array_aligned_auto(array_traits, array_values)
        self._test_packed_array_implicit(array_traits, array_values)

    def _test_eq(self, array_traits, array1_values, array2_values):
        array1 = Array(array_traits, array1_values)
        array2 = Array(array_traits, array2_values)
        array3 = Array(array_traits, array1_values)
        self.assertNotEqual(array1, None)
        self.assertNotEqual(array1, array2)
        self.assertEqual(array1, array3)

    def _test_hashcode(self, array_traits, array1_values, array2_values):
        array1 = Array(array_traits, array1_values)
        array2 = Array(array_traits, array2_values)
        array3 = Array(array_traits, array1_values)
        self.assertNotEqual(hash(array1), hash(array2))
        self.assertEqual(hash(array1), hash(array3))

    def _test_len(self, array_traits, array_values):
        array = Array(array_traits, array_values)
        raw_array = array.raw_array
        self.assertEqual(len(raw_array), len(array))

    def _test_get_item(self, array_traits, array_values):
        array = Array(array_traits, array_values)
        raw_array = array.raw_array
        for value, raw_value in zip(array, raw_array):
            self.assertEqual(value, raw_value)

    def _test_set_item(self, array_traits, array_values):
        array = Array(array_traits, array_values)
        raw_array = array.raw_array
        self.assertTrue(len(array) > 1)
        first_value = array[0]
        second_value = array[1]
        array[0] = second_value
        self.assertEqual(array[0], raw_array[0])
        raw_array[0] = first_value # return the original value for other tests
        self.assertEqual(array[0], raw_array[0])

    def _test_raw_array(self, array_traits, array1_values, array2_values):
        array1 = Array(array_traits, array1_values)
        array2 = Array(array_traits, array2_values)
        array3 = Array(array_traits, array1_values)
        self.assertNotEqual(array1.raw_array, array2.raw_array)
        self.assertEqual(array1.raw_array, array3.raw_array)

    def _test_array_normal(self, array_traits, array_values, expected_bitsize):
        for i in range(8):
            array = Array(array_traits, array_values)

            bitsize = array.bitsizeof(i)
            self.assertEqual(expected_bitsize, bitsize)
            self.assertEqual(i + bitsize, array.initialize_offsets(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            self.assertEqual(0, from_reader.read_bits(i))
            read_array_from_reader = Array.from_reader(array_traits, from_reader, len(array_values))
            self.assertEqual(array, read_array_from_reader, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits)
            read_array.read(reader, len(array_values))
            self.assertEqual(array, read_array, i)

    def _test_array_auto(self, array_traits, array_values, expected_bitsize):
        for i in range(8):
            array = Array(array_traits, array_values, is_auto=True)

            bitsize = array.bitsizeof(i)
            self.assertEqual(expected_bitsize, bitsize, i)
            self.assertEqual(i + bitsize, array.initialize_offsets(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            self.assertEqual(0, from_reader.read_bits(i))
            read_array_from_reader = Array.from_reader(array_traits, from_reader, is_auto=True)
            self.assertEqual(array, read_array_from_reader, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits, is_auto=True)
            read_array.read(reader)
            self.assertEqual(array, read_array, i)

    def _test_array_aligned(self, array_traits, array_values, expected_bitsize):
        for i in range(8):
            array = Array(array_traits, array_values, set_offset_method=ArrayTest._set_offset_method,
                          check_offset_method=ArrayTest._check_offset_method)

            bitsize = array.bitsizeof(i)
            self.assertEqual(alignto(8, i) - i + expected_bitsize, bitsize, i)
            self.assertEqual(i + bitsize, array.initialize_offsets(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            self.assertEqual(0, from_reader.read_bits(i))
            read_array_from_reader = Array.from_reader(array_traits, from_reader, len(array_values),
                                                       set_offset_method=ArrayTest._set_offset_method,
                                                       check_offset_method=ArrayTest._check_offset_method)
            self.assertEqual(array, read_array_from_reader, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits, set_offset_method=ArrayTest._set_offset_method,
                               check_offset_method=ArrayTest._check_offset_method)
            read_array.read(reader, len(array_values))
            self.assertEqual(array, read_array, i)

    def _test_array_aligned_auto(self, array_traits, array_values, expected_bitsize):
        for i in range(8):
            array = Array(array_traits, array_values, is_auto=True,
                          set_offset_method=ArrayTest._set_offset_method,
                          check_offset_method=ArrayTest._check_offset_method)

            bitsize = array.bitsizeof(i)
            self.assertEqual(alignto(8, i) - i + expected_bitsize, bitsize, i)
            self.assertEqual(i + bitsize, array.initialize_offsets(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            self.assertEqual(0, from_reader.read_bits(i))
            read_array_from_reader = Array.from_reader(array_traits, from_reader, is_auto=True,
                                                       set_offset_method=ArrayTest._set_offset_method,
                                                       check_offset_method=ArrayTest._check_offset_method)
            self.assertEqual(array, read_array_from_reader, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits, is_auto=True, set_offset_method=ArrayTest._set_offset_method,
                               check_offset_method=ArrayTest._check_offset_method)
            read_array.read(reader)
            self.assertEqual(array, read_array, i)

    def _test_array_implicit(self, array_traits, array_values, expected_bitsize):
        for i in range(8):
            array = Array(array_traits, array_values, is_implicit=True)

            bitsize = array.bitsizeof(i)
            self.assertEqual(expected_bitsize, bitsize, i)
            self.assertEqual(i + bitsize, array.initialize_offsets(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, from_reader.read_bits(i))
            if array_traits.HAS_BITSIZEOF_CONSTANT:
                read_array_from_reader = Array.from_reader(array_traits, from_reader, is_implicit=True)
                self.assertEqual(array, read_array_from_reader, i)
            else:
                with self.assertRaises(PythonRuntimeException):
                    Array.from_reader(array_traits, from_reader, is_implicit=True)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits, is_implicit=True)
            if array_traits.HAS_BITSIZEOF_CONSTANT:
                read_array.read(reader)
                self.assertEqual(array, read_array, i)
            else:
                with self.assertRaises(PythonRuntimeException):
                    read_array.read(reader)

    def _test_packed_array_normal(self, array_traits, array_values):
        for i in range(8):
            array = Array(array_traits, array_values)

            bitsize = array.bitsizeof_packed(i)
            self.assertEqual(i + bitsize, array.initialize_offsets_packed(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write_packed(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            self.assertEqual(0, from_reader.read_bits(i))
            read_array_from_reader = Array.from_reader_packed(array_traits, from_reader, len(array_values))
            self.assertEqual(array, read_array_from_reader, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits)
            read_array.read_packed(reader, len(array_values))
            self.assertEqual(array, read_array, i)

    def _test_packed_array_auto(self, array_traits, array_values):
        for i in range(8):
            array = Array(array_traits, array_values, is_auto=True)

            bitsize = array.bitsizeof_packed(i)
            self.assertEqual(i + bitsize, array.initialize_offsets_packed(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write_packed(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            self.assertEqual(0, from_reader.read_bits(i))
            read_array_from_reader = Array.from_reader_packed(array_traits, from_reader, is_auto=True)
            self.assertEqual(array, read_array_from_reader, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits, is_auto=True)
            read_array.read_packed(reader)
            self.assertEqual(array, read_array, i)

    def _test_packed_array_aligned(self, array_traits, array_values):
        for i in range(8):
            array = Array(array_traits, array_values, set_offset_method=ArrayTest._set_offset_method,
                          check_offset_method=ArrayTest._check_offset_method)

            bitsize = array.bitsizeof_packed(i)
            self.assertEqual(i + bitsize, array.initialize_offsets_packed(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write_packed(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            self.assertEqual(0, from_reader.read_bits(i))
            read_array_from_reader = Array.from_reader_packed(
                array_traits, from_reader, len(array_values),
                set_offset_method=ArrayTest._set_offset_method,
                check_offset_method=ArrayTest._check_offset_method)
            self.assertEqual(array, read_array_from_reader, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits, set_offset_method=ArrayTest._set_offset_method,
                               check_offset_method=ArrayTest._check_offset_method)
            read_array.read_packed(reader, len(array_values))
            self.assertEqual(array, read_array, i)

    def _test_packed_array_aligned_auto(self, array_traits, array_values):
        for i in range(8):
            array = Array(array_traits, array_values, is_auto=True,
                          set_offset_method=ArrayTest._set_offset_method,
                          check_offset_method=ArrayTest._check_offset_method)

            bitsize = array.bitsizeof_packed(i)
            self.assertEqual(i + bitsize, array.initialize_offsets_packed(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write_packed(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            from_reader = BitStreamReader(writer.byte_array, writer.bitposition)
            self.assertEqual(0, from_reader.read_bits(i))
            read_array_from_reader = Array.from_reader_packed(
                array_traits, from_reader, is_auto=True,
                set_offset_method=ArrayTest._set_offset_method,
                check_offset_method=ArrayTest._check_offset_method
            )
            self.assertEqual(array, read_array_from_reader, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits, is_auto=True, set_offset_method=ArrayTest._set_offset_method,
                               check_offset_method=ArrayTest._check_offset_method)
            read_array.read_packed(reader)
            self.assertEqual(array, read_array, i)

    def _test_packed_array_implicit(self, array_traits, array_values):
        for i in range(8):
            array = Array(array_traits, array_values, is_implicit=True)

            bitsize = array.bitsizeof_packed(i)
            self.assertEqual(i + bitsize, array.initialize_offsets_packed(i), i)

            writer = BitStreamWriter()
            if i > 0:
                writer.write_bits(0, i)
            array.write_packed(writer)
            self.assertEqual(i + bitsize, writer.bitposition, i)

            reader = BitStreamReader(writer.byte_array, writer.bitposition)
            if i > 0:
                self.assertEqual(0, reader.read_bits(i))
            read_array = Array(array_traits, is_implicit=True)
            with self.assertRaises(PythonRuntimeException):
                read_array.read_packed(reader)
