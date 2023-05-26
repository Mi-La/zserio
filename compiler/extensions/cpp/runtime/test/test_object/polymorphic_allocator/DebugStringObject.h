/**
 * Automatically generated by Zserio C++ extension version 2.11.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, polymorhpicAllocator.
 */

#ifndef TEST_OBJECT_POLYMORPHIC_ALLOCATOR_DEBUG_STRING_OBJECT_H
#define TEST_OBJECT_POLYMORPHIC_ALLOCATOR_DEBUG_STRING_OBJECT_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <zserio/pmr/ITypeInfo.h>
#include <zserio/pmr/IReflectable.h>
#include <zserio/pmr/PolymorphicAllocator.h>
#include <zserio/pmr/PackingContext.h>
#include <zserio/pmr/ArrayTraits.h>
#include <zserio/pmr/String.h>

namespace test_object
{
namespace polymorphic_allocator
{

class DebugStringObject
{
public:
    using allocator_type = ::zserio::pmr::PropagatingPolymorphicAllocator<>;

    DebugStringObject() noexcept :
            DebugStringObject(allocator_type())
    {}

    explicit DebugStringObject(const allocator_type& allocator) noexcept;

    template <typename ZSERIO_T_text = ::zserio::pmr::string,
            ::zserio::is_field_constructor_enabled_t<ZSERIO_T_text, DebugStringObject, allocator_type> = 0>
    explicit DebugStringObject(
            ZSERIO_T_text&& text_,
            const allocator_type& allocator = allocator_type()) :
            DebugStringObject(allocator)
    {
        m_text_ = ::std::forward<ZSERIO_T_text>(text_);
    }

    explicit DebugStringObject(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit DebugStringObject(::zserio::pmr::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~DebugStringObject() = default;

    DebugStringObject(const DebugStringObject&) = default;
    DebugStringObject& operator=(const DebugStringObject&) = default;

    DebugStringObject(DebugStringObject&&) = default;
    DebugStringObject& operator=(DebugStringObject&&) = default;

    DebugStringObject(::zserio::PropagateAllocatorT,
            const DebugStringObject& other, const allocator_type& allocator);

    static const ::zserio::pmr::ITypeInfo& typeInfo();
    ::zserio::pmr::IReflectableConstPtr reflectable(const allocator_type& allocator = allocator_type()) const;
    ::zserio::pmr::IReflectablePtr reflectable(const allocator_type& allocator = allocator_type());

    const ::zserio::pmr::string& getText() const;
    ::zserio::pmr::string& getText();
    void setText(const ::zserio::pmr::string& text_);
    void setText(::zserio::pmr::string&& text_);

    static void createPackingContext(::zserio::pmr::PackingContextNode& contextNode);
    void initPackingContext(::zserio::pmr::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::pmr::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::pmr::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const DebugStringObject& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::pmr::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    ::zserio::pmr::string readText(::zserio::BitStreamReader& in,
            const allocator_type& allocator);

    ::zserio::pmr::string m_text_;
};

} // namespace polymorphic_allocator
} // namespace test_object

#endif // TEST_OBJECT_POLYMORPHIC_ALLOCATOR_DEBUG_STRING_OBJECT_H