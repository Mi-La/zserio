/**
 * Automatically generated by Zserio C++ extension version 2.11.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, polymorphicAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/TypeInfo.h>
#include <zserio/pmr/AnyHolder.h>
#include <zserio/pmr/Reflectable.h>

#include <test_object/polymorphic_allocator/CreatorEnum.h>

namespace zserio
{

// This is full specialization of enumeration traits and methods for CreatorEnum enumeration.
constexpr ::std::array<const char*, 3> EnumTraits<::test_object::polymorphic_allocator::CreatorEnum>::names;
constexpr ::std::array<::test_object::polymorphic_allocator::CreatorEnum, 3> EnumTraits<::test_object::polymorphic_allocator::CreatorEnum>::values;
constexpr const char* EnumTraits<::test_object::polymorphic_allocator::CreatorEnum>::enumName;

template <>
const ::zserio::pmr::ITypeInfo& enumTypeInfo<::test_object::polymorphic_allocator::CreatorEnum, ::zserio::pmr::PropagatingPolymorphicAllocator<>>()
{
    using allocator_type = ::zserio::pmr::PropagatingPolymorphicAllocator<>;

    static const ::zserio::Span<::zserio::StringView> underlyingTypeArguments;

    static const ::std::array<::zserio::ItemInfo, 3> items = {
        ::zserio::ItemInfo{ ::zserio::makeStringView("ONE"), static_cast<uint64_t>(INT8_C(0)), false, false},
        ::zserio::ItemInfo{ ::zserio::makeStringView("TWO"), static_cast<uint64_t>(INT8_C(1)), false, false},
        ::zserio::ItemInfo{ ::zserio::makeStringView("MinusOne"), static_cast<uint64_t>(INT8_C(-1)), false, false}
    };

    static const ::zserio::EnumTypeInfo<allocator_type> typeInfo = {
        ::zserio::makeStringView("test_object.polymorphic_allocator.CreatorEnum"),
        ::zserio::BuiltinTypeInfo<allocator_type>::getInt8(), underlyingTypeArguments, items
    };

    return typeInfo;
}

template <>
::zserio::pmr::IReflectablePtr enumReflectable(::test_object::polymorphic_allocator::CreatorEnum value, const ::zserio::pmr::PropagatingPolymorphicAllocator<>& allocator)
{
    class Reflectable : public ::zserio::ReflectableBase<::zserio::pmr::PropagatingPolymorphicAllocator<>>
    {
    public:
        explicit Reflectable(::test_object::polymorphic_allocator::CreatorEnum value) :
                ::zserio::ReflectableBase<::zserio::pmr::PropagatingPolymorphicAllocator<>>(
                        ::zserio::enumTypeInfo<::test_object::polymorphic_allocator::CreatorEnum, ::zserio::pmr::PropagatingPolymorphicAllocator<>>()),
                m_value(value)
        {}

        size_t bitSizeOf(size_t) const override
        {
            return ::zserio::bitSizeOf(m_value);
        }

        void write(::zserio::BitStreamWriter& writer) const override
        {
            ::zserio::write(writer, m_value);
        }

        ::zserio::pmr::AnyHolder getAnyValue(const ::zserio::pmr::PropagatingPolymorphicAllocator<>& allocator) const override
        {
            return ::zserio::pmr::AnyHolder(m_value, allocator);
        }

        ::zserio::pmr::AnyHolder getAnyValue(const ::zserio::pmr::PropagatingPolymorphicAllocator<>& allocator) override
        {
            return ::zserio::pmr::AnyHolder(m_value, allocator);
        }

        int8_t getInt8() const override
        {
            return static_cast<typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type>(m_value);
        }

        int64_t toInt() const override
        {
            return static_cast<typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type>(m_value);
        }

        double toDouble() const override
        {
            return static_cast<double>(toInt());
        }

        ::zserio::pmr::string toString(const ::zserio::pmr::PropagatingPolymorphicAllocator<>& allocator) const override
        {
            return ::zserio::pmr::string(::zserio::enumToString(m_value), allocator);
        }

    private:
        ::test_object::polymorphic_allocator::CreatorEnum m_value;
    };

    return std::allocate_shared<Reflectable>(allocator, value);
}

template <>
size_t enumToOrdinal(::test_object::polymorphic_allocator::CreatorEnum value)
{
    switch (value)
    {
    case ::test_object::polymorphic_allocator::CreatorEnum::ONE:
        return 0;
    case ::test_object::polymorphic_allocator::CreatorEnum::TWO:
        return 1;
    case ::test_object::polymorphic_allocator::CreatorEnum::MinusOne:
        return 2;
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration CreatorEnum: ") <<
                static_cast<typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type>(value) << "!";
    }
}

template <>
::test_object::polymorphic_allocator::CreatorEnum valueToEnum(
        typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type rawValue)
{
    switch (rawValue)
    {
    case INT8_C(0):
    case INT8_C(1):
    case INT8_C(-1):
        return static_cast<::test_object::polymorphic_allocator::CreatorEnum>(rawValue);
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration CreatorEnum: ") << rawValue << "!";
    }
}

template <>
uint32_t enumHashCode<::test_object::polymorphic_allocator::CreatorEnum>(::test_object::polymorphic_allocator::CreatorEnum value)
{
    uint32_t result = ::zserio::HASH_SEED;
    result = ::zserio::calcHashCode(result, enumToValue(value));
    return result;
}

template <>
void initPackingContext(::zserio::DeltaContext& context, ::test_object::polymorphic_allocator::CreatorEnum value)
{
    context.init<::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type>>(
            ::zserio::enumToValue(value));
}

template <>
size_t bitSizeOf(::test_object::polymorphic_allocator::CreatorEnum)
{
    return UINT8_C(8);
}

template <>
size_t bitSizeOf(::zserio::DeltaContext& context, ::test_object::polymorphic_allocator::CreatorEnum value)
{
    return context.bitSizeOf<::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type>>(
            ::zserio::enumToValue(value));
}

template <>
size_t initializeOffsets(size_t bitPosition, ::test_object::polymorphic_allocator::CreatorEnum value)
{
    return bitPosition + bitSizeOf(value);
}

template <>
size_t initializeOffsets(::zserio::DeltaContext& context, size_t bitPosition, ::test_object::polymorphic_allocator::CreatorEnum value)
{
    return bitPosition + bitSizeOf(context, value);
}

template <>
::test_object::polymorphic_allocator::CreatorEnum read(::zserio::BitStreamReader& in)
{
    return valueToEnum<::test_object::polymorphic_allocator::CreatorEnum>(
            static_cast<typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type>(
                    in.readSignedBits(UINT8_C(8))));
}

template <>
::test_object::polymorphic_allocator::CreatorEnum read(::zserio::DeltaContext& context, ::zserio::BitStreamReader& in)
{
    return valueToEnum<::test_object::polymorphic_allocator::CreatorEnum>(context.read<::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type>>(
            in));
}

template <>
void write(::zserio::BitStreamWriter& out, ::test_object::polymorphic_allocator::CreatorEnum value)
{
    out.writeSignedBits(::zserio::enumToValue(value), UINT8_C(8));
}

template <>
void write(::zserio::DeltaContext& context, ::zserio::BitStreamWriter& out, ::test_object::polymorphic_allocator::CreatorEnum value)
{
    context.write<::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::polymorphic_allocator::CreatorEnum>::type>>(
            out, ::zserio::enumToValue(value));
}

} // namespace zserio
