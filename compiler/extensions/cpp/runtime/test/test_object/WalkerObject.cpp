/**
 * Automatically generated by Zserio C++ extension version 2.9.0-pre1.
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
#include <functional>

#include <test_object/WalkerObject.h>

namespace test_object
{

WalkerObject::ZserioElementFactory_unionArray::ZserioElementFactory_unionArray(WalkerObject& owner) :
        m_ownerRef(owner)
{}

void WalkerObject::ZserioElementFactory_unionArray::create(::zserio::vector<::test_object::WalkerUnion>& array,
        ::zserio::BitStreamReader& in, size_t index) const
{
    (void)index;
    array.emplace_back(in, array.get_allocator());
}

void WalkerObject::ZserioElementFactory_unionArray::create(::zserio::PackingContextNode& contextNode,
        ::zserio::vector<::test_object::WalkerUnion>& array, ::zserio::BitStreamReader& in, size_t index) const
{
    (void)index;
    array.emplace_back(contextNode, in, array.get_allocator());
}

WalkerObject::ZserioElementFactory_optionalUnionArray::ZserioElementFactory_optionalUnionArray(WalkerObject& owner) :
        m_ownerRef(owner)
{}

void WalkerObject::ZserioElementFactory_optionalUnionArray::create(::zserio::vector<::test_object::WalkerUnion>& array,
        ::zserio::BitStreamReader& in, size_t index) const
{
    (void)index;
    array.emplace_back(in, array.get_allocator());
}

void WalkerObject::ZserioElementFactory_optionalUnionArray::create(::zserio::PackingContextNode& contextNode,
        ::zserio::vector<::test_object::WalkerUnion>& array, ::zserio::BitStreamReader& in, size_t index) const
{
    (void)index;
    array.emplace_back(contextNode, in, array.get_allocator());
}

WalkerObject::WalkerObject(const allocator_type& allocator) noexcept :
        m_identifier_(uint32_t()),
        m_nested_(::zserio::NullOpt),
        m_text_(allocator),
        m_unionArray_(::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_unionArray>(), allocator),
        m_optionalUnionArray_(::zserio::NullOpt)
{
}

WalkerObject::WalkerObject(::zserio::BitStreamReader& in, const allocator_type& allocator) :
        m_identifier_(readIdentifier(in)),
        m_nested_(readNested(in, allocator)),
        m_text_(readText(in, allocator)),
        m_unionArray_(readUnionArray(in, allocator)),
        m_optionalUnionArray_(readOptionalUnionArray(in, allocator))
{
}

WalkerObject::WalkerObject(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in, const allocator_type& allocator) :
        m_identifier_(readIdentifier(contextNode, in)),
        m_nested_(readNested(contextNode, in, allocator)),
        m_text_(readText(in, allocator)),
        m_unionArray_(readUnionArray(contextNode, in, allocator)),
        m_optionalUnionArray_(readOptionalUnionArray(contextNode, in, allocator))
{
}

WalkerObject::WalkerObject(::zserio::PropagateAllocatorT,
        const WalkerObject& other, const allocator_type& allocator) :
        m_identifier_(::zserio::allocatorPropagatingCopy(other.m_identifier_, allocator)),
        m_nested_(::zserio::allocatorPropagatingCopy(other.m_nested_, allocator)),
        m_text_(::zserio::allocatorPropagatingCopy(other.m_text_, allocator)),
        m_unionArray_(::zserio::allocatorPropagatingCopy(other.m_unionArray_, allocator)),
        m_optionalUnionArray_(::zserio::allocatorPropagatingCopy(other.m_optionalUnionArray_, allocator))
{
}

const ::zserio::ITypeInfo& WalkerObject::typeInfo()
{
    static const ::zserio::StringView templateName;
    static const ::zserio::Span<::zserio::BasicTemplateArgumentInfo<allocator_type>> templateArguments;

    static const ::std::array<::zserio::BasicFieldInfo<allocator_type>, 5> fields = {
        ::zserio::BasicFieldInfo<allocator_type>{
            ::zserio::makeStringView("identifier"), // schemaName
            ::zserio::BuiltinTypeInfo<allocator_type>::getUInt32(), // typeInfo
            {}, // typeArguments
            {}, // alignment
            {}, // offset
            {}, // initializer
            false, // isOptional
            {}, // optionalClause
            {}, // constraint
            false, // isArray
            {}, // arrayLength
            false, // isPacked
            false // isImplicit
        },
        ::zserio::BasicFieldInfo<allocator_type>{
            ::zserio::makeStringView("nested"), // schemaName
            ::test_object::WalkerNested::typeInfo(), // typeInfo
            {}, // typeArguments
            {}, // alignment
            {}, // offset
            {}, // initializer
            true, // isOptional
            ::zserio::makeStringView("getIdentifier() != 0"), // optionalClause
            {}, // constraint
            false, // isArray
            {}, // arrayLength
            false, // isPacked
            false // isImplicit
        },
        ::zserio::BasicFieldInfo<allocator_type>{
            ::zserio::makeStringView("text"), // schemaName
            ::zserio::BuiltinTypeInfo<allocator_type>::getString(), // typeInfo
            {}, // typeArguments
            {}, // alignment
            {}, // offset
            {}, // initializer
            false, // isOptional
            {}, // optionalClause
            {}, // constraint
            false, // isArray
            {}, // arrayLength
            false, // isPacked
            false // isImplicit
        },
        ::zserio::BasicFieldInfo<allocator_type>{
            ::zserio::makeStringView("unionArray"), // schemaName
            ::test_object::WalkerUnion::typeInfo(), // typeInfo
            {}, // typeArguments
            {}, // alignment
            {}, // offset
            {}, // initializer
            false, // isOptional
            {}, // optionalClause
            {}, // constraint
            true, // isArray
            {}, // arrayLength
            false, // isPacked
            false // isImplicit
        },
        ::zserio::BasicFieldInfo<allocator_type>{
            ::zserio::makeStringView("optionalUnionArray"), // schemaName
            ::test_object::WalkerUnion::typeInfo(), // typeInfo
            {}, // typeArguments
            {}, // alignment
            {}, // offset
            {}, // initializer
            true, // isOptional
            {}, // optionalClause
            {}, // constraint
            true, // isArray
            {}, // arrayLength
            false, // isPacked
            false // isImplicit
        }
    };

    static const ::zserio::Span<::zserio::BasicParameterInfo<allocator_type>> parameters;

    static const ::zserio::Span<::zserio::BasicFunctionInfo<allocator_type>> functions;

    static const ::zserio::StructTypeInfo<allocator_type> typeInfo = {
        ::zserio::makeStringView("test_object.WalkerObject"),
        [](const allocator_type& allocator) -> ::zserio::IReflectablePtr
        {
            return std::allocate_shared<::zserio::ReflectableOwner<WalkerObject>>(allocator, allocator);
        },
        templateName, templateArguments,
        fields, parameters, functions
    };

    return typeInfo;
}

::zserio::IReflectableConstPtr WalkerObject::reflectable(const allocator_type& allocator) const
{
    class Reflectable : public ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>
    {
    public:
        using ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>::getField;
        using ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>::getParameter;
        using ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>::callFunction;
        using ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>::getAnyValue;

        explicit Reflectable(const ::test_object::WalkerObject& object, const allocator_type& allocator) :
                ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>(::test_object::WalkerObject::typeInfo(), allocator),
                m_object(object)
        {}

        virtual size_t bitSizeOf(size_t bitPosition) const override
        {
            return m_object.bitSizeOf(bitPosition);
        }

        virtual void write(::zserio::BitStreamWriter& writer) const override
        {
            m_object.write(writer);
        }

        virtual ::zserio::IReflectableConstPtr getField(::zserio::StringView name) const override
        {
            if (name == ::zserio::makeStringView("identifier"))
            {
                return ::zserio::ReflectableFactory::getUInt32(m_object.getIdentifier(), get_allocator());
            }
            if (name == ::zserio::makeStringView("nested"))
            {
                if (!m_object.isNestedSet())
                    return nullptr;

                return m_object.getNested().reflectable(get_allocator());
            }
            if (name == ::zserio::makeStringView("text"))
            {
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            if (name == ::zserio::makeStringView("unionArray"))
            {
                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getUnionArray(), get_allocator());
            }
            if (name == ::zserio::makeStringView("optionalUnionArray"))
            {
                if (!m_object.isOptionalUnionArraySet())
                    return nullptr;

                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getOptionalUnionArray(), get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        virtual ::zserio::AnyHolder<> getAnyValue(const allocator_type& allocator) const override
        {
            return ::zserio::AnyHolder<>(::std::cref(m_object), allocator);
        }

    private:
        const ::test_object::WalkerObject& m_object;
    };

    return std::allocate_shared<Reflectable>(allocator, *this, allocator);
}

::zserio::IReflectablePtr WalkerObject::reflectable(const allocator_type& allocator)
{
    class Reflectable : public ::zserio::ReflectableAllocatorHolderBase<allocator_type>
    {
    public:
        explicit Reflectable(::test_object::WalkerObject& object, const allocator_type& allocator) :
                ::zserio::ReflectableAllocatorHolderBase<allocator_type>(::test_object::WalkerObject::typeInfo(), allocator),
                m_object(object)
        {}

        virtual void initializeChildren() override
        {
        }

        virtual size_t initializeOffsets(size_t bitPosition) override
        {
            return m_object.initializeOffsets(bitPosition);
        }

        virtual size_t bitSizeOf(size_t bitPosition) const override
        {
            return m_object.bitSizeOf(bitPosition);
        }

        virtual void write(::zserio::BitStreamWriter& writer) const override
        {
            m_object.write(writer);
        }

        virtual ::zserio::IReflectableConstPtr getField(::zserio::StringView name) const override
        {
            if (name == ::zserio::makeStringView("identifier"))
            {
                return ::zserio::ReflectableFactory::getUInt32(m_object.getIdentifier(), get_allocator());
            }
            if (name == ::zserio::makeStringView("nested"))
            {
                if (!m_object.isNestedSet())
                    return nullptr;

                return m_object.getNested().reflectable(get_allocator());
            }
            if (name == ::zserio::makeStringView("text"))
            {
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            if (name == ::zserio::makeStringView("unionArray"))
            {
                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getUnionArray(), get_allocator());
            }
            if (name == ::zserio::makeStringView("optionalUnionArray"))
            {
                if (!m_object.isOptionalUnionArraySet())
                    return nullptr;

                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getOptionalUnionArray(), get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        virtual ::zserio::IReflectablePtr getField(::zserio::StringView name) override
        {
            if (name == ::zserio::makeStringView("identifier"))
            {
                return ::zserio::ReflectableFactory::getUInt32(m_object.getIdentifier(), get_allocator());
            }
            if (name == ::zserio::makeStringView("nested"))
            {
                if (!m_object.isNestedSet())
                    return nullptr;

                return m_object.getNested().reflectable(get_allocator());
            }
            if (name == ::zserio::makeStringView("text"))
            {
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            if (name == ::zserio::makeStringView("unionArray"))
            {
                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getUnionArray(), get_allocator());
            }
            if (name == ::zserio::makeStringView("optionalUnionArray"))
            {
                if (!m_object.isOptionalUnionArraySet())
                    return nullptr;

                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getOptionalUnionArray(), get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        virtual void setField(::zserio::StringView name,
                const ::zserio::AnyHolder<allocator_type>& value) override
        {
            if (name == ::zserio::makeStringView("identifier"))
            {
                m_object.setIdentifier(value.get<uint32_t>());
                return;
            }
            if (name == ::zserio::makeStringView("nested"))
            {
                if (value.isType<::std::nullptr_t>())
                {
                    m_object.resetNested();
                    return;
                }

                m_object.setNested(value.get<::test_object::WalkerNested>());
                return;
            }
            if (name == ::zserio::makeStringView("text"))
            {
                m_object.setText(value.get<::zserio::string<>>());
                return;
            }
            if (name == ::zserio::makeStringView("unionArray"))
            {
                m_object.setUnionArray(value.get<::zserio::vector<::test_object::WalkerUnion>>());
                return;
            }
            if (name == ::zserio::makeStringView("optionalUnionArray"))
            {
                if (value.isType<::std::nullptr_t>())
                {
                    m_object.resetOptionalUnionArray();
                    return;
                }

                m_object.setOptionalUnionArray(value.get<::zserio::vector<::test_object::WalkerUnion>>());
                return;
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        virtual ::zserio::IReflectablePtr createField(::zserio::StringView name) override
        {
            if (name == ::zserio::makeStringView("identifier"))
            {
                m_object.setIdentifier(uint32_t());
                return ::zserio::ReflectableFactory::getUInt32(m_object.getIdentifier(), get_allocator());
            }
            if (name == ::zserio::makeStringView("nested"))
            {
                m_object.setNested(::test_object::WalkerNested(get_allocator()));
                return m_object.getNested().reflectable(get_allocator());
            }
            if (name == ::zserio::makeStringView("text"))
            {
                m_object.setText(::zserio::string<>(get_allocator()));
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            if (name == ::zserio::makeStringView("unionArray"))
            {
                m_object.setUnionArray(::zserio::vector<::test_object::WalkerUnion>(get_allocator()));
                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getUnionArray(), get_allocator());
            }
            if (name == ::zserio::makeStringView("optionalUnionArray"))
            {
                m_object.setOptionalUnionArray(::zserio::vector<::test_object::WalkerUnion>(get_allocator()));
                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getOptionalUnionArray(), get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        virtual ::zserio::AnyHolder<> getAnyValue(const allocator_type& allocator) const override
        {
            return ::zserio::AnyHolder<>(::std::cref(m_object), allocator);
        }

        virtual ::zserio::AnyHolder<> getAnyValue(const allocator_type& allocator) override
        {
            return ::zserio::AnyHolder<>(::std::ref(m_object), allocator);
        }

    private:
        ::test_object::WalkerObject& m_object;
    };

    return std::allocate_shared<Reflectable>(allocator, *this, allocator);
}

uint32_t WalkerObject::getIdentifier() const
{
    return m_identifier_;
}

void WalkerObject::setIdentifier(uint32_t identifier_)
{
    m_identifier_ = identifier_;
}

::test_object::WalkerNested& WalkerObject::getNested()
{
    return m_nested_.value();
}

const ::test_object::WalkerNested& WalkerObject::getNested() const
{
    return m_nested_.value();
}

void WalkerObject::setNested(const ::test_object::WalkerNested& nested_)
{
    m_nested_ = nested_;
}

void WalkerObject::setNested(::test_object::WalkerNested&& nested_)
{
    m_nested_ = ::std::move(nested_);
}

bool WalkerObject::isNestedUsed() const
{
    return (getIdentifier() != 0);
}

bool WalkerObject::isNestedSet() const
{
    return m_nested_.hasValue();
}

void WalkerObject::resetNested()
{
    m_nested_.reset();
}

::zserio::string<>& WalkerObject::getText()
{
    return m_text_;
}

const ::zserio::string<>& WalkerObject::getText() const
{
    return m_text_;
}

void WalkerObject::setText(const ::zserio::string<>& text_)
{
    m_text_ = text_;
}

void WalkerObject::setText(::zserio::string<>&& text_)
{
    m_text_ = ::std::move(text_);
}

::zserio::vector<::test_object::WalkerUnion>& WalkerObject::getUnionArray()
{
    return m_unionArray_.getRawArray();
}

const ::zserio::vector<::test_object::WalkerUnion>& WalkerObject::getUnionArray() const
{
    return m_unionArray_.getRawArray();
}

void WalkerObject::setUnionArray(const ::zserio::vector<::test_object::WalkerUnion>& unionArray_)
{
    m_unionArray_ = ZserioArrayType_unionArray(unionArray_, ::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_unionArray>());
}

void WalkerObject::setUnionArray(::zserio::vector<::test_object::WalkerUnion>&& unionArray_)
{
    m_unionArray_ = ZserioArrayType_unionArray(std::move(unionArray_), ::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_unionArray>());
}

::zserio::vector<::test_object::WalkerUnion>& WalkerObject::getOptionalUnionArray()
{
    return m_optionalUnionArray_.value().getRawArray();
}

const ::zserio::vector<::test_object::WalkerUnion>& WalkerObject::getOptionalUnionArray() const
{
    return m_optionalUnionArray_.value().getRawArray();
}

void WalkerObject::setOptionalUnionArray(const ::zserio::vector<::test_object::WalkerUnion>& optionalUnionArray_)
{
    m_optionalUnionArray_ = ZserioArrayType_optionalUnionArray(optionalUnionArray_, ::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_optionalUnionArray>());
}

void WalkerObject::setOptionalUnionArray(::zserio::vector<::test_object::WalkerUnion>&& optionalUnionArray_)
{
    m_optionalUnionArray_ = ZserioArrayType_optionalUnionArray(std::move(optionalUnionArray_), ::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_optionalUnionArray>());
}

bool WalkerObject::isOptionalUnionArrayUsed() const
{
    return (isOptionalUnionArraySet());
}

bool WalkerObject::isOptionalUnionArraySet() const
{
    return m_optionalUnionArray_.hasValue();
}

void WalkerObject::resetOptionalUnionArray()
{
    m_optionalUnionArray_.reset();
}

void WalkerObject::createPackingContext(::zserio::PackingContextNode& contextNode)
{
    contextNode.createChild().createContext();
    ::test_object::WalkerNested::createPackingContext(contextNode.createChild());
    contextNode.createChild();
    contextNode.createChild();
    contextNode.createChild();
}

void WalkerObject::initPackingContext(::zserio::PackingContextNode& contextNode) const
{
    contextNode.getChildren().at(0).getContext().init(
            ::zserio::StdIntArrayTraits<uint32_t>(), m_identifier_);
    if (getIdentifier() != 0)
    {
        m_nested_.value().initPackingContext(contextNode.getChildren().at(1));
    }
}

size_t WalkerObject::bitSizeOf(size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(32);
    if (getIdentifier() != 0)
    {
        endBitPosition += m_nested_.value().bitSizeOf(endBitPosition);
    }
    endBitPosition += ::zserio::bitSizeOfString(m_text_);
    endBitPosition += m_unionArray_.bitSizeOf(endBitPosition);
    endBitPosition += 1;
    if (isOptionalUnionArraySet())
    {
        endBitPosition += m_optionalUnionArray_.value().bitSizeOf(endBitPosition);
    }

    return endBitPosition - bitPosition;
}

size_t WalkerObject::bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += contextNode.getChildren().at(0).getContext().bitSizeOf(
            ::zserio::StdIntArrayTraits<uint32_t>(), m_identifier_);
    if (getIdentifier() != 0)
    {
        endBitPosition += m_nested_.value().bitSizeOf(
                contextNode.getChildren().at(1), endBitPosition);
    }
    endBitPosition += ::zserio::bitSizeOfString(m_text_);
    endBitPosition += m_unionArray_.bitSizeOfPacked(endBitPosition);
    endBitPosition += 1;
    if (isOptionalUnionArraySet())
    {
        endBitPosition += m_optionalUnionArray_.value().bitSizeOfPacked(endBitPosition);
    }

    return endBitPosition - bitPosition;
}

size_t WalkerObject::initializeOffsets(size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += UINT8_C(32);
    if (getIdentifier() != 0)
    {
        endBitPosition = m_nested_.value().initializeOffsets(endBitPosition);
    }
    endBitPosition += ::zserio::bitSizeOfString(m_text_);
    endBitPosition = m_unionArray_.initializeOffsets(
            endBitPosition);
    endBitPosition += 1;
    if (isOptionalUnionArraySet())
    {
        endBitPosition = m_optionalUnionArray_.value().initializeOffsets(
                endBitPosition);
    }

    return endBitPosition;
}

size_t WalkerObject::initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += contextNode.getChildren().at(0).getContext().bitSizeOf(
            ::zserio::StdIntArrayTraits<uint32_t>(), m_identifier_);
    if (getIdentifier() != 0)
    {
        endBitPosition = m_nested_.value().initializeOffsets(
                contextNode.getChildren().at(1), endBitPosition);
    }
    endBitPosition += ::zserio::bitSizeOfString(m_text_);
    endBitPosition = m_unionArray_.initializeOffsetsPacked(
            endBitPosition);
    endBitPosition += 1;
    if (isOptionalUnionArraySet())
    {
        endBitPosition = m_optionalUnionArray_.value().initializeOffsetsPacked(
                endBitPosition);
    }

    return endBitPosition;
}

bool WalkerObject::operator==(const WalkerObject& other) const
{
    if (this != &other)
    {
        return
                (m_identifier_ == other.m_identifier_) &&
                ((!isNestedUsed()) ? !other.isNestedUsed() : (m_nested_ == other.m_nested_)) &&
                (m_text_ == other.m_text_) &&
                (m_unionArray_ == other.m_unionArray_) &&
                ((!isOptionalUnionArrayUsed()) ? !other.isOptionalUnionArrayUsed() : (m_optionalUnionArray_ == other.m_optionalUnionArray_));
    }

    return true;
}

uint32_t WalkerObject::hashCode() const
{
    uint32_t result = ::zserio::HASH_SEED;

    result = ::zserio::calcHashCode(result, m_identifier_);
    if (isNestedUsed())
        result = ::zserio::calcHashCode(result, m_nested_);
    result = ::zserio::calcHashCode(result, m_text_);
    result = ::zserio::calcHashCode(result, m_unionArray_);
    if (isOptionalUnionArrayUsed())
        result = ::zserio::calcHashCode(result, m_optionalUnionArray_);

    return result;
}

void WalkerObject::write(::zserio::BitStreamWriter& out) const
{
    out.writeBits(m_identifier_, UINT8_C(32));
    if (getIdentifier() != 0)
    {
        m_nested_.value().write(out);
    }
    out.writeString(m_text_);
    m_unionArray_.write(out);
    if (isOptionalUnionArraySet())
    {
        out.writeBool(true);
        m_optionalUnionArray_.value().write(out);
    }
    else
    {
        out.writeBool(false);
    }
}

void WalkerObject::write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const
{
    contextNode.getChildren().at(0).getContext().write(
            ::zserio::StdIntArrayTraits<uint32_t>(), out, m_identifier_);
    if (getIdentifier() != 0)
    {
        m_nested_.value().write(contextNode.getChildren().at(1), out);
    }
    out.writeString(m_text_);
    m_unionArray_.writePacked(out);
    if (isOptionalUnionArraySet())
    {
        out.writeBool(true);
        m_optionalUnionArray_.value().writePacked(out);
    }
    else
    {
        out.writeBool(false);
    }
}

uint32_t WalkerObject::readIdentifier(::zserio::BitStreamReader& in)
{
    return static_cast<uint32_t>(in.readBits(UINT8_C(32)));
}

uint32_t WalkerObject::readIdentifier(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in)
{
    return contextNode.getChildren().at(0).getContext().read(::zserio::StdIntArrayTraits<uint32_t>(), in);
}

::zserio::InplaceOptionalHolder<::test_object::WalkerNested> WalkerObject::readNested(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    if (getIdentifier() != 0)
    {
        return ::zserio::InplaceOptionalHolder<::test_object::WalkerNested>(::test_object::WalkerNested(in, allocator));
    }

    return ::zserio::InplaceOptionalHolder<::test_object::WalkerNested>(::zserio::NullOpt);
}

::zserio::InplaceOptionalHolder<::test_object::WalkerNested> WalkerObject::readNested(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in, const allocator_type& allocator)
{
    if (getIdentifier() != 0)
    {
        return ::zserio::InplaceOptionalHolder<::test_object::WalkerNested>(::test_object::WalkerNested(contextNode.getChildren().at(1), in, allocator));
    }

    return ::zserio::InplaceOptionalHolder<::test_object::WalkerNested>(::zserio::NullOpt);
}

::zserio::string<> WalkerObject::readText(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    return static_cast<::zserio::string<>>(in.readString(allocator));
}

WalkerObject::ZserioArrayType_unionArray WalkerObject::readUnionArray(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    ZserioArrayType_unionArray readField(::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_unionArray>(), allocator);
    readField.read(in, ZserioElementFactory_unionArray(*this));

    return readField;
}

WalkerObject::ZserioArrayType_unionArray WalkerObject::readUnionArray(::zserio::PackingContextNode&, ::zserio::BitStreamReader& in, const allocator_type& allocator)
{
    ZserioArrayType_unionArray readField(::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_unionArray>(), allocator);
    readField.readPacked(in, ZserioElementFactory_unionArray(*this));

    return readField;
}

::zserio::InplaceOptionalHolder<WalkerObject::ZserioArrayType_optionalUnionArray> WalkerObject::readOptionalUnionArray(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    if (in.readBool())
    {
        ZserioArrayType_optionalUnionArray readField(::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_optionalUnionArray>(), allocator);
        readField.read(in, ZserioElementFactory_optionalUnionArray(*this));

        return ::zserio::InplaceOptionalHolder<ZserioArrayType_optionalUnionArray>(::std::move(readField));
    }

    return ::zserio::InplaceOptionalHolder<ZserioArrayType_optionalUnionArray>(::zserio::NullOpt);
}

::zserio::InplaceOptionalHolder<WalkerObject::ZserioArrayType_optionalUnionArray> WalkerObject::readOptionalUnionArray(::zserio::PackingContextNode&, ::zserio::BitStreamReader& in, const allocator_type& allocator)
{
    if (in.readBool())
    {
        ZserioArrayType_optionalUnionArray readField(::zserio::ObjectArrayTraits<::test_object::WalkerUnion, ZserioElementFactory_optionalUnionArray>(), allocator);
        readField.readPacked(in, ZserioElementFactory_optionalUnionArray(*this));

        return ::zserio::InplaceOptionalHolder<ZserioArrayType_optionalUnionArray>(::std::move(readField));
    }

    return ::zserio::InplaceOptionalHolder<ZserioArrayType_optionalUnionArray>(::zserio::NullOpt);
}

} // namespace test_object
