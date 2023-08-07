/**
 * Automatically generated by Zserio C++ extension version 2.11.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, polymorhpicAllocator.
 */

#ifndef TEST_OBJECT_POLYMORPHIC_ALLOCATOR_REFLECTABLE_ENUM_H
#define TEST_OBJECT_POLYMORPHIC_ALLOCATOR_REFLECTABLE_ENUM_H

#include <array>

#include <zserio/Enums.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/DeltaContext.h>
#include <zserio/pmr/ITypeInfo.h>
#include <zserio/pmr/IReflectable.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Types.h>

namespace test_object
{
namespace polymorphic_allocator
{

enum class ReflectableEnum : int8_t
{
    VALUE1 = INT8_C(-1),
    VALUE2 = INT8_C(0),
    VALUE3 = INT8_C(1)
};

} // namespace polymorphic_allocator
} // namespace test_object

namespace zserio
{

// This is full specialization of enumeration traits and methods for ReflectableEnum enumeration.
template <>
struct EnumTraits<::test_object::polymorphic_allocator::ReflectableEnum>
{
    static constexpr ::std::array<const char*, 3> names =
    {{
        "VALUE1",
        "VALUE2",
        "VALUE3"
    }};

    static constexpr ::std::array<::test_object::polymorphic_allocator::ReflectableEnum, 3> values =
    {{
        ::test_object::polymorphic_allocator::ReflectableEnum::VALUE1,
        ::test_object::polymorphic_allocator::ReflectableEnum::VALUE2,
        ::test_object::polymorphic_allocator::ReflectableEnum::VALUE3
    }};

    static constexpr const char* enumName = "ReflectableEnum";
};

template <>
const ::zserio::pmr::ITypeInfo& enumTypeInfo<::test_object::polymorphic_allocator::ReflectableEnum, ::zserio::pmr::PropagatingPolymorphicAllocator<>>();

template <>
::zserio::pmr::IReflectablePtr enumReflectable(::test_object::polymorphic_allocator::ReflectableEnum value, const ::zserio::pmr::PropagatingPolymorphicAllocator<>& allocator);

template <>
size_t enumToOrdinal<::test_object::polymorphic_allocator::ReflectableEnum>(::test_object::polymorphic_allocator::ReflectableEnum value);

template <>
::test_object::polymorphic_allocator::ReflectableEnum valueToEnum<::test_object::polymorphic_allocator::ReflectableEnum>(
        typename ::std::underlying_type<::test_object::polymorphic_allocator::ReflectableEnum>::type rawValue);

template <>
uint32_t enumHashCode<::test_object::polymorphic_allocator::ReflectableEnum>(::test_object::polymorphic_allocator::ReflectableEnum value);

template <>
void initPackingContext<::zserio::DeltaContext, ::test_object::polymorphic_allocator::ReflectableEnum>(::zserio::DeltaContext& context, ::test_object::polymorphic_allocator::ReflectableEnum value);

template <>
size_t bitSizeOf<::test_object::polymorphic_allocator::ReflectableEnum>(::test_object::polymorphic_allocator::ReflectableEnum value);

template <>
size_t bitSizeOf<::zserio::DeltaContext, ::test_object::polymorphic_allocator::ReflectableEnum>(::zserio::DeltaContext& context, ::test_object::polymorphic_allocator::ReflectableEnum value);

template <>
size_t initializeOffsets<::test_object::polymorphic_allocator::ReflectableEnum>(size_t bitPosition, ::test_object::polymorphic_allocator::ReflectableEnum value);

template <>
size_t initializeOffsets<::zserio::DeltaContext, ::test_object::polymorphic_allocator::ReflectableEnum>(::zserio::DeltaContext& context, size_t bitPosition,
        ::test_object::polymorphic_allocator::ReflectableEnum value);

template <>
::test_object::polymorphic_allocator::ReflectableEnum read<::test_object::polymorphic_allocator::ReflectableEnum>(::zserio::BitStreamReader& in);

template <>
::test_object::polymorphic_allocator::ReflectableEnum read<::test_object::polymorphic_allocator::ReflectableEnum, ::zserio::DeltaContext>(::zserio::DeltaContext& context, ::zserio::BitStreamReader& in);

template <>
void write<::test_object::polymorphic_allocator::ReflectableEnum>(::zserio::BitStreamWriter& out, ::test_object::polymorphic_allocator::ReflectableEnum value);

template <>
void write<::zserio::DeltaContext, ::test_object::polymorphic_allocator::ReflectableEnum>(::zserio::DeltaContext& context, ::zserio::BitStreamWriter& out,
        ::test_object::polymorphic_allocator::ReflectableEnum value);

} // namespace zserio

#endif // TEST_OBJECT_POLYMORPHIC_ALLOCATOR_REFLECTABLE_ENUM_H
