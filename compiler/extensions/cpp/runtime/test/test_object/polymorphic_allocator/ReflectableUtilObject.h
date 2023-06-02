/**
 * Automatically generated by Zserio C++ extension version 2.11.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, polymorhpicAllocator.
 */

#ifndef TEST_OBJECT_POLYMORPHIC_ALLOCATOR_REFLECTABLE_UTIL_OBJECT_H
#define TEST_OBJECT_POLYMORPHIC_ALLOCATOR_REFLECTABLE_UTIL_OBJECT_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <zserio/pmr/ITypeInfo.h>
#include <zserio/pmr/IReflectable.h>
#include <zserio/pmr/PolymorphicAllocator.h>
#include <zserio/pmr/PackingContext.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Types.h>

#include <test_object/polymorphic_allocator/ReflectableUtilChoice.h>

namespace test_object
{
namespace polymorphic_allocator
{

class ReflectableUtilObject
{
public:
    using allocator_type = ::zserio::pmr::PropagatingPolymorphicAllocator<>;

    ReflectableUtilObject() noexcept :
            ReflectableUtilObject(allocator_type())
    {}

    explicit ReflectableUtilObject(const allocator_type& allocator) noexcept;

    template <typename ZSERIO_T_reflectableUtilChoice = ::test_object::polymorphic_allocator::ReflectableUtilChoice>
    ReflectableUtilObject(
            uint8_t choiceParam_,
            ZSERIO_T_reflectableUtilChoice&& reflectableUtilChoice_,
            const allocator_type& allocator = allocator_type()) :
            ReflectableUtilObject(allocator)
    {
        m_choiceParam_ = choiceParam_;
        m_reflectableUtilChoice_ = ::std::forward<ZSERIO_T_reflectableUtilChoice>(reflectableUtilChoice_);
    }

    explicit ReflectableUtilObject(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit ReflectableUtilObject(::zserio::pmr::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~ReflectableUtilObject() = default;

    ReflectableUtilObject(const ReflectableUtilObject& other);
    ReflectableUtilObject& operator=(const ReflectableUtilObject& other);

    ReflectableUtilObject(ReflectableUtilObject&& other);
    ReflectableUtilObject& operator=(ReflectableUtilObject&& other);

    ReflectableUtilObject(::zserio::PropagateAllocatorT,
            const ReflectableUtilObject& other, const allocator_type& allocator);

    static const ::zserio::pmr::ITypeInfo& typeInfo();
    ::zserio::pmr::IReflectableConstPtr reflectable(const allocator_type& allocator = allocator_type()) const;
    ::zserio::pmr::IReflectablePtr reflectable(const allocator_type& allocator = allocator_type());

    void initializeChildren();

    uint8_t getChoiceParam() const;
    void setChoiceParam(uint8_t choiceParam_);

    const ::test_object::polymorphic_allocator::ReflectableUtilChoice& getReflectableUtilChoice() const;
    ::test_object::polymorphic_allocator::ReflectableUtilChoice& getReflectableUtilChoice();
    void setReflectableUtilChoice(const ::test_object::polymorphic_allocator::ReflectableUtilChoice& reflectableUtilChoice_);
    void setReflectableUtilChoice(::test_object::polymorphic_allocator::ReflectableUtilChoice&& reflectableUtilChoice_);

    static void createPackingContext(::zserio::pmr::PackingContextNode& contextNode);
    void initPackingContext(::zserio::pmr::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::pmr::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::pmr::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const ReflectableUtilObject& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::pmr::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    uint8_t readChoiceParam(::zserio::BitStreamReader& in);
    uint8_t readChoiceParam(::zserio::pmr::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::test_object::polymorphic_allocator::ReflectableUtilChoice readReflectableUtilChoice(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::test_object::polymorphic_allocator::ReflectableUtilChoice readReflectableUtilChoice(::zserio::pmr::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);

    bool m_areChildrenInitialized;
    uint8_t m_choiceParam_;
    ::test_object::polymorphic_allocator::ReflectableUtilChoice m_reflectableUtilChoice_;
};

} // namespace polymorphic_allocator
} // namespace test_object

#endif // TEST_OBJECT_POLYMORPHIC_ALLOCATOR_REFLECTABLE_UTIL_OBJECT_H
