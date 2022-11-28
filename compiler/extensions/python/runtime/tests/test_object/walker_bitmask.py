# Automatically generated by Zserio Python extension version 2.9.0-pre1.
# Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode

from __future__ import annotations

import typing
import zserio

class WalkerBitmask:
    def __init__(self) -> None:
        self._value = 0

    @classmethod
    def from_value(cls: typing.Type['WalkerBitmask'], value: int) -> 'WalkerBitmask':
        if value < 0 or value > 4294967295:
            raise zserio.PythonRuntimeException(f"Value for bitmask 'WalkerBitmask' out of bounds: {value}!")

        instance = cls()
        instance._value = value
        return instance

    @classmethod
    def from_reader(cls: typing.Type['WalkerBitmask'], reader: zserio.BitStreamReader) -> 'WalkerBitmask':
        instance = cls()
        instance._value = reader.read_bits(32)
        return instance

    @classmethod
    def from_reader_packed(cls: typing.Type['WalkerBitmask'],
                           context_node: zserio.array.PackingContextNode,
                           reader: zserio.BitStreamReader) -> 'WalkerBitmask':
        instance = cls()
        instance._value = context_node.context.read(zserio.array.BitFieldArrayTraits(32), reader)
        return instance

    @staticmethod
    def type_info():
        attribute_list = {
            zserio.typeinfo.TypeAttribute.UNDERLYING_TYPE : zserio.typeinfo.TypeInfo('uint32', int),
            zserio.typeinfo.TypeAttribute.BITMASK_VALUES: [
                zserio.typeinfo.ItemInfo('ZERO', WalkerBitmask.Values.ZERO)
            ]
        }

        return zserio.typeinfo.TypeInfo('test_object.WalkerBitmask', WalkerBitmask, attributes=attribute_list)

    def __eq__(self, other: object) -> bool:
        if isinstance(other, WalkerBitmask):
            return self._value == other._value

        return False

    def __hash__(self) -> int:
        result = zserio.hashcode.HASH_SEED
        result = zserio.hashcode.calc_hashcode_int32(result, self._value)
        return result

    def __str__(self) -> str:
        result = ""

        if (self & WalkerBitmask.Values.ZERO) == WalkerBitmask.Values.ZERO:
            result += "ZERO" if not result else " | ZERO"

        return str(self._value) + "[" + result + "]"

    def __or__(self, other: 'WalkerBitmask') -> 'WalkerBitmask':
        return WalkerBitmask.from_value(self._value | other._value)

    def __and__(self, other: 'WalkerBitmask') -> 'WalkerBitmask':
        return WalkerBitmask.from_value(self._value & other._value)

    def __xor__(self, other: 'WalkerBitmask') -> 'WalkerBitmask':
        return WalkerBitmask.from_value(self._value ^ other._value)

    def __invert__(self) -> 'WalkerBitmask':
        return WalkerBitmask.from_value(~self._value & 4294967295)

    @staticmethod
    def create_packing_context(context_node: zserio.array.PackingContextNode) -> None:
        context_node.create_context()

    def init_packing_context(self, context_node: zserio.array.PackingContextNode) -> None:
        context_node.context.init(zserio.array.BitFieldArrayTraits(32),
                                  self._value)

    def bitsizeof(self, _bitposition: int = 0) -> int:
        return 32

    def bitsizeof_packed(self, context_node: zserio.array.PackingContextNode,
                         _bitposition: int) -> int:
        return context_node.context.bitsizeof(zserio.array.BitFieldArrayTraits(32),
                                              self._value)

    def initialize_offsets(self, bitposition: int = 0) -> int:
        return bitposition + self.bitsizeof(bitposition)

    def initialize_offsets_packed(self, context_node: zserio.array.PackingContextNode,
                                  bitposition: int) -> int:
        return bitposition + self.bitsizeof_packed(context_node, bitposition)

    def write(self, writer: zserio.BitStreamWriter) -> None:
        writer.write_bits(self._value, 32)

    def write_packed(self, context_node: zserio.array.PackingContextNode,
                     writer: zserio.BitStreamWriter) -> None:
        context_node.context.write(zserio.array.BitFieldArrayTraits(32), writer, self._value)

    @property
    def value(self) -> int:
        return self._value

    class Values:
        ZERO: 'WalkerBitmask' = None

WalkerBitmask.Values.ZERO = WalkerBitmask.from_value(1)
