/**
 * Automatically generated by Zserio C++ extension version 2.12.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, polymorphicAllocator.
 */

#ifndef TEST_OBJECT_POLYMORPHIC_ALLOCATOR_WALKER_NESTED_H
#define TEST_OBJECT_POLYMORPHIC_ALLOCATOR_WALKER_NESTED_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <zserio/pmr/ITypeInfo.h>
#include <zserio/pmr/IReflectable.h>
#include <zserio/pmr/PolymorphicAllocator.h>
#include <zserio/pmr/ArrayTraits.h>
#include <zserio/pmr/String.h>

namespace test_object
{
namespace polymorphic_allocator
{

class WalkerNested
{
public:
    using allocator_type = ::zserio::pmr::PropagatingPolymorphicAllocator<>;

    WalkerNested() noexcept :
            WalkerNested(allocator_type())
    {}

    explicit WalkerNested(const allocator_type& allocator) noexcept;

    template <typename ZSERIO_T_text = ::zserio::pmr::string,
            ::zserio::is_field_constructor_enabled_t<ZSERIO_T_text, WalkerNested, allocator_type> = 0>
    explicit WalkerNested(
            ZSERIO_T_text&& text_,
            const allocator_type& allocator = allocator_type()) :
            WalkerNested(allocator)
    {
        m_text_ = ::std::forward<ZSERIO_T_text>(text_);
    }

    explicit WalkerNested(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~WalkerNested() = default;

    WalkerNested(const WalkerNested&) = default;
    WalkerNested& operator=(const WalkerNested&) = default;

    WalkerNested(WalkerNested&&) = default;
    WalkerNested& operator=(WalkerNested&&) = default;

    WalkerNested(::zserio::PropagateAllocatorT,
            const WalkerNested& other, const allocator_type& allocator);

    static const ::zserio::pmr::ITypeInfo& typeInfo();
    ::zserio::pmr::IReflectableConstPtr reflectable(const allocator_type& allocator = allocator_type()) const;
    ::zserio::pmr::IReflectablePtr reflectable(const allocator_type& allocator = allocator_type());

    const ::zserio::pmr::string& getText() const;
    ::zserio::pmr::string& getText();
    void setText(const ::zserio::pmr::string& text_);
    void setText(::zserio::pmr::string&& text_);

    size_t bitSizeOf(size_t bitPosition = 0) const;

    size_t initializeOffsets(size_t bitPosition = 0);

    bool operator==(const WalkerNested& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;

private:
    ::zserio::pmr::string readText(::zserio::BitStreamReader& in,
            const allocator_type& allocator);

    ::zserio::pmr::string m_text_;
};

} // namespace polymorphic_allocator
} // namespace test_object

#endif // TEST_OBJECT_POLYMORPHIC_ALLOCATOR_WALKER_NESTED_H
