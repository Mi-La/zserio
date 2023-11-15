/**
 * Automatically generated by Zserio C++ extension version 2.12.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, stdAllocator.
 */

#ifndef TEST_OBJECT_STD_ALLOCATOR_CREATOR_OBJECT_H
#define TEST_OBJECT_STD_ALLOCATOR_CREATOR_OBJECT_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <zserio/DeltaContext.h>
#include <zserio/ITypeInfo.h>
#include <zserio/IReflectable.h>
#include <memory>
#include <zserio/OptionalHolder.h>
#include <zserio/Array.h>
#include <zserio/ArrayTraits.h>
#include <zserio/BitBuffer.h>
#include <zserio/String.h>
#include <zserio/Types.h>
#include <zserio/Vector.h>

#include <test_object/std_allocator/CreatorNested.h>

namespace test_object
{
namespace std_allocator
{

class CreatorObject
{
public:
    class ZserioPackingContext
    {
    public:
        ::zserio::DeltaContext& getValue()
        {
            return m_value_;
        }

        ::test_object::std_allocator::CreatorNested::ZserioPackingContext& getNested()
        {
            return m_nested_;
        }

        ::test_object::std_allocator::CreatorNested::ZserioPackingContext& getOptionalNested()
        {
            return m_optionalNested_;
        }

    private:
        ::zserio::DeltaContext m_value_;
        ::test_object::std_allocator::CreatorNested::ZserioPackingContext m_nested_;
        ::test_object::std_allocator::CreatorNested::ZserioPackingContext m_optionalNested_;
    };

    using allocator_type = ::std::allocator<uint8_t>;

    CreatorObject() noexcept :
            CreatorObject(allocator_type())
    {}

    explicit CreatorObject(const allocator_type& allocator) noexcept;

    template <typename ZSERIO_T_nested = ::test_object::std_allocator::CreatorNested,
            typename ZSERIO_T_text = ::zserio::string<>,
            typename ZSERIO_T_nestedArray = ::zserio::vector<::test_object::std_allocator::CreatorNested>,
            typename ZSERIO_T_textArray = ::zserio::vector<::zserio::string<>>,
            typename ZSERIO_T_externArray = ::zserio::vector<::zserio::BitBuffer>,
            typename ZSERIO_T_bytesArray = ::zserio::vector<::zserio::vector<uint8_t>>,
            typename ZSERIO_T_optionalBool = bool,
            typename ZSERIO_T_optionalNested = ::test_object::std_allocator::CreatorNested>
    CreatorObject(
            uint32_t value_,
            ZSERIO_T_nested&& nested_,
            ZSERIO_T_text&& text_,
            ZSERIO_T_nestedArray&& nestedArray_,
            ZSERIO_T_textArray&& textArray_,
            ZSERIO_T_externArray&& externArray_,
            ZSERIO_T_bytesArray&& bytesArray_,
            ZSERIO_T_optionalBool&& optionalBool_,
            ZSERIO_T_optionalNested&& optionalNested_,
            const allocator_type& allocator = allocator_type()) :
            CreatorObject(allocator)
    {
        m_value_ = value_;
        m_nested_ = ::std::forward<ZSERIO_T_nested>(nested_);
        m_text_ = ::std::forward<ZSERIO_T_text>(text_);
        m_nestedArray_ = ZserioArrayType_nestedArray(::std::forward<ZSERIO_T_nestedArray>(nestedArray_));
        m_textArray_ = ZserioArrayType_textArray(::std::forward<ZSERIO_T_textArray>(textArray_));
        m_externArray_ = ::zserio::createOptionalArray<ZserioArrayType_externArray>(::std::forward<ZSERIO_T_externArray>(externArray_));
        m_bytesArray_ = ::zserio::createOptionalArray<ZserioArrayType_bytesArray>(::std::forward<ZSERIO_T_bytesArray>(bytesArray_));
        m_optionalBool_ = ::std::forward<ZSERIO_T_optionalBool>(optionalBool_);
        m_optionalNested_ = ::std::forward<ZSERIO_T_optionalNested>(optionalNested_);
    }

    explicit CreatorObject(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit CreatorObject(ZserioPackingContext& context,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~CreatorObject() = default;

    CreatorObject(const CreatorObject& other);
    CreatorObject& operator=(const CreatorObject& other);

    CreatorObject(CreatorObject&& other);
    CreatorObject& operator=(CreatorObject&& other);

    CreatorObject(::zserio::PropagateAllocatorT,
            const CreatorObject& other, const allocator_type& allocator);

    static const ::zserio::ITypeInfo& typeInfo();
    ::zserio::IReflectableConstPtr reflectable(const allocator_type& allocator = allocator_type()) const;
    ::zserio::IReflectablePtr reflectable(const allocator_type& allocator = allocator_type());

    void initializeChildren();

    uint32_t getValue() const;
    void setValue(uint32_t value_);

    const ::test_object::std_allocator::CreatorNested& getNested() const;
    ::test_object::std_allocator::CreatorNested& getNested();
    void setNested(const ::test_object::std_allocator::CreatorNested& nested_);
    void setNested(::test_object::std_allocator::CreatorNested&& nested_);

    const ::zserio::string<>& getText() const;
    ::zserio::string<>& getText();
    void setText(const ::zserio::string<>& text_);
    void setText(::zserio::string<>&& text_);

    const ::zserio::vector<::test_object::std_allocator::CreatorNested>& getNestedArray() const;
    ::zserio::vector<::test_object::std_allocator::CreatorNested>& getNestedArray();
    void setNestedArray(const ::zserio::vector<::test_object::std_allocator::CreatorNested>& nestedArray_);
    void setNestedArray(::zserio::vector<::test_object::std_allocator::CreatorNested>&& nestedArray_);

    const ::zserio::vector<::zserio::string<>>& getTextArray() const;
    ::zserio::vector<::zserio::string<>>& getTextArray();
    void setTextArray(const ::zserio::vector<::zserio::string<>>& textArray_);
    void setTextArray(::zserio::vector<::zserio::string<>>&& textArray_);

    const ::zserio::vector<::zserio::BitBuffer>& getExternArray() const;
    ::zserio::vector<::zserio::BitBuffer>& getExternArray();
    void setExternArray(const ::zserio::vector<::zserio::BitBuffer>& externArray_);
    void setExternArray(::zserio::vector<::zserio::BitBuffer>&& externArray_);
    bool isExternArrayUsed() const;
    bool isExternArraySet() const;
    void resetExternArray();

    const ::zserio::vector<::zserio::vector<uint8_t>>& getBytesArray() const;
    ::zserio::vector<::zserio::vector<uint8_t>>& getBytesArray();
    void setBytesArray(const ::zserio::vector<::zserio::vector<uint8_t>>& bytesArray_);
    void setBytesArray(::zserio::vector<::zserio::vector<uint8_t>>&& bytesArray_);
    bool isBytesArrayUsed() const;
    bool isBytesArraySet() const;
    void resetBytesArray();

    bool getOptionalBool() const;
    void setOptionalBool(bool optionalBool_);
    bool isOptionalBoolUsed() const;
    bool isOptionalBoolSet() const;
    void resetOptionalBool();

    const ::test_object::std_allocator::CreatorNested& getOptionalNested() const;
    ::test_object::std_allocator::CreatorNested& getOptionalNested();
    void setOptionalNested(const ::test_object::std_allocator::CreatorNested& optionalNested_);
    void setOptionalNested(::test_object::std_allocator::CreatorNested&& optionalNested_);
    bool isOptionalNestedUsed() const;
    bool isOptionalNestedSet() const;
    void resetOptionalNested();

    void initPackingContext(ZserioPackingContext& context) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(ZserioPackingContext& context, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(ZserioPackingContext& context, size_t bitPosition);

    bool operator==(const CreatorObject& other) const;

    bool operator<(const CreatorObject& other) const;

    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(ZserioPackingContext& context, ::zserio::BitStreamWriter& out) const;

private:
    class ZserioArrayExpressions_nestedArray
    {
    public:
        using OwnerType = CreatorObject;

        static void initializeElement(CreatorObject& owner,
                ::test_object::std_allocator::CreatorNested& element, size_t index);
    };

    class ZserioElementFactory_nestedArray
    {
    public:
        using OwnerType = CreatorObject;

        static void create(CreatorObject& owner,
                ::zserio::vector<::test_object::std_allocator::CreatorNested>& array,
                ::zserio::BitStreamReader& in, size_t index);

        static void create(CreatorObject& owner,
                ::zserio::vector<::test_object::std_allocator::CreatorNested>& array,
                ::test_object::std_allocator::CreatorNested::ZserioPackingContext& context,
                ::zserio::BitStreamReader& in, size_t index);
    };

    using ZserioArrayType_nestedArray = ::zserio::Array<::zserio::vector<::test_object::std_allocator::CreatorNested>, ::zserio::ObjectArrayTraits<::test_object::std_allocator::CreatorNested, ZserioElementFactory_nestedArray>, ::zserio::ArrayType::AUTO, ZserioArrayExpressions_nestedArray>;
    using ZserioArrayType_textArray = ::zserio::Array<::zserio::vector<::zserio::string<>>, ::zserio::StringArrayTraits, ::zserio::ArrayType::AUTO>;
    using ZserioArrayType_externArray = ::zserio::Array<::zserio::vector<::zserio::BitBuffer>, ::zserio::BitBufferArrayTraits, ::zserio::ArrayType::AUTO>;
    using ZserioArrayType_bytesArray = ::zserio::Array<::zserio::vector<::zserio::vector<uint8_t>>, ::zserio::BytesArrayTraits, ::zserio::ArrayType::AUTO>;

    uint32_t readValue(::zserio::BitStreamReader& in);
    uint32_t readValue(ZserioPackingContext& context,
            ::zserio::BitStreamReader& in);
    ::test_object::std_allocator::CreatorNested readNested(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::test_object::std_allocator::CreatorNested readNested(ZserioPackingContext& context,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::zserio::string<> readText(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ZserioArrayType_nestedArray readNestedArray(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ZserioArrayType_nestedArray readNestedArray(ZserioPackingContext& context,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ZserioArrayType_textArray readTextArray(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<ZserioArrayType_externArray> readExternArray(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<ZserioArrayType_bytesArray> readBytesArray(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<bool> readOptionalBool(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<::test_object::std_allocator::CreatorNested> readOptionalNested(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::test_object::std_allocator::CreatorNested> readOptionalNested(ZserioPackingContext& context,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);

    bool m_areChildrenInitialized;
    uint32_t m_value_;
    ::test_object::std_allocator::CreatorNested m_nested_;
    ::zserio::string<> m_text_;
    ZserioArrayType_nestedArray m_nestedArray_;
    ZserioArrayType_textArray m_textArray_;
    ::zserio::InplaceOptionalHolder<ZserioArrayType_externArray> m_externArray_;
    ::zserio::InplaceOptionalHolder<ZserioArrayType_bytesArray> m_bytesArray_;
    ::zserio::InplaceOptionalHolder<bool> m_optionalBool_;
    ::zserio::InplaceOptionalHolder<::test_object::std_allocator::CreatorNested> m_optionalNested_;
};

} // namespace std_allocator
} // namespace test_object

#endif // TEST_OBJECT_STD_ALLOCATOR_CREATOR_OBJECT_H
