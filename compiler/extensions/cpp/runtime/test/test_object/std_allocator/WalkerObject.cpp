/**
 * Automatically generated by Zserio C++ extension version 2.12.0.
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

#include <test_object/std_allocator/WalkerObject.h>

namespace test_object
{
namespace std_allocator
{

WalkerObject::WalkerObject(const allocator_type& allocator) noexcept :
        m_areChildrenInitialized(false),
        m_identifier_(uint32_t()),
        m_nested_(::zserio::NullOpt),
        m_text_(allocator),
        m_unionArray_(allocator),
        m_optionalUnionArray_(::zserio::NullOpt),
        m_choiceSelector_(uint8_t()),
        m_choiceField_(allocator)
{
}

WalkerObject::WalkerObject(::zserio::BitStreamReader& in, const allocator_type& allocator) :
        m_areChildrenInitialized(true),
        m_identifier_(readIdentifier(in)),
        m_nested_(readNested(in, allocator)),
        m_text_(readText(in, allocator)),
        m_unionArray_(readUnionArray(in, allocator)),
        m_optionalUnionArray_(readOptionalUnionArray(in, allocator)),
        m_choiceSelector_(readChoiceSelector(in)),
        m_choiceField_(readChoiceField(in, allocator))
{
}

WalkerObject::WalkerObject(WalkerObject::ZserioPackingContext& context, ::zserio::BitStreamReader& in, const allocator_type& allocator) :
        m_areChildrenInitialized(true),
        m_identifier_(readIdentifier(context, in)),
        m_nested_(readNested(in, allocator)),
        m_text_(readText(in, allocator)),
        m_unionArray_(readUnionArray(context, in, allocator)),
        m_optionalUnionArray_(readOptionalUnionArray(context, in, allocator)),
        m_choiceSelector_(readChoiceSelector(context, in)),
        m_choiceField_(readChoiceField(context, in, allocator))
{
}

WalkerObject::WalkerObject(const WalkerObject& other) :
        m_identifier_(other.m_identifier_),
        m_nested_(other.m_nested_),
        m_text_(other.m_text_),
        m_unionArray_(other.m_unionArray_),
        m_optionalUnionArray_(other.m_optionalUnionArray_),
        m_choiceSelector_(other.m_choiceSelector_),
        m_choiceField_(::zserio::NoInit, other.m_choiceField_)
{
    if (other.m_areChildrenInitialized)
        initializeChildren();
    else
        m_areChildrenInitialized = false;
}

WalkerObject& WalkerObject::operator=(const WalkerObject& other)
{
    m_identifier_ = other.m_identifier_;
    m_nested_ = other.m_nested_;
    m_text_ = other.m_text_;
    m_unionArray_ = other.m_unionArray_;
    m_optionalUnionArray_ = other.m_optionalUnionArray_;
    m_choiceSelector_ = other.m_choiceSelector_;
    m_choiceField_.assign(::zserio::NoInit, other.m_choiceField_);
    if (other.m_areChildrenInitialized)
        initializeChildren();
    else
        m_areChildrenInitialized = false;

    return *this;
}

WalkerObject::WalkerObject(WalkerObject&& other) :
        m_identifier_(::std::move(other.m_identifier_)),
        m_nested_(::std::move(other.m_nested_)),
        m_text_(::std::move(other.m_text_)),
        m_unionArray_(::std::move(other.m_unionArray_)),
        m_optionalUnionArray_(::std::move(other.m_optionalUnionArray_)),
        m_choiceSelector_(::std::move(other.m_choiceSelector_)),
        m_choiceField_(::zserio::NoInit, ::std::move(other.m_choiceField_))
{
    if (other.m_areChildrenInitialized)
        initializeChildren();
    else
        m_areChildrenInitialized = false;
}

WalkerObject& WalkerObject::operator=(WalkerObject&& other)
{
    m_identifier_ = ::std::move(other.m_identifier_);
    m_nested_ = ::std::move(other.m_nested_);
    m_text_ = ::std::move(other.m_text_);
    m_unionArray_ = ::std::move(other.m_unionArray_);
    m_optionalUnionArray_ = ::std::move(other.m_optionalUnionArray_);
    m_choiceSelector_ = ::std::move(other.m_choiceSelector_);
    m_choiceField_.assign(::zserio::NoInit, ::std::move(other.m_choiceField_));
    if (other.m_areChildrenInitialized)
        initializeChildren();
    else
        m_areChildrenInitialized = false;

    return *this;
}

WalkerObject::WalkerObject(::zserio::PropagateAllocatorT,
        const WalkerObject& other, const allocator_type& allocator) :
        m_identifier_(::zserio::allocatorPropagatingCopy(other.m_identifier_, allocator)),
        m_nested_(::zserio::allocatorPropagatingCopy(other.m_nested_, allocator)),
        m_text_(::zserio::allocatorPropagatingCopy(other.m_text_, allocator)),
        m_unionArray_(::zserio::allocatorPropagatingCopy(other.m_unionArray_, allocator)),
        m_optionalUnionArray_(::zserio::allocatorPropagatingCopy(other.m_optionalUnionArray_, allocator)),
        m_choiceSelector_(::zserio::allocatorPropagatingCopy(other.m_choiceSelector_, allocator)),
        m_choiceField_(::zserio::NoInit, ::zserio::allocatorPropagatingCopy(::zserio::NoInit, other.m_choiceField_, allocator))
{
    if (other.m_areChildrenInitialized)
        initializeChildren();
    else
        m_areChildrenInitialized = false;
}

const ::zserio::ITypeInfo& WalkerObject::typeInfo()
{
    static const ::zserio::StringView templateName;
    static const ::zserio::Span<::zserio::BasicTemplateArgumentInfo<allocator_type>> templateArguments;

    static const ::std::array<::zserio::StringView, 1> choiceFieldTypeArguments = {
        ::zserio::makeStringView("getChoiceSelector()")
    };
    static const ::std::array<::zserio::BasicFieldInfo<allocator_type>, 7> fields = {
        ::zserio::BasicFieldInfo<allocator_type>{
            ::zserio::makeStringView("identifier"), // schemaName
            ::zserio::BuiltinTypeInfo<allocator_type>::getUInt32(), // typeInfo
            {}, // typeArguments
            false, // isExtended
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
            ::test_object::std_allocator::WalkerNested::typeInfo(), // typeInfo
            {}, // typeArguments
            false, // isExtended
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
            false, // isExtended
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
            ::test_object::std_allocator::WalkerUnion::typeInfo(), // typeInfo
            {}, // typeArguments
            false, // isExtended
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
            ::test_object::std_allocator::WalkerUnion::typeInfo(), // typeInfo
            {}, // typeArguments
            false, // isExtended
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
        },
        ::zserio::BasicFieldInfo<allocator_type>{
            ::zserio::makeStringView("choiceSelector"), // schemaName
            ::zserio::BuiltinTypeInfo<allocator_type>::getUInt8(), // typeInfo
            {}, // typeArguments
            false, // isExtended
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
            ::zserio::makeStringView("choiceField"), // schemaName
            ::test_object::std_allocator::WalkerChoice::typeInfo(), // typeInfo
            choiceFieldTypeArguments, // typeArguments
            false, // isExtended
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
        }
    };

    static const ::zserio::Span<::zserio::BasicParameterInfo<allocator_type>> parameters;

    static const ::zserio::Span<::zserio::BasicFunctionInfo<allocator_type>> functions;

    static const ::zserio::StructTypeInfo<allocator_type> typeInfo = {
        ::zserio::makeStringView("test_object.std_allocator.WalkerObject"),
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

        explicit Reflectable(const ::test_object::std_allocator::WalkerObject& object, const allocator_type& allocator) :
                ::zserio::ReflectableConstAllocatorHolderBase<allocator_type>(::test_object::std_allocator::WalkerObject::typeInfo(), allocator),
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
            if (name == ::zserio::makeStringView("choiceSelector"))
            {
                return ::zserio::ReflectableFactory::getUInt8(m_object.getChoiceSelector(), get_allocator());
            }
            if (name == ::zserio::makeStringView("choiceField"))
            {
                return m_object.getChoiceField().reflectable(get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        ::zserio::AnyHolder<> getAnyValue(const allocator_type& allocator) const override
        {
            return ::zserio::AnyHolder<>(::std::cref(m_object), allocator);
        }

    private:
        const ::test_object::std_allocator::WalkerObject& m_object;
    };

    return std::allocate_shared<Reflectable>(allocator, *this, allocator);
}

::zserio::IReflectablePtr WalkerObject::reflectable(const allocator_type& allocator)
{
    class Reflectable : public ::zserio::ReflectableAllocatorHolderBase<allocator_type>
    {
    public:
        explicit Reflectable(::test_object::std_allocator::WalkerObject& object, const allocator_type& allocator) :
                ::zserio::ReflectableAllocatorHolderBase<allocator_type>(::test_object::std_allocator::WalkerObject::typeInfo(), allocator),
                m_object(object)
        {}

        void initializeChildren() override
        {
            m_object.initializeChildren();
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
            if (name == ::zserio::makeStringView("choiceSelector"))
            {
                return ::zserio::ReflectableFactory::getUInt8(m_object.getChoiceSelector(), get_allocator());
            }
            if (name == ::zserio::makeStringView("choiceField"))
            {
                return m_object.getChoiceField().reflectable(get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        ::zserio::IReflectablePtr getField(::zserio::StringView name) override
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
            if (name == ::zserio::makeStringView("choiceSelector"))
            {
                return ::zserio::ReflectableFactory::getUInt8(m_object.getChoiceSelector(), get_allocator());
            }
            if (name == ::zserio::makeStringView("choiceField"))
            {
                return m_object.getChoiceField().reflectable(get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        void setField(::zserio::StringView name,
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

                m_object.setNested(value.get<::test_object::std_allocator::WalkerNested>());
                return;
            }
            if (name == ::zserio::makeStringView("text"))
            {
                m_object.setText(value.get<::zserio::string<>>());
                return;
            }
            if (name == ::zserio::makeStringView("unionArray"))
            {
                m_object.setUnionArray(value.get<::zserio::vector<::test_object::std_allocator::WalkerUnion>>());
                return;
            }
            if (name == ::zserio::makeStringView("optionalUnionArray"))
            {
                if (value.isType<::std::nullptr_t>())
                {
                    m_object.resetOptionalUnionArray();
                    return;
                }

                m_object.setOptionalUnionArray(value.get<::zserio::vector<::test_object::std_allocator::WalkerUnion>>());
                return;
            }
            if (name == ::zserio::makeStringView("choiceSelector"))
            {
                m_object.setChoiceSelector(value.get<uint8_t>());
                return;
            }
            if (name == ::zserio::makeStringView("choiceField"))
            {
                m_object.setChoiceField(value.get<::test_object::std_allocator::WalkerChoice>());
                return;
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
        }

        ::zserio::IReflectablePtr createField(::zserio::StringView name) override
        {
            if (name == ::zserio::makeStringView("identifier"))
            {
                m_object.setIdentifier(uint32_t());
                return ::zserio::ReflectableFactory::getUInt32(m_object.getIdentifier(), get_allocator());
            }
            if (name == ::zserio::makeStringView("nested"))
            {
                m_object.setNested(::test_object::std_allocator::WalkerNested(get_allocator()));
                return m_object.getNested().reflectable(get_allocator());
            }
            if (name == ::zserio::makeStringView("text"))
            {
                m_object.setText(::zserio::string<>(get_allocator()));
                return ::zserio::ReflectableFactory::getString(m_object.getText(), get_allocator());
            }
            if (name == ::zserio::makeStringView("unionArray"))
            {
                m_object.setUnionArray(::zserio::vector<::test_object::std_allocator::WalkerUnion>(get_allocator()));
                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getUnionArray(), get_allocator());
            }
            if (name == ::zserio::makeStringView("optionalUnionArray"))
            {
                m_object.setOptionalUnionArray(::zserio::vector<::test_object::std_allocator::WalkerUnion>(get_allocator()));
                return ::zserio::ReflectableFactory::getCompoundArray(m_object.getOptionalUnionArray(), get_allocator());
            }
            if (name == ::zserio::makeStringView("choiceSelector"))
            {
                m_object.setChoiceSelector(uint8_t());
                return ::zserio::ReflectableFactory::getUInt8(m_object.getChoiceSelector(), get_allocator());
            }
            if (name == ::zserio::makeStringView("choiceField"))
            {
                m_object.setChoiceField(::test_object::std_allocator::WalkerChoice(get_allocator()));
                return m_object.getChoiceField().reflectable(get_allocator());
            }
            throw ::zserio::CppRuntimeException("Field '") << name << "' doesn't exist in 'WalkerObject'!";
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
        ::test_object::std_allocator::WalkerObject& m_object;
    };

    return std::allocate_shared<Reflectable>(allocator, *this, allocator);
}

void WalkerObject::initializeChildren()
{
    m_choiceField_.initialize(static_cast<uint8_t>(getChoiceSelector()));

    m_areChildrenInitialized = true;
}

uint32_t WalkerObject::getIdentifier() const
{
    return m_identifier_;
}

void WalkerObject::setIdentifier(uint32_t identifier_)
{
    m_identifier_ = identifier_;
}

::test_object::std_allocator::WalkerNested& WalkerObject::getNested()
{
    return m_nested_.value();
}

const ::test_object::std_allocator::WalkerNested& WalkerObject::getNested() const
{
    return m_nested_.value();
}

void WalkerObject::setNested(const ::test_object::std_allocator::WalkerNested& nested_)
{
    m_nested_ = nested_;
}

void WalkerObject::setNested(::test_object::std_allocator::WalkerNested&& nested_)
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

::zserio::vector<::test_object::std_allocator::WalkerUnion>& WalkerObject::getUnionArray()
{
    return m_unionArray_.getRawArray();
}

const ::zserio::vector<::test_object::std_allocator::WalkerUnion>& WalkerObject::getUnionArray() const
{
    return m_unionArray_.getRawArray();
}

void WalkerObject::setUnionArray(const ::zserio::vector<::test_object::std_allocator::WalkerUnion>& unionArray_)
{
    m_unionArray_ = ZserioArrayType_unionArray(unionArray_);
}

void WalkerObject::setUnionArray(::zserio::vector<::test_object::std_allocator::WalkerUnion>&& unionArray_)
{
    m_unionArray_ = ZserioArrayType_unionArray(std::move(unionArray_));
}

::zserio::vector<::test_object::std_allocator::WalkerUnion>& WalkerObject::getOptionalUnionArray()
{
    return m_optionalUnionArray_.value().getRawArray();
}

const ::zserio::vector<::test_object::std_allocator::WalkerUnion>& WalkerObject::getOptionalUnionArray() const
{
    return m_optionalUnionArray_.value().getRawArray();
}

void WalkerObject::setOptionalUnionArray(const ::zserio::vector<::test_object::std_allocator::WalkerUnion>& optionalUnionArray_)
{
    m_optionalUnionArray_ = ZserioArrayType_optionalUnionArray(optionalUnionArray_);
}

void WalkerObject::setOptionalUnionArray(::zserio::vector<::test_object::std_allocator::WalkerUnion>&& optionalUnionArray_)
{
    m_optionalUnionArray_ = ZserioArrayType_optionalUnionArray(std::move(optionalUnionArray_));
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

uint8_t WalkerObject::getChoiceSelector() const
{
    return m_choiceSelector_;
}

void WalkerObject::setChoiceSelector(uint8_t choiceSelector_)
{
    m_choiceSelector_ = choiceSelector_;
}

::test_object::std_allocator::WalkerChoice& WalkerObject::getChoiceField()
{
    return m_choiceField_;
}

const ::test_object::std_allocator::WalkerChoice& WalkerObject::getChoiceField() const
{
    return m_choiceField_;
}

void WalkerObject::setChoiceField(const ::test_object::std_allocator::WalkerChoice& choiceField_)
{
    m_choiceField_ = choiceField_;
}

void WalkerObject::setChoiceField(::test_object::std_allocator::WalkerChoice&& choiceField_)
{
    m_choiceField_ = ::std::move(choiceField_);
}

void WalkerObject::initPackingContext(WalkerObject::ZserioPackingContext& context) const
{
    context.getIdentifier().init<::zserio::StdIntArrayTraits<uint32_t>>(m_identifier_);
    context.getChoiceSelector().init<::zserio::StdIntArrayTraits<uint8_t>>(m_choiceSelector_);
    m_choiceField_.initPackingContext(context.getChoiceField());
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
    endBitPosition += m_unionArray_.bitSizeOf(*this, endBitPosition);
    endBitPosition += 1;
    if (isOptionalUnionArraySet())
    {
        endBitPosition += m_optionalUnionArray_.value().bitSizeOf(*this, endBitPosition);
    }
    endBitPosition += UINT8_C(8);
    endBitPosition += m_choiceField_.bitSizeOf(endBitPosition);

    return endBitPosition - bitPosition;
}

size_t WalkerObject::bitSizeOf(WalkerObject::ZserioPackingContext& context, size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    endBitPosition += context.getIdentifier().bitSizeOf<::zserio::StdIntArrayTraits<uint32_t>>(m_identifier_);
    if (getIdentifier() != 0)
    {
        endBitPosition += m_nested_.value().bitSizeOf(endBitPosition);
    }
    endBitPosition += ::zserio::bitSizeOfString(m_text_);
    endBitPosition += m_unionArray_.bitSizeOfPacked(*this, endBitPosition);
    endBitPosition += 1;
    if (isOptionalUnionArraySet())
    {
        endBitPosition += m_optionalUnionArray_.value().bitSizeOfPacked(*this, endBitPosition);
    }
    endBitPosition += context.getChoiceSelector().bitSizeOf<::zserio::StdIntArrayTraits<uint8_t>>(m_choiceSelector_);
    endBitPosition += m_choiceField_.bitSizeOf(context.getChoiceField(), endBitPosition);

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
    endBitPosition = m_unionArray_.initializeOffsets(*this, endBitPosition);
    endBitPosition += 1;
    if (isOptionalUnionArraySet())
    {
        endBitPosition = m_optionalUnionArray_.value().initializeOffsets(*this, endBitPosition);
    }
    endBitPosition += UINT8_C(8);
    endBitPosition = m_choiceField_.initializeOffsets(endBitPosition);

    return endBitPosition;
}

size_t WalkerObject::initializeOffsets(WalkerObject::ZserioPackingContext& context, size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    endBitPosition += context.getIdentifier().bitSizeOf<::zserio::StdIntArrayTraits<uint32_t>>(m_identifier_);
    if (getIdentifier() != 0)
    {
        endBitPosition = m_nested_.value().initializeOffsets(endBitPosition);
    }
    endBitPosition += ::zserio::bitSizeOfString(m_text_);
    endBitPosition = m_unionArray_.initializeOffsetsPacked(*this, endBitPosition);
    endBitPosition += 1;
    if (isOptionalUnionArraySet())
    {
        endBitPosition = m_optionalUnionArray_.value().initializeOffsetsPacked(*this, endBitPosition);
    }
    endBitPosition += context.getChoiceSelector().bitSizeOf<::zserio::StdIntArrayTraits<uint8_t>>(m_choiceSelector_);
    endBitPosition = m_choiceField_.initializeOffsets(context.getChoiceField(), endBitPosition);

    return endBitPosition;
}

bool WalkerObject::operator==(const WalkerObject& other) const
{
    if (this != &other)
    {
        return
                (m_identifier_ == other.m_identifier_) &&
                (!isNestedUsed() ? !other.isNestedUsed() : (m_nested_ == other.m_nested_)) &&
                (m_text_ == other.m_text_) &&
                (m_unionArray_ == other.m_unionArray_) &&
                (!isOptionalUnionArrayUsed() ? !other.isOptionalUnionArrayUsed() : (m_optionalUnionArray_ == other.m_optionalUnionArray_)) &&
                (m_choiceSelector_ == other.m_choiceSelector_) &&
                (m_choiceField_ == other.m_choiceField_);
    }

    return true;
}

bool WalkerObject::operator<(const WalkerObject& other) const
{
    if (m_identifier_ < other.m_identifier_)
        return true;
    if (other.m_identifier_ < m_identifier_)
        return false;

    if (isNestedUsed() && other.isNestedUsed())
    {
        if (m_nested_ < other.m_nested_)
            return true;
        if (other.m_nested_ < m_nested_)
            return false;
    }
    else if (isNestedUsed() != other.isNestedUsed())
    {
        return !isNestedUsed();
    }

    if (m_text_ < other.m_text_)
        return true;
    if (other.m_text_ < m_text_)
        return false;

    if (m_unionArray_ < other.m_unionArray_)
        return true;
    if (other.m_unionArray_ < m_unionArray_)
        return false;

    if (isOptionalUnionArrayUsed() && other.isOptionalUnionArrayUsed())
    {
        if (m_optionalUnionArray_ < other.m_optionalUnionArray_)
            return true;
        if (other.m_optionalUnionArray_ < m_optionalUnionArray_)
            return false;
    }
    else if (isOptionalUnionArrayUsed() != other.isOptionalUnionArrayUsed())
    {
        return !isOptionalUnionArrayUsed();
    }

    if (m_choiceSelector_ < other.m_choiceSelector_)
        return true;
    if (other.m_choiceSelector_ < m_choiceSelector_)
        return false;

    if (m_choiceField_ < other.m_choiceField_)
        return true;
    if (other.m_choiceField_ < m_choiceField_)
        return false;

    return false;
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
    result = ::zserio::calcHashCode(result, m_choiceSelector_);
    result = ::zserio::calcHashCode(result, m_choiceField_);

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

    m_unionArray_.write(*this, out);

    if (isOptionalUnionArraySet())
    {
        out.writeBool(true);
        m_optionalUnionArray_.value().write(*this, out);
    }
    else
    {
        out.writeBool(false);
    }

    out.writeBits(m_choiceSelector_, UINT8_C(8));

    // check parameters
    if (m_choiceField_.getSelector() != static_cast<uint8_t>(getChoiceSelector()))
    {
        throw ::zserio::CppRuntimeException("Write: Wrong parameter selector for field WalkerObject.choiceField: ") <<
                m_choiceField_.getSelector() << " != " << static_cast<uint8_t>(getChoiceSelector()) << "!";
    }
    m_choiceField_.write(out);
}

void WalkerObject::write(WalkerObject::ZserioPackingContext& context, ::zserio::BitStreamWriter& out) const
{
    context.getIdentifier().write<::zserio::StdIntArrayTraits<uint32_t>>(out, m_identifier_);

    if (getIdentifier() != 0)
    {
        m_nested_.value().write(out);
    }

    out.writeString(m_text_);

    m_unionArray_.writePacked(*this, out);

    if (isOptionalUnionArraySet())
    {
        out.writeBool(true);
        m_optionalUnionArray_.value().writePacked(*this, out);
    }
    else
    {
        out.writeBool(false);
    }

    context.getChoiceSelector().write<::zserio::StdIntArrayTraits<uint8_t>>(out, m_choiceSelector_);

    // check parameters
    if (m_choiceField_.getSelector() != static_cast<uint8_t>(getChoiceSelector()))
    {
        throw ::zserio::CppRuntimeException("Write: Wrong parameter selector for field WalkerObject.choiceField: ") <<
                m_choiceField_.getSelector() << " != " << static_cast<uint8_t>(getChoiceSelector()) << "!";
    }
    m_choiceField_.write(context.getChoiceField(), out);
}

void WalkerObject::ZserioElementFactory_unionArray::create(WalkerObject&        ,
        ::zserio::vector<::test_object::std_allocator::WalkerUnion>& array,
        ::zserio::BitStreamReader& in, size_t)
{
    array.emplace_back(in, array.get_allocator());
}

void WalkerObject::ZserioElementFactory_unionArray::create(WalkerObject&        ,
        ::zserio::vector<::test_object::std_allocator::WalkerUnion>& array,
        ::test_object::std_allocator::WalkerUnion::ZserioPackingContext& context, ::zserio::BitStreamReader& in,
        size_t)
{
    array.emplace_back(context, in, array.get_allocator());
}

void WalkerObject::ZserioElementFactory_optionalUnionArray::create(WalkerObject&        ,
        ::zserio::vector<::test_object::std_allocator::WalkerUnion>& array,
        ::zserio::BitStreamReader& in, size_t)
{
    array.emplace_back(in, array.get_allocator());
}

void WalkerObject::ZserioElementFactory_optionalUnionArray::create(WalkerObject&        ,
        ::zserio::vector<::test_object::std_allocator::WalkerUnion>& array,
        ::test_object::std_allocator::WalkerUnion::ZserioPackingContext& context, ::zserio::BitStreamReader& in,
        size_t)
{
    array.emplace_back(context, in, array.get_allocator());
}

uint32_t WalkerObject::readIdentifier(::zserio::BitStreamReader& in)
{
    return static_cast<uint32_t>(in.readBits(UINT8_C(32)));
}

uint32_t WalkerObject::readIdentifier(WalkerObject::ZserioPackingContext& context, ::zserio::BitStreamReader& in)
{
    return context.getIdentifier().read<::zserio::StdIntArrayTraits<uint32_t>>(in);
}
::zserio::InplaceOptionalHolder<::test_object::std_allocator::WalkerNested> WalkerObject::readNested(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    if (getIdentifier() != 0)
    {
        return ::zserio::InplaceOptionalHolder<::test_object::std_allocator::WalkerNested>(::test_object::std_allocator::WalkerNested(in, allocator));
    }

    return ::zserio::InplaceOptionalHolder<::test_object::std_allocator::WalkerNested>(::zserio::NullOpt);
}
::zserio::string<> WalkerObject::readText(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    return static_cast<::zserio::string<>>(in.readString(allocator));
}
WalkerObject::ZserioArrayType_unionArray WalkerObject::readUnionArray(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    ZserioArrayType_unionArray readField(allocator);
    readField.read(*this, in);

    return readField;
}

WalkerObject::ZserioArrayType_unionArray WalkerObject::readUnionArray(WalkerObject::ZserioPackingContext&, ::zserio::BitStreamReader& in, const allocator_type& allocator)
{
    ZserioArrayType_unionArray readField(allocator);
    readField.readPacked(*this, in);

    return readField;
}
::zserio::InplaceOptionalHolder<WalkerObject::ZserioArrayType_optionalUnionArray> WalkerObject::readOptionalUnionArray(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    if (in.readBool())
    {
        ZserioArrayType_optionalUnionArray readField(allocator);
        readField.read(*this, in);

        return ::zserio::InplaceOptionalHolder<ZserioArrayType_optionalUnionArray>(::std::move(readField));
    }

    return ::zserio::InplaceOptionalHolder<ZserioArrayType_optionalUnionArray>(::zserio::NullOpt);
}

::zserio::InplaceOptionalHolder<WalkerObject::ZserioArrayType_optionalUnionArray> WalkerObject::readOptionalUnionArray(WalkerObject::ZserioPackingContext&, ::zserio::BitStreamReader& in, const allocator_type& allocator)
{
    if (in.readBool())
    {
        ZserioArrayType_optionalUnionArray readField(allocator);
        readField.readPacked(*this, in);

        return ::zserio::InplaceOptionalHolder<ZserioArrayType_optionalUnionArray>(::std::move(readField));
    }

    return ::zserio::InplaceOptionalHolder<ZserioArrayType_optionalUnionArray>(::zserio::NullOpt);
}
uint8_t WalkerObject::readChoiceSelector(::zserio::BitStreamReader& in)
{
    return static_cast<uint8_t>(in.readBits(UINT8_C(8)));
}

uint8_t WalkerObject::readChoiceSelector(WalkerObject::ZserioPackingContext& context, ::zserio::BitStreamReader& in)
{
    return context.getChoiceSelector().read<::zserio::StdIntArrayTraits<uint8_t>>(in);
}
::test_object::std_allocator::WalkerChoice WalkerObject::readChoiceField(::zserio::BitStreamReader& in,
        const allocator_type& allocator)
{
    return ::test_object::std_allocator::WalkerChoice(in, static_cast<uint8_t>(getChoiceSelector()), allocator);
}

::test_object::std_allocator::WalkerChoice WalkerObject::readChoiceField(WalkerObject::ZserioPackingContext& context, ::zserio::BitStreamReader& in, const allocator_type& allocator)
{
    return ::test_object::std_allocator::WalkerChoice(context.getChoiceField(), in, static_cast<uint8_t>(getChoiceSelector()), allocator);
}

} // namespace std_allocator
} // namespace test_object
