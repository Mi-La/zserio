# Automatically generated by Zserio Python generator version 1.0.0 using Zserio core 2.12.0.
# Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode

from __future__ import annotations

import typing
import zserio

class WalkerNested:
    def __init__(
            self,
            text_: str = str()) -> None:
        self._text_ = text_

    @classmethod
    def from_reader(
            cls: typing.Type['WalkerNested'],
            zserio_reader: zserio.BitStreamReader) -> 'WalkerNested':
        self = object.__new__(cls)

        self.read(zserio_reader)

        return self

    @staticmethod
    def type_info() -> zserio.typeinfo.TypeInfo:
        field_list: typing.List[zserio.typeinfo.MemberInfo] = [
            zserio.typeinfo.MemberInfo(
                'text', zserio.typeinfo.TypeInfo('string', str),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'text'
                }
            )
        ]
        attribute_list = {
            zserio.typeinfo.TypeAttribute.FIELDS : field_list
        }

        return zserio.typeinfo.TypeInfo("test_object.WalkerNested", WalkerNested, attributes=attribute_list)

    def __eq__(self, other: object) -> bool:
        if isinstance(other, WalkerNested):
            return (self._text_ == other._text_)

        return False

    def __hash__(self) -> int:
        result = zserio.hashcode.HASH_SEED
        result = zserio.hashcode.calc_hashcode_string(result, self._text_)

        return result

    @property
    def text(self) -> str:
        return self._text_

    @text.setter
    def text(self, text_: str) -> None:
        self._text_ = text_

    def bitsizeof(self, bitposition: int = 0) -> int:
        end_bitposition = bitposition
        end_bitposition += zserio.bitsizeof.bitsizeof_string(self._text_)

        return end_bitposition - bitposition

    def initialize_offsets(self, bitposition: int = 0) -> int:
        end_bitposition = bitposition
        end_bitposition += zserio.bitsizeof.bitsizeof_string(self._text_)

        return end_bitposition

    def read(self, zserio_reader: zserio.BitStreamReader) -> None:
        self._text_ = zserio_reader.read_string()

    def write(self, zserio_writer: zserio.BitStreamWriter) -> None:
        zserio_writer.write_string(self._text_)
