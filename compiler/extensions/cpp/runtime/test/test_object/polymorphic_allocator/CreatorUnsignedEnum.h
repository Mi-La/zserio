/**
 * Automatically generated by Zserio C++ extension version 2.12.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, polymorphicAllocator.
 */

#ifndef TEST_OBJECT_POLYMORPHIC_ALLOCATOR_CREATOR_UNSIGNED_ENUM_H
#define TEST_OBJECT_POLYMORPHIC_ALLOCATOR_CREATOR_UNSIGNED_ENUM_H

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

enum class CreatorUnsignedEnum : uint8_t
{
    ONE = UINT8_C(0),
    TWO = UINT8_C(1)
};

} // namespace polymorphic_allocator
} // namespace test_object

namespace zserio
{

// This is full specialization of enumeration traits and methods for CreatorUnsignedEnum enumeration.
template <>
struct EnumTraits<::test_object::polymorphic_allocator::CreatorUnsignedEnum>
{
    static constexpr ::std::array<const char*, 2> names =
    {{
        "ONE",
        "TWO"
    }};

    static constexpr ::std::array<::test_object::polymorphic_allocator::CreatorUnsignedEnum, 2> values =
    {{
        ::test_object::polymorphic_allocator::CreatorUnsignedEnum::ONE,
        ::test_object::polymorphic_allocator::CreatorUnsignedEnum::TWO
    }};

    static constexpr const char* enumName = "CreatorUnsignedEnum";
};

template <>
const ::zserio::pmr::ITypeInfo& enumTypeInfo<::test_object::polymorphic_allocator::CreatorUnsignedEnum, ::zserio::pmr::PropagatingPolymorphicAllocator<>>();

template <>
::zserio::pmr::IReflectablePtr enumReflectable(::test_object::polymorphic_allocator::CreatorUnsignedEnum value, const ::zserio::pmr::PropagatingPolymorphicAllocator<>& allocator);

template <>
size_t enumToOrdinal<::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

template <>
::test_object::polymorphic_allocator::CreatorUnsignedEnum valueToEnum<::test_object::polymorphic_allocator::CreatorUnsignedEnum>(
        typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorUnsignedEnum>::type rawValue);

template <>
uint32_t enumHashCode<::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

template <>
void initPackingContext<::zserio::DeltaContext, ::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::zserio::DeltaContext& context, ::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

template <>
size_t bitSizeOf<::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

template <>
size_t bitSizeOf<::zserio::DeltaContext, ::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::zserio::DeltaContext& context, ::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

template <>
size_t initializeOffsets<::test_object::polymorphic_allocator::CreatorUnsignedEnum>(size_t bitPosition, ::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

template <>
size_t initializeOffsets<::zserio::DeltaContext, ::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::zserio::DeltaContext& context, size_t bitPosition,
        ::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

template <>
::test_object::polymorphic_allocator::CreatorUnsignedEnum read<::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::zserio::BitStreamReader& in);

template <>
::test_object::polymorphic_allocator::CreatorUnsignedEnum read<::test_object::polymorphic_allocator::CreatorUnsignedEnum, ::zserio::DeltaContext>(::zserio::DeltaContext& context, ::zserio::BitStreamReader& in);

template <>
void write<::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::zserio::BitStreamWriter& out, ::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

template <>
void write<::zserio::DeltaContext, ::test_object::polymorphic_allocator::CreatorUnsignedEnum>(::zserio::DeltaContext& context, ::zserio::BitStreamWriter& out,
        ::test_object::polymorphic_allocator::CreatorUnsignedEnum value);

} // namespace zserio

#endif // TEST_OBJECT_POLYMORPHIC_ALLOCATOR_CREATOR_UNSIGNED_ENUM_H
