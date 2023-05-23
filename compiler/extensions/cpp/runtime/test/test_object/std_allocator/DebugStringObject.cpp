/**
 * Automatically generated by Zserio C++ extension version 2.11.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, typeInfoCode, reflectionCode, stdAllocator.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/HashCodeUtil.h>
#include <zserio/BitPositionUtil.h>
#include <zserio/BitSizeOfCalculator.h>
#include <zserio/BitFieldUtil.h>
#include <zserio/TypeInfo.h>
#include <zserio/AnyHolder.h>
#include <zserio/Reflectable.h>
#include <zserio/StringView.h>

#include <test_object/std_allocator/DebugStringObject.h>

namespace test_object
{
namespace std_allocator
{

DebugStringObject::DebugStringObject(const allocator_type& allocator) noexcept :
        m_text_(::zserio::stringViewToString(::zserio::makeStringView("test"), allocator))
{
}

DebugStringObject::DebugStringObject(::zserio::BitStreamReader& in, const allocator_type& allocator) :
        m_text_(readText(in, allocator))
{
}

DebugStringObject::DebugStringObject(::zserio::PackingContextNode&, ::zserio::BitStreamReader& in, const allocator_type& allocator) :
        m_text_(readText(in, allocator))
{
}

DebugStringObject::DebugStringObject(::zserio::PropagateAllocatorT,
        const DebugStringObject& other, const allocator_type& allocator) :
        m_text_(::zserio::allocatorPropagatingCopy(other.m_text_, allocator))
{
}

const ::zserio::ITypeInfo& DebugStringObject::typeInfo()
{
    static const ::zserio::StringView templateName;
    static const ::zserio::Span<::zserio::BasicTemplateArgumentInfo<allocator_type>> templateArguments;

    static const ::std::array<::zserio::BasicFieldInfo<allocator_type>, 1> fields = {
        ::zserio::BasicFieldInfo<allocator_type>{
            ::zserio::makeStringView("text"), // schemaName
            ::zserio::BuiltinTypeInfo<allocator_type>::getString(), // typeInfo
            {}, // typeArguments
            {}, // alignment
            {}, // offset
            ::zserio::makeStringView("::zserio::makeStringView(\"test\")"), // initializer
            false, // isOptional
            {}, // optionalClause
            {}, // constraint
            false, // isArray
            {}, // arrayLength
            false, // isPacked
            false // isImplicit
        }
    };

    static const ::zserio::Span<::zserio::BasicParameterInfo<allocator_type>> parameters;

    static const ::zserio::Span<::zserio::BasicFunctionInfo<allocator_type>> functions;

    static const ::zserio::StructTypeInfo<allocator_type> typeInfo = {
        ::zserio::makeStringView("test_object.std_allocator.DebugStringObject"),
        [](const allocator_type& allocator) -> ::zserio::IReflectablePtr
        {
            return std::allocate_shared<::zserio::ReflectableOwner<DebugStringObject>>(allocator, allocator);
        },
        templateName, templateArguments,
        fields, parameters, functions
    };

    return typeInfo;
}

::zserio::IReflectableConstPtr DebugStringObject::reflectable(const allocator_type& allocator) const
{
    class Reflectable : public ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>
    {
    public:
        using ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>::getField;
        using ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>::getParameter;
        using ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>::callFunction;
        using ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>::getAnyValue;

        explicit Reflectable(const ::test_object::std_allocator::DebugStringObject& object, const allocator_type& allocator) :
                ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>(::test_object::std_allocator::DebugStringObject::typeInfo(), allocator),
                m_object(object)
        {}

        size_t bitSizeOf(size_t bitPosition) const override
        {
            return m_object.bitSizeOf(bitPosition);
        }

        void write(::zserio::BitStreamWriter& writer) const override
        {
            m_object.write(writer);
        }

        ::zserio::IReflectableConstPtr getField(::zserio::StringView name) const override
        {
            if (name == ::zserio::makeStringView("text"))
            {
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'DebugStringObject'!";
        }

        ::zserio::AnyHolder<> getAnyValue(const allocator_type& allocator) const override
        {
            return ::zserio::AnyHolder<>(::std::cref(m_object), allocator);
        }

    private:
        const ::test_object::std_allocator::DebugStringObject& m_object;
    };

    return std::allocate_shared<Reflectable>(allocator, *this, allocator);
}

::zserio::IReflectablePtr DebugStringObject::reflectable(const allocator_type& allocator)
{
    class Reflectable : public ::zserio::ReflectableAllocatorHolderBase<allocator_type>
    {
    public:
        explicit Reflectable(::test_object::std_allocator::DebugStringObject& object, const allocator_type& allocator) :
                ::zserio::ReflectableAllocatorHolderBase<allocator_type>(::test_object::std_allocator::DebugStringObject::typeInfo(), allocator),
                m_object(object)
        {}

        void initializeChildren() override
        {
        }

        size_t initializeOffsets(size_t bitPosition) override
        {
            return m_object.initializeOffsets(bitPosition);
        }

        size_t bitSizeOf(size_t bitPosition) const override
        {
            return m_object.bitSizeOf(bitPosition);
        }

        void write(::zserio::BitStreamWriter& writer) const override
        {
            m_object.write(writer);
        }

        ::zserio::IReflectableConstPtr getField(::zserio::StringView name) const override
        {
            if (name == ::zserio::makeStringView("text"))
            {
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'DebugStringObject'!";
        }

        ::zserio::IReflectablePtr getField(::zserio::StringView name) override
        {
            if (name == ::zserio::makeStringView("text"))
            {
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'DebugStringObject'!";
        }

        void setField(::zserio::StringView name,
                const ::zserio::AnyHolder<allocator_type>& value) override
        {
            if (name == ::zserio::makeStringView("text"))
            {
                m_object.setText(value.get<::zserio::string<>>());
                return;
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'DebugStringObject'!";
        }

        ::zserio::IReflectablePtr createField(::zserio::StringView name) override
        {
            if (name == ::zserio::makeStringView("text"))
            {
                m_object.setText(::zserio::string<>(get_allocator()));
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'DebugStringObject'!";
        }

        ::zserio::AnyHolder<> getAnyValue(const allocator_type& allocator) const override
        {
            return ::zserio::AnyHolder<>(::std::cref(m_object), allocator);
        }

        ::zserio::AnyHolder<> getAnyValue(const allocator_type& allocator) override
        {
            return ::zserio::AnyHolder<>(::std::ref(m_object), allocator);
        }

    private:
        ::test_object::std_allocator::DebugStringObject& m_object;
    };

    return std::allocate_shared<Reflectable>(allocator, *this, allocator);
}

::zserio::string<>& DebugStringObject::getText()
{
    return m_text_;
}

const ::zserio::string<>& DebugStringObject::getText() const
{
    return m_text_;
}

void DebugStringObject::setText(const ::zserio::string<>& text_)
{
    m_text_ = text_;
}

void DebugStringObject::setText(::zserio::string<>&& text_)
{
    m_text_ = ::std::move(text_);
}

void DebugStringObject::createPackingContext(::zserio::PackingContextNode& contextNode)
{
    contextNode.reserveChildren(1);

    contextNode.createChild();
}

void DebugStringObject::initPackingContext(::zserio::PackingContextNode&) const
{
}

size_t DebugStringObject::bitSizeOf(size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += ::zserio::bitSizeOfString(m_text_);

    return endBitPosition - bitPosition;
}

size_t DebugStringObject::bitSizeOf(::zserio::PackingContextNode&, size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += ::zserio::bitSizeOfString(m_text_);

    return endBitPosition - bitPosition;
}

size_t DebugStringObject::initializeOffsets(size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += ::zserio::bitSizeOfString(m_text_);

    return endBitPosition;
}

size_t DebugStringObject::initializeOffsets(::zserio::PackingContextNode&, size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += ::zserio::bitSizeOfString(m_text_);

    return endBitPosition;
}

bool DebugStringObject::operator==(const DebugStringObject& other) const
{
    if (this != &other)
    {
        return
                (m_text_ == other.m_text_);
    }

    return true;
}

uint32_t DebugStringObject::hashCode() const
{
    uint32_t result = ::zserio::HASH_SEED;

    result = ::zserio::calcHashCode(result, m_text_);

    return result;
}

void DebugStringObject::write(::zserio::BitStreamWriter& out) const
{
    out.writeString(m_text_);
}

void DebugStringObject::write(::zserio::PackingContextNode&, ::zserio::BitStreamWriter& out) const
{
    out.writeString(m_text_);
}

::zserio::string<> DebugStringObject::readText(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    return static_cast<::zserio::string<>>(in.readString(allocator));
}

} // namespace std_allocator
} // namespace test_object
