/**
 * Automatically generated by Zserio C++ extension version 2.12.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, stdAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/TypeInfo.h>
#include <zserio/AnyHolder.h>
#include <zserio/Reflectable.h>

#include <test_object/std_allocator/ArrayEnum.h>

namespace zserio
{

// This is full specialization of enumeration traits and methods for ArrayEnum enumeration.
constexpr ::std::array<const char*, 3> EnumTraits<::test_object::std_allocator::ArrayEnum>::names;
constexpr ::std::array<::test_object::std_allocator::ArrayEnum, 3> EnumTraits<::test_object::std_allocator::ArrayEnum>::values;
constexpr const char* EnumTraits<::test_object::std_allocator::ArrayEnum>::enumName;

template <>
const ::zserio::ITypeInfo& enumTypeInfo<::test_object::std_allocator::ArrayEnum, ::std::allocator<uint8_t>>()
{
    using allocator_type = ::std::allocator<uint8_t>;

    static const ::zserio::Span<::zserio::StringView> underlyingTypeArguments;

    static const ::std::array<::zserio::ItemInfo, 3> items = {
        ::zserio::ItemInfo{ ::zserio::makeStringView("VALUE1"), static_cast<uint64_t>(INT8_C(0)), false, false},
        ::zserio::ItemInfo{ ::zserio::makeStringView("VALUE2"), static_cast<uint64_t>(INT8_C(1)), false, false},
        ::zserio::ItemInfo{ ::zserio::makeStringView("VALUE3"), static_cast<uint64_t>(INT8_C(2)), false, false}
    };

    static const ::zserio::EnumTypeInfo<allocator_type> typeInfo = {
        ::zserio::makeStringView("test_object.std_allocator.ArrayEnum"),
        ::zserio::BuiltinTypeInfo<allocator_type>::getInt8(), underlyingTypeArguments, items
    };

    return typeInfo;
}

template <>
::zserio::IReflectablePtr enumReflectable(::test_object::std_allocator::ArrayEnum value, const ::std::allocator<uint8_t>& allocator)
{
    class Reflectable : public ::zserio::ReflectableBase<::std::allocator<uint8_t>>
    {
    public:
        explicit Reflectable(::test_object::std_allocator::ArrayEnum value) :
                ::zserio::ReflectableBase<::std::allocator<uint8_t>>(
                        ::zserio::enumTypeInfo<::test_object::std_allocator::ArrayEnum, ::std::allocator<uint8_t>>()),
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

        ::zserio::AnyHolder<> getAnyValue(const ::std::allocator<uint8_t>& allocator) const override
        {
            return ::zserio::AnyHolder<>(m_value, allocator);
        }

        ::zserio::AnyHolder<> getAnyValue(const ::std::allocator<uint8_t>& allocator) override
        {
            return ::zserio::AnyHolder<>(m_value, allocator);
        }

        int8_t getInt8() const override
        {
            return static_cast<typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type>(m_value);
        }

        int64_t toInt() const override
        {
            return static_cast<typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type>(m_value);
        }

        double toDouble() const override
        {
            return static_cast<double>(toInt());
        }

        ::zserio::string<> toString(const ::std::allocator<uint8_t>& allocator) const override
        {
            return ::zserio::string<>(::zserio::enumToString(m_value), allocator);
        }

    private:
        ::test_object::std_allocator::ArrayEnum m_value;
    };

    return std::allocate_shared<Reflectable>(allocator, value);
}

template <>
size_t enumToOrdinal(::test_object::std_allocator::ArrayEnum value)
{
    switch (value)
    {
    case ::test_object::std_allocator::ArrayEnum::VALUE1:
        return 0;
    case ::test_object::std_allocator::ArrayEnum::VALUE2:
        return 1;
    case ::test_object::std_allocator::ArrayEnum::VALUE3:
        return 2;
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration ArrayEnum: ") <<
                static_cast<typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type>(value) << "!";
    }
}

template <>
::test_object::std_allocator::ArrayEnum valueToEnum(
        typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type rawValue)
{
    switch (rawValue)
    {
    case INT8_C(0):
    case INT8_C(1):
    case INT8_C(2):
        return static_cast<::test_object::std_allocator::ArrayEnum>(rawValue);
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration ArrayEnum: ") << rawValue << "!";
    }
}

template <>
uint32_t enumHashCode<::test_object::std_allocator::ArrayEnum>(::test_object::std_allocator::ArrayEnum value)
{
    uint32_t result = ::zserio::HASH_SEED;
    result = ::zserio::calcHashCode(result, enumToValue(value));
    return result;
}

template <>
void initPackingContext(::zserio::DeltaContext& context, ::test_object::std_allocator::ArrayEnum value)
{
    context.init<::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type>>(
            ::zserio::enumToValue(value));
}

template <>
size_t bitSizeOf(::test_object::std_allocator::ArrayEnum)
{
    return UINT8_C(8);
}

template <>
size_t bitSizeOf(::zserio::DeltaContext& context, ::test_object::std_allocator::ArrayEnum value)
{
    return context.bitSizeOf<::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type>>(
            ::zserio::enumToValue(value));
}

template <>
size_t initializeOffsets(size_t bitPosition, ::test_object::std_allocator::ArrayEnum value)
{
    return bitPosition + bitSizeOf(value);
}

template <>
size_t initializeOffsets(::zserio::DeltaContext& context, size_t bitPosition, ::test_object::std_allocator::ArrayEnum value)
{
    return bitPosition + bitSizeOf(context, value);
}

template <>
::test_object::std_allocator::ArrayEnum read(::zserio::BitStreamReader& in)
{
    return valueToEnum<::test_object::std_allocator::ArrayEnum>(
            static_cast<typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type>(
                    in.readSignedBits(UINT8_C(8))));
}

template <>
::test_object::std_allocator::ArrayEnum read(::zserio::DeltaContext& context, ::zserio::BitStreamReader& in)
{
    return valueToEnum<::test_object::std_allocator::ArrayEnum>(context.read<::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type>>(
            in));
}

template <>
void write(::zserio::BitStreamWriter& out, ::test_object::std_allocator::ArrayEnum value)
{
    out.writeSignedBits(::zserio::enumToValue(value), UINT8_C(8));
}

template <>
void write(::zserio::DeltaContext& context, ::zserio::BitStreamWriter& out, ::test_object::std_allocator::ArrayEnum value)
{
    context.write<::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::std_allocator::ArrayEnum>::type>>(
            out, ::zserio::enumToValue(value));
}

} // namespace zserio
