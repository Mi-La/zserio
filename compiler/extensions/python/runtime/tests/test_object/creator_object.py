# Automatically generated by Zserio Python extension version 2.9.0-pre1.
# Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode

from __future__ import annotations

import typing
import zserio

import test_object.creator_nested

class CreatorObject:
    def __init__(
            self,
            value_: int = int(),
            nested_: typing.Union[test_object.creator_nested.CreatorNested, None] = None,
            text_: str = str(),
            nested_array_: typing.List[test_object.creator_nested.CreatorNested] = None,
            text_array_: typing.List[str] = None,
            extern_array_: typing.Optional[typing.List[zserio.bitbuffer.BitBuffer]] = None,
            bytes_array_: typing.Optional[typing.List[bytearray]] = None,
            optional_bool_: typing.Optional[bool] = None,
            optional_nested_: typing.Optional[test_object.creator_nested.CreatorNested] = None) -> None:
        self._value_ = value_
        self._nested_ = nested_
        self._text_ = text_
        self._nested_array_ = zserio.array.Array(zserio.array.ObjectArrayTraits(self._element_creator_nested_array, self._packed_element_creator_nested_array, test_object.creator_nested.CreatorNested.create_packing_context), nested_array_, is_auto=True)
        self._text_array_ = zserio.array.Array(zserio.array.StringArrayTraits(), text_array_, is_auto=True)
        if extern_array_ is None:
            self._extern_array_ = None
        else:
            self._extern_array_ = zserio.array.Array(zserio.array.BitBufferArrayTraits(), extern_array_, is_auto=True)
        if bytes_array_ is None:
            self._bytes_array_ = None
        else:
            self._bytes_array_ = zserio.array.Array(zserio.array.BytesArrayTraits(), bytes_array_, is_auto=True)
        self._optional_bool_ = optional_bool_
        self._optional_nested_ = optional_nested_

    @classmethod
    def from_reader(
            cls: typing.Type['CreatorObject'],
            zserio_reader: zserio.BitStreamReader) -> 'CreatorObject':
        instance = cls()
        instance.read(zserio_reader)

        return instance

    @classmethod
    def from_reader_packed(
            cls: typing.Type['CreatorObject'],
            zserio_context_node: zserio.array.PackingContextNode,
            zserio_reader: zserio.BitStreamReader) -> 'CreatorObject':
        instance = cls()
        instance.read_packed(zserio_context_node, zserio_reader)

        return instance

    @staticmethod
    def type_info() -> zserio.typeinfo.TypeInfo:
        field_list: typing.List[zserio.typeinfo.MemberInfo] = [
            zserio.typeinfo.MemberInfo(
                'value', zserio.typeinfo.TypeInfo('uint32', int),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'value'
                }
            ),
            zserio.typeinfo.MemberInfo(
                'nested', test_object.creator_nested.CreatorNested.type_info(),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'nested',
                    zserio.typeinfo.MemberAttribute.TYPE_ARGUMENTS : [(lambda self, zserio_index: self.value)]
                }
            ),
            zserio.typeinfo.MemberInfo(
                'text', zserio.typeinfo.TypeInfo('string', str),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'text'
                }
            ),
            zserio.typeinfo.MemberInfo(
                'nestedArray', test_object.creator_nested.CreatorNested.type_info(),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'nested_array',
                    zserio.typeinfo.MemberAttribute.ARRAY_LENGTH : None,
                    zserio.typeinfo.MemberAttribute.TYPE_ARGUMENTS : [(lambda self, zserio_index: self.value)]
                }
            ),
            zserio.typeinfo.MemberInfo(
                'textArray', zserio.typeinfo.TypeInfo('string', str),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'text_array',
                    zserio.typeinfo.MemberAttribute.ARRAY_LENGTH : None
                }
            ),
            zserio.typeinfo.MemberInfo(
                'externArray', zserio.typeinfo.TypeInfo('extern', zserio.bitbuffer.BitBuffer),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'extern_array',
                    zserio.typeinfo.MemberAttribute.ARRAY_LENGTH : None,
                    zserio.typeinfo.MemberAttribute.OPTIONAL : None,
                    zserio.typeinfo.MemberAttribute.IS_USED_INDICATOR_NAME : 'is_extern_array_used',
                    zserio.typeinfo.MemberAttribute.IS_SET_INDICATOR_NAME : 'is_extern_array_set'
                }
            ),
            zserio.typeinfo.MemberInfo(
                'bytesArray', zserio.typeinfo.TypeInfo('bytes', bytearray),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'bytes_array',
                    zserio.typeinfo.MemberAttribute.ARRAY_LENGTH : None,
                    zserio.typeinfo.MemberAttribute.OPTIONAL : None,
                    zserio.typeinfo.MemberAttribute.IS_USED_INDICATOR_NAME : 'is_bytes_array_used',
                    zserio.typeinfo.MemberAttribute.IS_SET_INDICATOR_NAME : 'is_bytes_array_set'
                }
            ),
            zserio.typeinfo.MemberInfo(
                'optionalBool', zserio.typeinfo.TypeInfo('bool', bool),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'optional_bool',
                    zserio.typeinfo.MemberAttribute.OPTIONAL : None,
                    zserio.typeinfo.MemberAttribute.IS_USED_INDICATOR_NAME : 'is_optional_bool_used',
                    zserio.typeinfo.MemberAttribute.IS_SET_INDICATOR_NAME : 'is_optional_bool_set'
                }
            ),
            zserio.typeinfo.MemberInfo(
                'optionalNested', test_object.creator_nested.CreatorNested.type_info(),
                attributes={
                    zserio.typeinfo.MemberAttribute.PROPERTY_NAME : 'optional_nested',
                    zserio.typeinfo.MemberAttribute.TYPE_ARGUMENTS : [(lambda self, zserio_index: self.value)],
                    zserio.typeinfo.MemberAttribute.OPTIONAL : None,
                    zserio.typeinfo.MemberAttribute.IS_USED_INDICATOR_NAME : 'is_optional_nested_used',
                    zserio.typeinfo.MemberAttribute.IS_SET_INDICATOR_NAME : 'is_optional_nested_set'
                }
            )
        ]
        attribute_list = {
            zserio.typeinfo.TypeAttribute.FIELDS : field_list
        }

        return zserio.typeinfo.TypeInfo("test_object.CreatorObject", CreatorObject, attributes=attribute_list)

    def __eq__(self, other: object) -> bool:
        if isinstance(other, CreatorObject):
            return ((self._value_ == other._value_) and
                    (self._nested_ == other._nested_) and
                    (self._text_ == other._text_) and
                    (self._nested_array_ == other._nested_array_) and
                    (self._text_array_ == other._text_array_) and
                    (not other.is_extern_array_used() if not self.is_extern_array_used() else (self._extern_array_ == other._extern_array_)) and
                    (not other.is_bytes_array_used() if not self.is_bytes_array_used() else (self._bytes_array_ == other._bytes_array_)) and
                    (not other.is_optional_bool_used() if not self.is_optional_bool_used() else (self._optional_bool_ == other._optional_bool_)) and
                    (not other.is_optional_nested_used() if not self.is_optional_nested_used() else (self._optional_nested_ == other._optional_nested_)))

        return False

    def __hash__(self) -> int:
        result = zserio.hashcode.HASH_SEED
        result = zserio.hashcode.calc_hashcode_int32(result, self._value_)
        result = zserio.hashcode.calc_hashcode_object(result, self._nested_)
        result = zserio.hashcode.calc_hashcode_string(result, self._text_)
        result = zserio.hashcode.calc_hashcode_object(result, self._nested_array_)
        result = zserio.hashcode.calc_hashcode_object(result, self._text_array_)
        if self.is_extern_array_used():
            result = zserio.hashcode.calc_hashcode_object(result, self._extern_array_)
        if self.is_bytes_array_used():
            result = zserio.hashcode.calc_hashcode_object(result, self._bytes_array_)
        if self.is_optional_bool_used():
            result = zserio.hashcode.calc_hashcode_bool(result, self._optional_bool_)
        if self.is_optional_nested_used():
            result = zserio.hashcode.calc_hashcode_object(result, self._optional_nested_)

        return result

    @property
    def value(self) -> int:
        return self._value_

    @value.setter
    def value(self, value_: int) -> None:
        self._value_ = value_

    @property
    def nested(self) -> typing.Union[test_object.creator_nested.CreatorNested, None]:
        return self._nested_

    @nested.setter
    def nested(self, nested_: typing.Union[test_object.creator_nested.CreatorNested, None]) -> None:
        self._nested_ = nested_

    @property
    def text(self) -> str:
        return self._text_

    @text.setter
    def text(self, text_: str) -> None:
        self._text_ = text_

    @property
    def nested_array(self) -> typing.List[test_object.creator_nested.CreatorNested]:
        return self._nested_array_.raw_array

    @nested_array.setter
    def nested_array(self, nested_array_: typing.List[test_object.creator_nested.CreatorNested]) -> None:
        self._nested_array_ = zserio.array.Array(zserio.array.ObjectArrayTraits(self._element_creator_nested_array, self._packed_element_creator_nested_array, test_object.creator_nested.CreatorNested.create_packing_context), nested_array_, is_auto=True)

    @property
    def text_array(self) -> typing.List[str]:
        return self._text_array_.raw_array

    @text_array.setter
    def text_array(self, text_array_: typing.List[str]) -> None:
        self._text_array_ = zserio.array.Array(zserio.array.StringArrayTraits(), text_array_, is_auto=True)

    @property
    def extern_array(self) -> typing.Optional[typing.List[zserio.bitbuffer.BitBuffer]]:
        return None if self._extern_array_ is None else self._extern_array_.raw_array

    @extern_array.setter
    def extern_array(self, extern_array_: typing.Optional[typing.List[zserio.bitbuffer.BitBuffer]]) -> None:
        if extern_array_ is None:
            self._extern_array_ = None
        else:
            self._extern_array_ = zserio.array.Array(zserio.array.BitBufferArrayTraits(), extern_array_, is_auto=True)

    def is_extern_array_used(self) -> bool:
        return self.is_extern_array_set()

    def is_extern_array_set(self) -> bool:
        return not self._extern_array_ is None

    def reset_extern_array(self) -> None:
        self._extern_array_ = None

    @property
    def bytes_array(self) -> typing.Optional[typing.List[bytearray]]:
        return None if self._bytes_array_ is None else self._bytes_array_.raw_array

    @bytes_array.setter
    def bytes_array(self, bytes_array_: typing.Optional[typing.List[bytearray]]) -> None:
        if bytes_array_ is None:
            self._bytes_array_ = None
        else:
            self._bytes_array_ = zserio.array.Array(zserio.array.BytesArrayTraits(), bytes_array_, is_auto=True)

    def is_bytes_array_used(self) -> bool:
        return self.is_bytes_array_set()

    def is_bytes_array_set(self) -> bool:
        return not self._bytes_array_ is None

    def reset_bytes_array(self) -> None:
        self._bytes_array_ = None

    @property
    def optional_bool(self) -> typing.Optional[bool]:
        return self._optional_bool_

    @optional_bool.setter
    def optional_bool(self, optional_bool_: typing.Optional[bool]) -> None:
        self._optional_bool_ = optional_bool_

    def is_optional_bool_used(self) -> bool:
        return self.is_optional_bool_set()

    def is_optional_bool_set(self) -> bool:
        return not self._optional_bool_ is None

    def reset_optional_bool(self) -> None:
        self._optional_bool_ = None

    @property
    def optional_nested(self) -> typing.Optional[test_object.creator_nested.CreatorNested]:
        return self._optional_nested_

    @optional_nested.setter
    def optional_nested(self, optional_nested_: typing.Optional[test_object.creator_nested.CreatorNested]) -> None:
        self._optional_nested_ = optional_nested_

    def is_optional_nested_used(self) -> bool:
        return self.is_optional_nested_set()

    def is_optional_nested_set(self) -> bool:
        return not self._optional_nested_ is None

    def reset_optional_nested(self) -> None:
        self._optional_nested_ = None

    @staticmethod
    def create_packing_context(zserio_context_node: zserio.array.PackingContextNode) -> None:
        zserio_context_node.create_child().create_context()
        test_object.creator_nested.CreatorNested.create_packing_context(zserio_context_node.create_child())
        zserio_context_node.create_child()
        zserio_context_node.create_child()
        zserio_context_node.create_child()
        zserio_context_node.create_child()
        zserio_context_node.create_child()
        zserio_context_node.create_child()
        test_object.creator_nested.CreatorNested.create_packing_context(zserio_context_node.create_child())

    def init_packing_context(self, zserio_context_node: zserio.array.PackingContextNode) -> None:
        zserio_context_node.children[0].context.init(zserio.array.BitFieldArrayTraits(32), self._value_)
        self._nested_.init_packing_context(zserio_context_node.children[1])
        if self.is_optional_nested_used():
            self._optional_nested_.init_packing_context(zserio_context_node.children[8])

    def bitsizeof(self, bitposition: int = 0) -> int:
        end_bitposition = bitposition
        end_bitposition += 32
        end_bitposition += self._nested_.bitsizeof(end_bitposition)
        end_bitposition += zserio.bitsizeof.bitsizeof_string(self._text_)
        end_bitposition += self._nested_array_.bitsizeof(end_bitposition)
        end_bitposition += self._text_array_.bitsizeof(end_bitposition)
        end_bitposition += 1
        if self.is_extern_array_used():
            end_bitposition += self._extern_array_.bitsizeof(end_bitposition)
        end_bitposition += 1
        if self.is_bytes_array_used():
            end_bitposition += self._bytes_array_.bitsizeof(end_bitposition)
        end_bitposition += 1
        if self.is_optional_bool_used():
            end_bitposition += 1
        end_bitposition += 1
        if self.is_optional_nested_used():
            end_bitposition += self._optional_nested_.bitsizeof(end_bitposition)

        return end_bitposition - bitposition

    def bitsizeof_packed(self, zserio_context_node: zserio.array.PackingContextNode,
                         bitposition: int = 0) -> int:
        end_bitposition = bitposition
        end_bitposition += zserio_context_node.children[0].context.bitsizeof(zserio.array.BitFieldArrayTraits(32), self._value_)
        end_bitposition += self._nested_.bitsizeof_packed(zserio_context_node.children[1], end_bitposition)
        end_bitposition += zserio.bitsizeof.bitsizeof_string(self._text_)
        end_bitposition += self._nested_array_.bitsizeof_packed(end_bitposition)
        end_bitposition += self._text_array_.bitsizeof(end_bitposition)
        end_bitposition += 1
        if self.is_extern_array_used():
            end_bitposition += self._extern_array_.bitsizeof(end_bitposition)
        end_bitposition += 1
        if self.is_bytes_array_used():
            end_bitposition += self._bytes_array_.bitsizeof(end_bitposition)
        end_bitposition += 1
        if self.is_optional_bool_used():
            end_bitposition += 1
        end_bitposition += 1
        if self.is_optional_nested_used():
            end_bitposition += self._optional_nested_.bitsizeof_packed(zserio_context_node.children[8], end_bitposition)

        return end_bitposition - bitposition

    def initialize_offsets(self, bitposition: int = 0) -> int:
        end_bitposition = bitposition
        end_bitposition += 32
        end_bitposition = self._nested_.initialize_offsets(end_bitposition)
        end_bitposition += zserio.bitsizeof.bitsizeof_string(self._text_)
        end_bitposition = self._nested_array_.initialize_offsets(end_bitposition)
        end_bitposition = self._text_array_.initialize_offsets(end_bitposition)
        end_bitposition += 1
        if self.is_extern_array_used():
            end_bitposition = self._extern_array_.initialize_offsets(end_bitposition)
        end_bitposition += 1
        if self.is_bytes_array_used():
            end_bitposition = self._bytes_array_.initialize_offsets(end_bitposition)
        end_bitposition += 1
        if self.is_optional_bool_used():
            end_bitposition += 1
        end_bitposition += 1
        if self.is_optional_nested_used():
            end_bitposition = self._optional_nested_.initialize_offsets(end_bitposition)

        return end_bitposition

    def initialize_offsets_packed(self, zserio_context_node: zserio.array.PackingContextNode,
                                  bitposition: int) -> int:
        end_bitposition = bitposition
        end_bitposition += zserio_context_node.children[0].context.bitsizeof(zserio.array.BitFieldArrayTraits(32), self._value_)
        end_bitposition = self._nested_.initialize_offsets_packed(zserio_context_node.children[1], end_bitposition)
        end_bitposition += zserio.bitsizeof.bitsizeof_string(self._text_)
        end_bitposition = self._nested_array_.initialize_offsets_packed(end_bitposition)
        end_bitposition = self._text_array_.initialize_offsets(end_bitposition)
        end_bitposition += 1
        if self.is_extern_array_used():
            end_bitposition = self._extern_array_.initialize_offsets(end_bitposition)
        end_bitposition += 1
        if self.is_bytes_array_used():
            end_bitposition = self._bytes_array_.initialize_offsets(end_bitposition)
        end_bitposition += 1
        if self.is_optional_bool_used():
            end_bitposition += 1
        end_bitposition += 1
        if self.is_optional_nested_used():
            end_bitposition = self._optional_nested_.initialize_offsets_packed(zserio_context_node.children[8], end_bitposition)

        return end_bitposition

    def read(self, zserio_reader: zserio.BitStreamReader) -> None:
        self._value_ = zserio_reader.read_bits(32)
        self._nested_ = test_object.creator_nested.CreatorNested.from_reader(zserio_reader, self.value)
        self._text_ = zserio_reader.read_string()
        self._nested_array_ = zserio.array.Array.from_reader(zserio.array.ObjectArrayTraits(self._element_creator_nested_array, self._packed_element_creator_nested_array, test_object.creator_nested.CreatorNested.create_packing_context), zserio_reader, is_auto=True)
        self._text_array_ = zserio.array.Array.from_reader(zserio.array.StringArrayTraits(), zserio_reader, is_auto=True)
        if zserio_reader.read_bool():
            self._extern_array_ = zserio.array.Array.from_reader(zserio.array.BitBufferArrayTraits(), zserio_reader, is_auto=True)
        if zserio_reader.read_bool():
            self._bytes_array_ = zserio.array.Array.from_reader(zserio.array.BytesArrayTraits(), zserio_reader, is_auto=True)
        if zserio_reader.read_bool():
            self._optional_bool_ = zserio_reader.read_bool()
        if zserio_reader.read_bool():
            self._optional_nested_ = test_object.creator_nested.CreatorNested.from_reader(zserio_reader, self.value)

    def read_packed(self, zserio_context_node: zserio.array.PackingContextNode,
                    zserio_reader: zserio.BitStreamReader) -> None:
        self._value_ = zserio_context_node.children[0].context.read(zserio.array.BitFieldArrayTraits(32), zserio_reader)

        self._nested_ = test_object.creator_nested.CreatorNested.from_reader_packed(zserio_context_node.children[1], zserio_reader, self.value)

        self._text_ = zserio_reader.read_string()

        self._nested_array_ = zserio.array.Array.from_reader_packed(zserio.array.ObjectArrayTraits(self._element_creator_nested_array, self._packed_element_creator_nested_array, test_object.creator_nested.CreatorNested.create_packing_context), zserio_reader, is_auto=True)

        self._text_array_ = zserio.array.Array.from_reader(zserio.array.StringArrayTraits(), zserio_reader, is_auto=True)

        if zserio_reader.read_bool():
            self._extern_array_ = zserio.array.Array.from_reader(zserio.array.BitBufferArrayTraits(), zserio_reader, is_auto=True)

        if zserio_reader.read_bool():
            self._bytes_array_ = zserio.array.Array.from_reader(zserio.array.BytesArrayTraits(), zserio_reader, is_auto=True)

        if zserio_reader.read_bool():
            self._optional_bool_ = zserio_reader.read_bool()

        if zserio_reader.read_bool():
            self._optional_nested_ = test_object.creator_nested.CreatorNested.from_reader_packed(zserio_context_node.children[8], zserio_reader, self.value)

    def write(self, zserio_writer: zserio.BitStreamWriter) -> None:
        zserio_writer.write_bits(self._value_, 32)

        # check parameters
        if self._nested_.param != (self.value):
            raise zserio.PythonRuntimeException("Wrong parameter param for field CreatorObject.nested: "
                                                f"{self._nested_.param} != {self.value}!")
        self._nested_.write(zserio_writer)

        zserio_writer.write_string(self._text_)

        self._nested_array_.write(zserio_writer)

        self._text_array_.write(zserio_writer)

        if self.is_extern_array_used():
            zserio_writer.write_bool(True)
            self._extern_array_.write(zserio_writer)
        else:
            zserio_writer.write_bool(False)

        if self.is_bytes_array_used():
            zserio_writer.write_bool(True)
            self._bytes_array_.write(zserio_writer)
        else:
            zserio_writer.write_bool(False)

        if self.is_optional_bool_used():
            zserio_writer.write_bool(True)
            zserio_writer.write_bool(self._optional_bool_)
        else:
            zserio_writer.write_bool(False)

        if self.is_optional_nested_used():
            zserio_writer.write_bool(True)
            # check parameters
            if self._optional_nested_.param != (self.value):
                raise zserio.PythonRuntimeException("Wrong parameter param for field CreatorObject.optionalNested: "
                                                    f"{self._optional_nested_.param} != {self.value}!")
            self._optional_nested_.write(zserio_writer)
        else:
            zserio_writer.write_bool(False)

    def write_packed(self, zserio_context_node: zserio.array.PackingContextNode,
                     zserio_writer: zserio.BitStreamWriter) -> None:
        zserio_context_node.children[0].context.write(zserio.array.BitFieldArrayTraits(32), zserio_writer, self._value_)

        # check parameters
        if self._nested_.param != (self.value):
            raise zserio.PythonRuntimeException("Wrong parameter param for field CreatorObject.nested: "
                                                f"{self._nested_.param} != {self.value}!")
        self._nested_.write_packed(zserio_context_node.children[1], zserio_writer)

        zserio_writer.write_string(self._text_)

        self._nested_array_.write_packed(zserio_writer)

        self._text_array_.write(zserio_writer)

        if self.is_extern_array_used():
            zserio_writer.write_bool(True)
            self._extern_array_.write(zserio_writer)
        else:
            zserio_writer.write_bool(False)

        if self.is_bytes_array_used():
            zserio_writer.write_bool(True)
            self._bytes_array_.write(zserio_writer)
        else:
            zserio_writer.write_bool(False)

        if self.is_optional_bool_used():
            zserio_writer.write_bool(True)
            zserio_writer.write_bool(self._optional_bool_)
        else:
            zserio_writer.write_bool(False)

        if self.is_optional_nested_used():
            zserio_writer.write_bool(True)
            # check parameters
            if self._optional_nested_.param != (self.value):
                raise zserio.PythonRuntimeException("Wrong parameter param for field CreatorObject.optionalNested: "
                                                    f"{self._optional_nested_.param} != {self.value}!")
            self._optional_nested_.write_packed(zserio_context_node.children[8], zserio_writer)
        else:
            zserio_writer.write_bool(False)

    def _element_creator_nested_array(self, zserio_reader: zserio.BitStreamReader, zserio_index: int) -> test_object.creator_nested.CreatorNested:
        del zserio_index
        return test_object.creator_nested.CreatorNested.from_reader(zserio_reader, self.value)

    def _packed_element_creator_nested_array(
            self, zserio_context_node: zserio.array.PackingContextNode,
            zserio_reader: zserio.BitStreamReader, zserio_index: int) -> test_object.creator_nested.CreatorNested:
        del zserio_index
        return test_object.creator_nested.CreatorNested.from_reader_packed(zserio_context_node, zserio_reader, self.value)