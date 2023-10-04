/**
 * Automatically generated by Zserio C++ extension version 2.12.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, stdAllocator.
 */

#ifndef TEST_OBJECT_STD_ALLOCATOR_REFLECTABLE_UTIL_BITMASK_H
#define TEST_OBJECT_STD_ALLOCATOR_REFLECTABLE_UTIL_BITMASK_H

#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/DeltaContext.h>
#include <zserio/ITypeInfo.h>
#include <zserio/IReflectable.h>
#include <zserio/ArrayTraits.h>
#include <zserio/String.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Types.h>

namespace test_object
{
namespace std_allocator
{

class ReflectableUtilBitmask
{
public:
    using underlying_type = uint8_t;

    enum class Values : underlying_type
    {
        READ = UINT8_C(1),
        WRITE = UINT8_C(2)
    };

    constexpr ReflectableUtilBitmask() noexcept :
            m_value(0)
    {}

    explicit ReflectableUtilBitmask(::zserio::BitStreamReader& in);
    ReflectableUtilBitmask(::zserio::DeltaContext& context, ::zserio::BitStreamReader& in);
    constexpr ReflectableUtilBitmask(Values value) noexcept :
            m_value(static_cast<underlying_type>(value))
    {}

    constexpr explicit ReflectableUtilBitmask(underlying_type value) noexcept :
            m_value(value)
    {}

    ~ReflectableUtilBitmask() = default;

    ReflectableUtilBitmask(const ReflectableUtilBitmask&) = default;
    ReflectableUtilBitmask& operator=(const ReflectableUtilBitmask&) = default;

    ReflectableUtilBitmask(ReflectableUtilBitmask&&) = default;
    ReflectableUtilBitmask& operator=(ReflectableUtilBitmask&&) = default;

    static const ::zserio::ITypeInfo& typeInfo();
    ::zserio::IReflectablePtr reflectable(const ::std::allocator<uint8_t>& allocator = ::std::allocator<uint8_t>()) const;

    constexpr explicit operator underlying_type() const
    {
        return m_value;
    }

    constexpr underlying_type getValue() const
    {
        return m_value;
    }

    void initPackingContext(::zserio::DeltaContext& context) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::DeltaContext& context, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0) const;
    size_t initializeOffsets(::zserio::DeltaContext& context, size_t bitPosition) const;

    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::DeltaContext& context, ::zserio::BitStreamWriter& out) const;

    ::zserio::string<> toString(const ::zserio::string<>::allocator_type& allocator =
            ::zserio::string<>::allocator_type()) const;

private:
    static underlying_type readValue(::zserio::BitStreamReader& in);
    static underlying_type readValue(::zserio::DeltaContext& context, ::zserio::BitStreamReader& in);

    underlying_type m_value;
};

inline bool operator==(const ReflectableUtilBitmask& lhs, const ReflectableUtilBitmask& rhs)
{
    return lhs.getValue() == rhs.getValue();
}

inline bool operator!=(const ReflectableUtilBitmask& lhs, const ReflectableUtilBitmask& rhs)
{
    return lhs.getValue() != rhs.getValue();
}

inline ReflectableUtilBitmask operator|(ReflectableUtilBitmask::Values lhs, ReflectableUtilBitmask::Values rhs)
{
    return ReflectableUtilBitmask(static_cast<ReflectableUtilBitmask::underlying_type>(lhs) | static_cast<ReflectableUtilBitmask::underlying_type>(rhs));
}

inline ReflectableUtilBitmask operator|(const ReflectableUtilBitmask& lhs, const ReflectableUtilBitmask& rhs)
{
    return ReflectableUtilBitmask(lhs.getValue() | rhs.getValue());
}

inline ReflectableUtilBitmask operator&(ReflectableUtilBitmask::Values lhs, ReflectableUtilBitmask::Values rhs)
{
    return ReflectableUtilBitmask(static_cast<ReflectableUtilBitmask::underlying_type>(lhs) & static_cast<ReflectableUtilBitmask::underlying_type>(rhs));
}

inline ReflectableUtilBitmask operator&(const ReflectableUtilBitmask& lhs, const ReflectableUtilBitmask& rhs)
{
    return ReflectableUtilBitmask(lhs.getValue() & rhs.getValue());
}

inline ReflectableUtilBitmask operator^(ReflectableUtilBitmask::Values lhs, ReflectableUtilBitmask::Values rhs)
{
    return ReflectableUtilBitmask(static_cast<ReflectableUtilBitmask::underlying_type>(lhs) ^ static_cast<ReflectableUtilBitmask::underlying_type>(rhs));
}

inline ReflectableUtilBitmask operator^(const ReflectableUtilBitmask& lhs, const ReflectableUtilBitmask& rhs)
{
    return ReflectableUtilBitmask(lhs.getValue() ^ rhs.getValue());
}

inline ReflectableUtilBitmask operator~(ReflectableUtilBitmask::Values lhs)
{
    return ReflectableUtilBitmask(~static_cast<ReflectableUtilBitmask::underlying_type>(lhs));
}

inline ReflectableUtilBitmask operator~(const ReflectableUtilBitmask& lhs)
{
    return ReflectableUtilBitmask(~lhs.getValue());
}

inline ReflectableUtilBitmask operator|=(ReflectableUtilBitmask& lhs, const ReflectableUtilBitmask& rhs)
{
    lhs = ReflectableUtilBitmask(lhs.getValue() | rhs.getValue());
    return lhs;
}

inline ReflectableUtilBitmask operator&=(ReflectableUtilBitmask& lhs, const ReflectableUtilBitmask& rhs)
{
    lhs = ReflectableUtilBitmask(lhs.getValue() & rhs.getValue());
    return lhs;
}

inline ReflectableUtilBitmask operator^=(ReflectableUtilBitmask& lhs, const ReflectableUtilBitmask& rhs)
{
    lhs = ReflectableUtilBitmask(lhs.getValue() ^ rhs.getValue());
    return lhs;
}

} // namespace std_allocator
} // namespace test_object

#endif // TEST_OBJECT_STD_ALLOCATOR_REFLECTABLE_UTIL_BITMASK_H
