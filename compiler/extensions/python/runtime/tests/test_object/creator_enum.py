# Automatically generated by Zserio Python generator version 1.0.0 using Zserio core 2.12.0.
# Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode

from __future__ import annotations

import typing
import zserio

class CreatorEnum(zserio.Enum):
    ONE = 0
    TWO = 1
    MINUS_ONE = -1

    @classmethod
    def from_name(cls: typing.Type['CreatorEnum'], item_name: str) -> 'CreatorEnum':
        if item_name == 'ONE':
            item = CreatorEnum.ONE
        elif item_name == 'TWO':
            item = CreatorEnum.TWO
        elif item_name == 'MINUS_ONE':
            item = CreatorEnum.MINUS_ONE
        else:
            raise zserio.PythonRuntimeException(f"Enum item '{item_name}' doesn't exist in enum 'CreatorEnum'!")

        return item

    @classmethod
    def from_reader(cls: typing.Type['CreatorEnum'], reader: zserio.BitStreamReader) -> 'CreatorEnum':
        return cls(reader.read_signed_bits(8))

    @staticmethod
    def type_info():
        attribute_list = {
            zserio.typeinfo.TypeAttribute.UNDERLYING_TYPE : zserio.typeinfo.TypeInfo('int8', int),
            zserio.typeinfo.TypeAttribute.ENUM_ITEMS: [
                zserio.typeinfo.ItemInfo('ONE', CreatorEnum.ONE, False, False),
                zserio.typeinfo.ItemInfo('TWO', CreatorEnum.TWO, False, False),
                zserio.typeinfo.ItemInfo('MinusOne', CreatorEnum.MINUS_ONE, False, False)
            ]
        }

        return zserio.typeinfo.TypeInfo('test_object.CreatorEnum', CreatorEnum, attributes=attribute_list)

    def __hash__(self) -> int:
        result = zserio.hashcode.HASH_SEED
        result = zserio.hashcode.calc_hashcode_int32(result, self.value)
        return result

    def bitsizeof(self, _bitposition: int = 0) -> int:
        return 8

    def initialize_offsets(self, bitposition: int = 0) -> int:
        return bitposition + self.bitsizeof(bitposition)

    def write(self, writer: zserio.BitStreamWriter) -> None:
        writer.write_signed_bits(self.value, 8)
