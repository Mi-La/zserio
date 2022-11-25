/**
 * Automatically generated by Zserio C++ extension version 2.9.0-pre1.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, stdAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/TypeInfo.h>
#include <zserio/AnyHolder.h>
#include <zserio/Reflectable.h>

#include <test_object/DummyEnum.h>

namespace zserio
{

// This is full specialization of enumeration traits and methods for DummyEnum enumeration.
constexpr ::std::array<const char*, 3> EnumTraits<::test_object::DummyEnum>::names;
constexpr ::std::array<::test_object::DummyEnum, 3> EnumTraits<::test_object::DummyEnum>::values;

template <>
const ::zserio::ITypeInfo& enumTypeInfo<::test_object::DummyEnum, ::std::allocator<uint8_t>>()
{
    using allocator_type = ::std::allocator<uint8_t>;

    static const ::zserio::Span<::zserio::StringView> underlyingTypeArguments;

    static const ::std::array<::zserio::ItemInfo, 3> items = {
        ::zserio::ItemInfo{ ::zserio::makeStringView("ONE"), static_cast<uint64_t>(INT8_C(0)) },
        ::zserio::ItemInfo{ ::zserio::makeStringView("TWO"), static_cast<uint64_t>(INT8_C(1)) },
        ::zserio::ItemInfo{ ::zserio::makeStringView("MinusOne"), static_cast<uint64_t>(INT8_C(-1)) }
    };

    static const ::zserio::EnumTypeInfo<allocator_type> typeInfo = {
        ::zserio::makeStringView("test_object.DummyEnum"),
        ::zserio::BuiltinTypeInfo<allocator_type>::getInt8(), underlyingTypeArguments, items
    };

    return typeInfo;
}

template <>
::zserio::IReflectablePtr enumReflectable(::test_object::DummyEnum value, const ::std::allocator<uint8_t>& allocator)
{
    class Reflectable : public ::zserio::ReflectableBase<::std::allocator<uint8_t>>
    {
    public:
        explicit Reflectable(::test_object::DummyEnum value) :
                ::zserio::ReflectableBase<::std::allocator<uint8_t>>(
                        ::zserio::enumTypeInfo<::test_object::DummyEnum, ::std::allocator<uint8_t>>()),
                m_value(value)
        {}

        virtual size_t bitSizeOf(size_t) const override
        {
            return ::zserio::bitSizeOf(m_value);
        }

        virtual void write(::zserio::BitStreamWriter& writer) const override
        {
            ::zserio::write(writer, m_value);
        }

        virtual ::zserio::AnyHolder<> getAnyValue(const ::std::allocator<uint8_t>& allocator) const override
        {
            return ::zserio::AnyHolder<>(m_value, allocator);
        }

        virtual ::zserio::AnyHolder<> getAnyValue(const ::std::allocator<uint8_t>& allocator) override
        {
            return ::zserio::AnyHolder<>(m_value, allocator);
        }

        virtual int8_t getInt8() const override
        {
            return static_cast<typename ::std::underlying_type<::test_object::DummyEnum>::type>(m_value);
        }

        virtual int64_t toInt() const override
        {
            return static_cast<typename ::std::underlying_type<::test_object::DummyEnum>::type>(m_value);
        }

        virtual double toDouble() const override
        {
            return static_cast<double>(toInt());
        }

        virtual ::zserio::string<> toString(
                const ::std::allocator<uint8_t>& allocator = ::std::allocator<uint8_t>()) const override
        {
            return ::zserio::string<>(::zserio::enumToString(m_value), allocator);
        }

    private:
        ::test_object::DummyEnum m_value;
    };

    return std::allocate_shared<Reflectable>(allocator, value);
}

template <>
size_t enumToOrdinal(::test_object::DummyEnum value)
{
    switch (value)
    {
    case ::test_object::DummyEnum::ONE:
        return 0;
    case ::test_object::DummyEnum::TWO:
        return 1;
    case ::test_object::DummyEnum::MinusOne:
        return 2;
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration DummyEnum: ") <<
                static_cast<typename ::std::underlying_type<::test_object::DummyEnum>::type>(value) << "!";
    }
}

template <>
::test_object::DummyEnum valueToEnum(
        typename ::std::underlying_type<::test_object::DummyEnum>::type rawValue)
{
    switch (rawValue)
    {
    case INT8_C(0):
    case INT8_C(1):
    case INT8_C(-1):
        return ::test_object::DummyEnum(rawValue);
    default:
        throw ::zserio::CppRuntimeException("Unknown value for enumeration DummyEnum: ") << rawValue << "!";
    }
}

template <>
uint32_t enumHashCode<::test_object::DummyEnum>(::test_object::DummyEnum value)
{
    uint32_t result = ::zserio::HASH_SEED;
    result = ::zserio::calcHashCode(result, enumToValue(value));
    return result;
}

template <>
void initPackingContext(::zserio::PackingContextNode& contextNode, ::test_object::DummyEnum value)
{
    contextNode.getContext().init(::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::DummyEnum>::type>(),
            ::zserio::enumToValue(value));
}

template <>
size_t bitSizeOf(::test_object::DummyEnum)
{
    return UINT8_C(8);
}

template <>
size_t bitSizeOf(::zserio::PackingContextNode& contextNode, ::test_object::DummyEnum value)
{
    return contextNode.getContext().bitSizeOf(
            ::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::DummyEnum>::type>(),
            ::zserio::enumToValue(value));
}

template <>
size_t initializeOffsets(size_t bitPosition, ::test_object::DummyEnum value)
{
    return bitPosition + bitSizeOf(value);
}

template <>
size_t initializeOffsets(::zserio::PackingContextNode& contextNode,
        size_t bitPosition, ::test_object::DummyEnum value)
{
    return bitPosition + bitSizeOf(contextNode, value);
}

template <>
::test_object::DummyEnum read(::zserio::BitStreamReader& in)
{
    return valueToEnum<::test_object::DummyEnum>(
            static_cast<typename ::std::underlying_type<::test_object::DummyEnum>::type>(
                    in.readSignedBits(UINT8_C(8))));
}

template <>
::test_object::DummyEnum read(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    return valueToEnum<::test_object::DummyEnum>(contextNode.getContext().read(
            ::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::DummyEnum>::type>(), in));
}

template <>
void write(::zserio::BitStreamWriter& out, ::test_object::DummyEnum value)
{
    out.writeSignedBits(::zserio::enumToValue(value), UINT8_C(8));
}

template <>
void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out, ::test_object::DummyEnum value)
{
    contextNode.getContext().write(
            ::zserio::StdIntArrayTraits<typename ::std::underlying_type<::test_object::DummyEnum>::type>(),
            out, ::zserio::enumToValue(value));
}

} // namespace zserio