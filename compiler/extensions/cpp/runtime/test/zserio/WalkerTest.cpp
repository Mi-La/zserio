#include "gtest/gtest.h"

#include "zserio/Walker.h"
#include "zserio/Traits.h"
#include "zserio/TypeInfo.h"
#include "zserio/Reflectable.h"
#include "zserio/Array.h"
#include "zserio/ArrayTraits.h"
#include "zserio/PackingContext.h"
#include "zserio/BitStreamWriter.h"

using namespace zserio::literals;

namespace zserio
{

namespace
{

class DummyNested
{
public:
    using allocator_type = ::std::allocator<uint8_t>;

    explicit DummyNested(const allocator_type& allocator = allocator_type()) :
            m_text_(allocator)
    {}

    template <typename ZSERIO_T_text,
            is_field_constructor_enabled_t<ZSERIO_T_text, DummyNested, allocator_type> = 0>
    explicit DummyNested(
            ZSERIO_T_text&& text_,
            const allocator_type& allocator = allocator_type()) :
            DummyNested(allocator)
    {
        m_text_ = ::std::forward<ZSERIO_T_text>(text_);
    }

    static void createPackingContext(PackingContextNode&)
    {}

    static const ITypeInfo& typeInfo()
    {
        static const StringView templateName;
        static const Span<TemplateArgumentInfo> templateArguments;

        static const ::std::array<FieldInfo, 1> fields = {
            FieldInfo{
                makeStringView("text"), // schemaName
                BuiltinTypeInfo::getString(), // typeInfo
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
            }
        };

        static const Span<ParameterInfo> parameters;

        static const Span<FunctionInfo> functions;

        static const StructTypeInfo typeInfo = {
            makeStringView("DummyNested"), templateName, templateArguments,
            fields, parameters, functions
        };

        return typeInfo;
    }

    IReflectablePtr reflectable(const allocator_type& allocator = allocator_type())
    {
        class Reflectable : public ReflectableAllocatorHolderBase<allocator_type>
        {
        public:
            explicit Reflectable(DummyNested& object, const allocator_type& allocator) :
                    ReflectableAllocatorHolderBase<allocator_type>(DummyNested::typeInfo(), allocator),
                    m_object(object)
            {}

            virtual IReflectablePtr getField(StringView name) const override
            {
                if (name == makeStringView("text"))
                {
                    return ReflectableFactory::getString(m_object.getText(), get_allocator());
                }
                else
                {
                    throw CppRuntimeException("Field '") + name + "' doesn't exist in 'DummyNested'!";
                }
            }

            virtual void setField(StringView, const AnyHolder<allocator_type>&) override
            {
            }

            virtual void write(BitStreamWriter&) override
            {
            }

            virtual size_t bitSizeOf(size_t) const override
            {
                return 0;
            }

        private:
            DummyNested& m_object;
        };

        return std::allocate_shared<Reflectable>(allocator, *this, allocator);
    }

    const string<>& getText() const
    {
        return m_text_;
    }

    void setText(const string<>& text_)
    {
        m_text_ = text_;
    }

private:
    string<> m_text_;
};

class DummyUnion
{
private:
    class ZserioElementFactory_nestedArray
    {
    public:
        explicit ZserioElementFactory_nestedArray(DummyUnion& owner) :
                m_owner(owner)
        {}

        void create(::std::vector<DummyNested>&, BitStreamReader&, size_t) const
        {}

        void create(PackingContextNode&, ::std::vector<DummyNested>&,
                BitStreamReader&, size_t) const
        {}

    private:
        DummyUnion& m_owner;
    };

    using ZserioArrayType_nestedArray = Array<::std::vector<DummyNested>,
            ObjectArrayTraits<DummyNested, ZserioElementFactory_nestedArray>,
            ArrayType::AUTO>;

public:
    using allocator_type = ::std::allocator<uint8_t>;

    enum ChoiceTag : int32_t
    {
        CHOICE_value = 0,
        CHOICE_text = 1,
        CHOICE_nestedArray = 2,
        UNDEFINED_CHOICE = -1
    };

    explicit DummyUnion(const allocator_type& allocator = allocator_type()) noexcept :
            m_choiceTag(UNDEFINED_CHOICE),
            m_objectChoice(allocator)
    {
    }

    static const ITypeInfo& typeInfo()
    {
        static const StringView templateName;
        static const Span<TemplateArgumentInfo> templateArguments;

        static const ::std::array<FieldInfo, 3> fields = {
            FieldInfo{
                makeStringView("value"), // schemaName
                BuiltinTypeInfo::getUInt32(), // typeInfo
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
            FieldInfo{
                makeStringView("text"), // schemaName
                BuiltinTypeInfo::getString(), // typeInfo
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
            FieldInfo{
                makeStringView("nestedArray"), // schemaName
                DummyNested::typeInfo(), // typeInfo
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
            }
        };

        static const Span<ParameterInfo> parameters;

        static const Span<FunctionInfo> functions;

        static const UnionTypeInfo typeInfo = {
            makeStringView("DummyUnion"), templateName, templateArguments,
            fields, parameters, functions
        };

        return typeInfo;
    }

    IReflectablePtr reflectable(const allocator_type& allocator = allocator_type())
    {
        class Reflectable : public ReflectableAllocatorHolderBase<allocator_type>
        {
        public:
            explicit Reflectable(DummyUnion& object, const allocator_type& allocator) :
                    ReflectableAllocatorHolderBase<allocator_type>(DummyUnion::typeInfo(), allocator),
                    m_object(object)
            {}

            virtual IReflectablePtr getField(StringView name) const override
            {
                if (name == makeStringView("value"))
                {
                    return ReflectableFactory::getUInt32(m_object.getValue(), get_allocator());
                }
                if (name == makeStringView("text"))
                {
                    return ReflectableFactory::getString(m_object.getText(), get_allocator());
                }
                if (name == makeStringView("nestedArray"))
                {
                    return ReflectableFactory::getCompoundArray(m_object.getNestedArray(), get_allocator());
                }
                else
                {
                    throw CppRuntimeException("Field '") + name + "' doesn't exist in 'DummyUnion'!";
                }
            }

            virtual void setField(StringView, const AnyHolder<allocator_type>&) override
            {
            }

            virtual StringView getChoice() const override
            {
                switch (m_object.choiceTag())
                {
                case CHOICE_value:
                    return makeStringView("value");
                case CHOICE_text:
                    return makeStringView("text");
                case CHOICE_nestedArray:
                    return makeStringView("nestedArray");
                default:
                    return {};
                }
            }

            virtual void write(BitStreamWriter&) override
            {
            }

            virtual size_t bitSizeOf(size_t) const override
            {
                return 0;
            }

        private:
            DummyUnion& m_object;
        };

        return std::allocate_shared<Reflectable>(allocator, *this, allocator);
    }

    ChoiceTag choiceTag() const
    {
        return m_choiceTag;
    }

    uint32_t getValue() const
    {
        return m_objectChoice.get<uint32_t>();
    }

    void setValue(uint32_t value_)
    {
        m_choiceTag = CHOICE_value;
        m_objectChoice = value_;
    }

    const string<>& getText() const
    {
        return m_objectChoice.get<string<>>();
    }

    void setText(const string<>& text_)
    {
        m_choiceTag = CHOICE_text;
        m_objectChoice = text_;
    }

    const ::std::vector<DummyNested>& getNestedArray() const
    {
        return m_objectChoice.get<ZserioArrayType_nestedArray>().getRawArray();
    }

    ::std::vector<DummyNested>& getNestedArray()
    {
        return m_objectChoice.get<ZserioArrayType_nestedArray>().getRawArray();
    }

    void setNestedArray(const ::std::vector<DummyNested>& nestedArray_)
    {
        m_choiceTag = CHOICE_nestedArray;
        m_objectChoice = ZserioArrayType_nestedArray(nestedArray_,
                ObjectArrayTraits<DummyNested, ZserioElementFactory_nestedArray>());
    }

private:
    ChoiceTag m_choiceTag;
    AnyHolder<> m_objectChoice;
};

class DummyObject
{
private:
    class ZserioElementFactory_unionArray
    {
    public:
        explicit ZserioElementFactory_unionArray(DummyObject& owner) :
            m_owner(owner)
        {}

        void create(::std::vector<DummyUnion>&, BitStreamReader&, size_t) const
        {}

        void create(PackingContextNode&, ::std::vector<DummyUnion>&,
                BitStreamReader&, size_t) const
        {}

    private:
        DummyObject& m_owner;
    };

    using ZserioArrayType_unionArray = Array<::std::vector<DummyUnion>,
            ObjectArrayTraits<DummyUnion, ZserioElementFactory_unionArray>,
            ArrayType::AUTO>;

public:
    using allocator_type = ::std::allocator<uint8_t>;

    DummyObject(const allocator_type& allocator = allocator_type()) :
            m_identifier_(uint32_t()),
            m_nested_(allocator),
            m_text_(allocator),
            m_unionArray_(ObjectArrayTraits<DummyUnion, ZserioElementFactory_unionArray>(), allocator)
    {}

    template <typename ZSERIO_T_nested,
            typename ZSERIO_T_text,
            typename ZSERIO_T_unionArray>
    DummyObject(
            uint32_t identifier_,
            ZSERIO_T_nested&& nested_,
            ZSERIO_T_text&& text_,
            ZSERIO_T_unionArray&& unionArray_,
            const allocator_type& allocator = allocator_type()) :
            DummyObject(allocator)
    {
        m_identifier_ = identifier_;
        m_nested_ = ::std::forward<ZSERIO_T_nested>(nested_);
        m_text_ = ::std::forward<ZSERIO_T_text>(text_);
        m_unionArray_ = ZserioArrayType_unionArray(::std::forward<ZSERIO_T_unionArray>(unionArray_),
                ObjectArrayTraits<DummyUnion, ZserioElementFactory_unionArray>());
    }

    static const ITypeInfo& typeInfo()
    {
        static const StringView templateName;
        static const Span<TemplateArgumentInfo> templateArguments;

        static const ::std::array<FieldInfo, 4> fields = {
            FieldInfo{
                makeStringView("identifier"), // schemaName
                BuiltinTypeInfo::getUInt32(), // typeInfo
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
            FieldInfo{
                makeStringView("nested"), // schemaName
                DummyNested::typeInfo(), // typeInfo
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
            FieldInfo{
                makeStringView("text"), // schemaName
                BuiltinTypeInfo::getString(), // typeInfo
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
            FieldInfo{
                makeStringView("unionArray"), // schemaName
                DummyUnion::typeInfo(), // typeInfo
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
            }
        };

        static const Span<ParameterInfo> parameters;

        static const Span<FunctionInfo> functions;

        static const StructTypeInfo typeInfo = {
            makeStringView("DummyObject"), templateName, templateArguments,
            fields, parameters, functions
        };

        return typeInfo;
    }

    IReflectablePtr reflectable(const allocator_type& allocator = allocator_type())
    {
        class Reflectable : public ReflectableAllocatorHolderBase<allocator_type>
        {
        public:
            explicit Reflectable(DummyObject& object, const allocator_type& allocator) :
                    ReflectableAllocatorHolderBase<allocator_type>(DummyObject::typeInfo(), allocator),
                    m_object(object)
            {}

            virtual IReflectablePtr getField(StringView name) const override
            {
                if (name == makeStringView("identifier"))
                {
                    return ReflectableFactory::getUInt32(m_object.getIdentifier(), get_allocator());
                }
                if (name == makeStringView("nested"))
                {
                    return m_object.getNested().reflectable(get_allocator());
                }
                if (name == makeStringView("text"))
                {
                    return ReflectableFactory::getString(m_object.getText(), get_allocator());
                }
                if (name == makeStringView("unionArray"))
                {
                    return ReflectableFactory::getCompoundArray(m_object.getUnionArray(), get_allocator());
                }
                else
                {
                    throw CppRuntimeException("Field '") + name + "' doesn't exist in 'DummyObject'!";
                }
            }

            virtual void setField(StringView, const AnyHolder<allocator_type>&) override
            {
            }

            virtual void write(BitStreamWriter&) override
            {
            }

            virtual size_t bitSizeOf(size_t) const override
            {
                return 0;
            }

        private:
            DummyObject& m_object;
        };

        return std::allocate_shared<Reflectable>(allocator, *this, allocator);
    }

    uint32_t getIdentifier() const
    {
        return m_identifier_;
    }

    void setIdentifier(uint32_t identifier_)
    {
        m_identifier_ = identifier_;
    }

    const DummyNested& getNested() const
    {
        return m_nested_;
    }

    DummyNested& getNested()
    {
        return m_nested_;
    }

    const string<>& getText() const
    {
        return m_text_;
    }

    void setText(string<>&& text_)
    {
        m_text_ = std::move(text_);
    }

    const ::std::vector<DummyUnion>& getUnionArray() const
    {
        return m_unionArray_.getRawArray();
    }

    ::std::vector<DummyUnion>& getUnionArray()
    {
        return m_unionArray_.getRawArray();
    }

    void setUnionArray(::std::vector<DummyUnion>&& unionArray_)
    {
        m_unionArray_ = ZserioArrayType_unionArray(std::move(unionArray_),
                ObjectArrayTraits<DummyUnion, ZserioElementFactory_unionArray>());
    }

private:
    uint32_t m_identifier_;
    DummyNested m_nested_;
    string<> m_text_;
    ZserioArrayType_unionArray m_unionArray_;
};

DummyObject createDummyObject()
{
    std::vector<DummyUnion> unionArray;
    unionArray.resize(3);
    unionArray[0].setText("1");
    unionArray[1].setValue(2);
    unionArray[2].setNestedArray(std::vector<DummyNested>{{DummyNested{"nestedArray"}}});
    return DummyObject(13, DummyNested("nested"), "test", std::move(unionArray));
}

class TestObserver : public IWalkObserver
{
public:
    typedef std::map<StringView, std::vector<IReflectablePtr>> CapturesMap;

    TestObserver()
    {
        // initialize empty captures
        m_captures["beginRoot"_sv];
        m_captures["endRoot"_sv];
        m_captures["beginArray"_sv];
        m_captures["endArray"_sv];
        m_captures["beginCompound"_sv];
        m_captures["endCompound"_sv];
        m_captures["visitValue"_sv];
    }

    virtual void beginRoot(const IReflectablePtr& compound) override
    {
        m_captures["beginRoot"_sv].push_back(compound);
    }

    virtual void endRoot(const IReflectablePtr& compound) override
    {
        m_captures["endRoot"_sv].push_back(compound);
    }

    virtual void beginArray(const IReflectablePtr& array, const FieldInfo&) override
    {
        m_captures["beginArray"_sv].push_back(array);
    }

    virtual void endArray(const IReflectablePtr& array, const FieldInfo&) override
    {
        m_captures["endArray"_sv].push_back(array);
    }

    virtual void beginCompound(const IReflectablePtr& compound, const FieldInfo&, size_t) override
    {
        m_captures["beginCompound"_sv].push_back(compound);
    }

    virtual void endCompound(const IReflectablePtr& compound, const FieldInfo&, size_t) override
    {
        m_captures["endCompound"_sv].push_back(compound);
    }

    virtual void visitValue(const IReflectablePtr& value, const FieldInfo&, size_t) override
    {
        m_captures["visitValue"_sv].push_back(value);
    }

    const std::vector<IReflectablePtr>& getCaptures(StringView captureName) const
    {
        return m_captures.find(captureName)->second;
    }

private:
    CapturesMap m_captures;
};

class TestFilter : public IWalkFilter
{
public:
    TestFilter& beforeArray(bool beforeArray) { m_beforeArray = beforeArray; return *this; }
    TestFilter& afterArray(bool afterArray) { m_afterArray = afterArray; return *this; }
    TestFilter& onlyFirstElement(bool onlyFirstElement) { m_onlyFirstElement = onlyFirstElement; return *this; }
    TestFilter& beforeCompound(bool beforeCompound) { m_beforeCompound = beforeCompound; return *this; }
    TestFilter& afterCompound(bool afterCompound) { m_afterCompound = afterCompound; return *this; }
    TestFilter& beforeValue(bool beforeValue) { m_beforeValue = beforeValue; return *this; }
    TestFilter& afterValue(bool afterValue) { m_afterValue = afterValue; return *this; }

    virtual bool beforeArray(const IReflectablePtr&, const FieldInfo&) override
    {
        m_isFirstElement = true;
        return m_beforeArray;
    }

    virtual bool afterArray(const IReflectablePtr&, const FieldInfo&) override
    {
        m_isFirstElement = false;
        return m_afterArray;
    }

    virtual bool beforeCompound(const IReflectablePtr&, const FieldInfo&, size_t) override
    {
        return m_beforeCompound;
    }

    virtual bool afterCompound(const IReflectablePtr&, const FieldInfo&, size_t) override
    {
        bool goToNext = !(m_onlyFirstElement && m_isFirstElement);
        m_isFirstElement = false;
        return goToNext && m_afterCompound;
    }

    virtual bool beforeValue(const IReflectablePtr&, const FieldInfo&, size_t) override
    {
        return m_beforeValue;
    }

    virtual bool afterValue(const IReflectablePtr&, const FieldInfo&, size_t) override
    {
        return m_afterValue;
    }

private:
    bool m_beforeArray = true;
    bool m_afterArray = true;
    bool m_onlyFirstElement = false;
    bool m_beforeCompound = true;
    bool m_afterCompound = true;
    bool m_beforeValue = true;
    bool m_afterValue = true;
    bool m_isFirstElement = false;
};

} // namespace

TEST(WalkerTest, walk)
{
    TestObserver observer;
    DefaultWalkFilter noFilter;
    Walker walker(observer, noFilter);
    DummyObject dummyObject = createDummyObject();
    walker.walk(dummyObject.reflectable());

    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("beginRoot"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("endRoot"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_EQ(2, observer.getCaptures("beginArray"_sv).size());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("beginArray"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("beginArray"_sv).at(1)->getTypeInfo().getSchemaName());

    ASSERT_EQ(2, observer.getCaptures("endArray"_sv).size());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("endArray"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("endArray"_sv).at(1)->getTypeInfo().getSchemaName());

    ASSERT_EQ(5, observer.getCaptures("beginCompound"_sv).size());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("beginCompound"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("beginCompound"_sv).at(1)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("beginCompound"_sv).at(2)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("beginCompound"_sv).at(3)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("beginCompound"_sv).at(4)->getTypeInfo().getSchemaName());

    ASSERT_EQ(5, observer.getCaptures("endCompound"_sv).size());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("endCompound"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("endCompound"_sv).at(1)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("endCompound"_sv).at(2)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("endCompound"_sv).at(3)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("endCompound"_sv).at(4)->getTypeInfo().getSchemaName());

    ASSERT_EQ(6, observer.getCaptures("visitValue"_sv).size());
    ASSERT_EQ(13, observer.getCaptures("visitValue"_sv).at(0)->toUInt());
    ASSERT_EQ("nested", observer.getCaptures("visitValue"_sv).at(1)->toString());
    ASSERT_EQ("test", observer.getCaptures("visitValue"_sv).at(2)->toString());
    ASSERT_EQ("1", observer.getCaptures("visitValue"_sv).at(3)->toString());
    ASSERT_EQ(2, observer.getCaptures("visitValue"_sv).at(4)->toUInt());
    ASSERT_EQ("nestedArray", observer.getCaptures("visitValue"_sv).at(5)->toString());
}

TEST(WalkerTest, walkSkipCompund)
{
    TestObserver observer;
    TestFilter testFilter;
    testFilter.beforeCompound(false);
    Walker walker(observer, testFilter);
    DummyObject dummyObject = createDummyObject();
    walker.walk(dummyObject.reflectable());

    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("beginRoot"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("endRoot"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_EQ(1, observer.getCaptures("beginArray"_sv).size());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("beginArray"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_EQ(1, observer.getCaptures("endArray"_sv).size());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("endArray"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_TRUE(observer.getCaptures("beginCompound"_sv).empty());
    ASSERT_TRUE(observer.getCaptures("endCompound"_sv).empty());

    ASSERT_EQ(2, observer.getCaptures("visitValue"_sv).size());
    ASSERT_EQ(13, observer.getCaptures("visitValue"_sv).at(0)->toUInt());
    ASSERT_EQ("test", observer.getCaptures("visitValue"_sv).at(1)->toString());
}

TEST(WalkerTest, walkSkipSiblings)
{
    TestObserver observer;
    TestFilter testFilter;
    testFilter.afterValue(false);
    Walker walker(observer, testFilter);
    DummyObject dummyObject = createDummyObject();
    walker.walk(dummyObject.reflectable());

    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("beginRoot"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("endRoot"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_TRUE(observer.getCaptures("beginArray"_sv).empty());
    ASSERT_TRUE(observer.getCaptures("endArray"_sv).empty());

    ASSERT_TRUE(observer.getCaptures("beginCompound"_sv).empty());
    ASSERT_TRUE(observer.getCaptures("endCompound"_sv).empty());

    ASSERT_EQ(1, observer.getCaptures("visitValue"_sv).size());
    ASSERT_EQ(13, observer.getCaptures("visitValue"_sv).at(0)->toUInt());
}

TEST(WalkerTest, walkSkipAfterNested)
{
    TestObserver observer;
    TestFilter testFilter;
    testFilter.afterCompound(false);
    Walker walker(observer, testFilter);
    DummyObject dummyObject = createDummyObject();
    walker.walk(dummyObject.reflectable());

    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("beginRoot"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("endRoot"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_TRUE(observer.getCaptures("beginArray"_sv).empty());
    ASSERT_TRUE(observer.getCaptures("endArray"_sv).empty());

    ASSERT_EQ(1, observer.getCaptures("beginCompound"_sv).size());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("beginCompound"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_EQ(1, observer.getCaptures("endCompound"_sv).size());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("endCompound"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_EQ(2, observer.getCaptures("visitValue"_sv).size());
    ASSERT_EQ(13, observer.getCaptures("visitValue"_sv).at(0)->toUInt());
    ASSERT_EQ("nested", observer.getCaptures("visitValue"_sv).at(1)->toString());
}

TEST(WalkerTest, walkOnlyFirstElement)
{
    TestObserver observer;
    TestFilter testFilter;
    testFilter.onlyFirstElement(true);
    Walker walker(observer, testFilter);
    DummyObject dummyObject = createDummyObject();
    walker.walk(dummyObject.reflectable());

    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("beginRoot"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyObject"_sv, observer.getCaptures("endRoot"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_EQ(1, observer.getCaptures("beginArray"_sv).size());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("beginArray"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_EQ(1, observer.getCaptures("endArray"_sv).size());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("endArray"_sv).at(0)->getTypeInfo().getSchemaName());

    ASSERT_EQ(2, observer.getCaptures("beginCompound"_sv).size());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("beginCompound"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("beginCompound"_sv).at(1)->getTypeInfo().getSchemaName());

    ASSERT_EQ(2, observer.getCaptures("endCompound"_sv).size());
    ASSERT_EQ("DummyNested"_sv, observer.getCaptures("endCompound"_sv).at(0)->getTypeInfo().getSchemaName());
    ASSERT_EQ("DummyUnion"_sv, observer.getCaptures("endCompound"_sv).at(1)->getTypeInfo().getSchemaName());

    ASSERT_EQ(4, observer.getCaptures("visitValue"_sv).size());
    ASSERT_EQ(13, observer.getCaptures("visitValue"_sv).at(0)->toUInt());
    ASSERT_EQ("nested", observer.getCaptures("visitValue"_sv).at(1)->toString());
    ASSERT_EQ("test", observer.getCaptures("visitValue"_sv).at(2)->toString());
    ASSERT_EQ("1", observer.getCaptures("visitValue"_sv).at(3)->toString());
}

TEST(DefaultWalkObserverTest, allMethods)
{
    DefaultWalkObserver defaultObserver;
    IWalkObserver& walkObserver = defaultObserver;
    IReflectablePtr dummyReflectable = nullptr;
    const FieldInfo& dummyFieldInfo = DummyObject::typeInfo().getFields()[0];

    ASSERT_NO_THROW(walkObserver.beginRoot(dummyReflectable));
    ASSERT_NO_THROW(walkObserver.endRoot(dummyReflectable));
    ASSERT_NO_THROW(walkObserver.beginArray(dummyReflectable, dummyFieldInfo));
    ASSERT_NO_THROW(walkObserver.endArray(dummyReflectable, dummyFieldInfo));
    ASSERT_NO_THROW(walkObserver.beginCompound(dummyReflectable, dummyFieldInfo));
    ASSERT_NO_THROW(walkObserver.endCompound(dummyReflectable, dummyFieldInfo));
    ASSERT_NO_THROW(walkObserver.visitValue(dummyReflectable, dummyFieldInfo));
}

TEST(DefaultWalkFilterTest, allMethods)
{
    DefaultWalkFilter defaultFilter;
    IWalkFilter& walkFilter = defaultFilter;
    IReflectablePtr dummyReflectable = nullptr;
    const FieldInfo& dummyFieldInfo = DummyObject::typeInfo().getFields()[0];

    ASSERT_TRUE(walkFilter.beforeArray(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.afterArray(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.beforeCompound(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.afterCompound(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo));
}

TEST(DepthFilterTest, depth0)
{
    DepthWalkFilter depthWalkFilter(0);
    IWalkFilter& walkFilter = depthWalkFilter;
    IReflectablePtr dummyReflectable = nullptr;
    const FieldInfo& dummyFieldInfo = DummyObject::typeInfo().getFields()[0];

    ASSERT_FALSE(walkFilter.beforeArray(dummyReflectable, dummyFieldInfo)); // 0
    ASSERT_TRUE(walkFilter.afterArray(dummyReflectable, dummyFieldInfo)); // 0

    ASSERT_FALSE(walkFilter.beforeCompound(dummyReflectable, dummyFieldInfo)); // 0
    ASSERT_TRUE(walkFilter.afterCompound(dummyReflectable, dummyFieldInfo)); // 0

    ASSERT_FALSE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo)); // 0
    ASSERT_TRUE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo)); // 0
}

TEST(DepthFilterTest, depth1)
{
    DepthWalkFilter depthWalkFilter(1);
    IWalkFilter& walkFilter = depthWalkFilter;
    IReflectablePtr dummyReflectable = nullptr;
    const FieldInfo& dummyFieldInfo = DummyObject::typeInfo().getFields()[0];

    ASSERT_TRUE(walkFilter.beforeArray(dummyReflectable, dummyFieldInfo)); // 0
    ASSERT_FALSE(walkFilter.beforeArray(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_TRUE(walkFilter.afterArray(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_FALSE(walkFilter.beforeCompound(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_TRUE(walkFilter.afterCompound(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_FALSE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_TRUE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_TRUE(walkFilter.afterArray(dummyReflectable, dummyFieldInfo)); // 0

    ASSERT_TRUE(walkFilter.beforeCompound(dummyReflectable, dummyFieldInfo)); // 0
    ASSERT_FALSE(walkFilter.beforeArray(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_TRUE(walkFilter.afterArray(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_FALSE(walkFilter.beforeCompound(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_TRUE(walkFilter.afterCompound(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_FALSE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_TRUE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo)); // 1
    ASSERT_TRUE(walkFilter.afterCompound(dummyReflectable, dummyFieldInfo)); // 0

    ASSERT_TRUE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo)); // 0
    ASSERT_TRUE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo)); // 0
}

TEST(RegexWalkFilterTest, regexAll)
{
    RegexWalkFilter regexWalkFilter(".*");
    IWalkFilter& walkFilter = regexWalkFilter;
    IReflectablePtr dummyReflectable = nullptr;
    const FieldInfo& dummyFieldInfo = DummyObject::typeInfo().getFields()[0];
    const FieldInfo& dummyArrayFieldInfo = DummyObject::typeInfo().getFields()[3];

    ASSERT_TRUE(walkFilter.beforeArray(dummyReflectable, dummyArrayFieldInfo));
    ASSERT_TRUE(walkFilter.afterArray(dummyReflectable, dummyArrayFieldInfo));
    ASSERT_TRUE(walkFilter.beforeCompound(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.afterCompound(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo));
}

TEST(RegexWalkFilterTest, regexPrefix)
{
    RegexWalkFilter regexWalkFilter("nested\\..*");
    IWalkFilter& walkFilter = regexWalkFilter;
    DummyObject dummyObject = createDummyObject();
    IReflectablePtr dummyReflectable = dummyObject.reflectable();

    const FieldInfo& identifierFieldInfo = dummyObject.typeInfo().getFields()[0];
    IReflectablePtr identifierReflectable = dummyReflectable->getField("identifier");
    ASSERT_FALSE(walkFilter.beforeValue(identifierReflectable, identifierFieldInfo));
    ASSERT_TRUE(walkFilter.afterValue(identifierReflectable, identifierFieldInfo));

    const FieldInfo& nestedFieldInfo = dummyObject.typeInfo().getFields()[1];
    IReflectablePtr nestedReflectable = dummyReflectable->getField("nested");
    ASSERT_TRUE(walkFilter.beforeCompound(nestedReflectable, nestedFieldInfo));
    const FieldInfo& textFieldInfo = nestedFieldInfo.typeInfo.getFields()[0];
    IReflectablePtr textReflectable = nestedReflectable->getField("text");
    ASSERT_TRUE(walkFilter.beforeValue(textReflectable, textFieldInfo));
    ASSERT_TRUE(walkFilter.afterValue(textReflectable, textFieldInfo));
    ASSERT_TRUE(walkFilter.afterCompound(nestedReflectable, nestedFieldInfo));

    // ignore text

    const FieldInfo& unionArrayFieldInfo = dummyObject.typeInfo().getFields()[3];
    IReflectablePtr unionArrayReflectable = dummyReflectable->getField("unionArray");
    ASSERT_FALSE(walkFilter.beforeArray(unionArrayReflectable, unionArrayFieldInfo));
    ASSERT_TRUE(walkFilter.afterArray(unionArrayReflectable, unionArrayFieldInfo));
}

TEST(RegexWalkFilterTest, regexArray)
{
    RegexWalkFilter regexWalkFilter("unionArray\\[\\d+\\]\\.nes.*");
    IWalkFilter& walkFilter = regexWalkFilter;
    DummyObject dummyObject = createDummyObject();
    IReflectablePtr dummyReflectable = dummyObject.reflectable();

    const FieldInfo& unionArrayFieldInfo = dummyObject.typeInfo().getFields()[3];
    IReflectablePtr unionArrayReflectable = dummyReflectable->getField("unionArray");
    ASSERT_TRUE(walkFilter.beforeArray(unionArrayReflectable, unionArrayFieldInfo));

    ASSERT_FALSE(walkFilter.beforeCompound(unionArrayReflectable->at(0), unionArrayFieldInfo, 0));
    ASSERT_TRUE(walkFilter.afterCompound(unionArrayReflectable->at(0), unionArrayFieldInfo, 0));

    ASSERT_FALSE(walkFilter.beforeCompound(unionArrayReflectable->at(1), unionArrayFieldInfo, 1));
    ASSERT_TRUE(walkFilter.afterCompound(unionArrayReflectable->at(1), unionArrayFieldInfo, 1));

    ASSERT_TRUE(walkFilter.beforeCompound(unionArrayReflectable->at(2), unionArrayFieldInfo, 2));
    ASSERT_TRUE(walkFilter.afterCompound(unionArrayReflectable->at(2), unionArrayFieldInfo, 2));

    ASSERT_TRUE(walkFilter.afterArray(unionArrayReflectable, unionArrayFieldInfo));
}

TEST(RegexWalkFilterTest, regexArrayNoMatch)
{
    RegexWalkFilter regexWalkFilter("^unionArray\\[\\d*\\]\\.te.*");
    IWalkFilter& walkFilter = regexWalkFilter;

    std::vector<DummyUnion> unionArray;
    unionArray.resize(1);
    unionArray[0].setNestedArray(std::vector<DummyNested>{{DummyNested{"nestedArray"}}});
    DummyObject dummyObject (13, DummyNested("nested"), "test", std::move(unionArray));
    IReflectablePtr dummyReflectable = dummyObject.reflectable();

    const FieldInfo& unionArrayFieldInfo = dummyObject.typeInfo().getFields()[3];
    IReflectablePtr unionArrayReflectable = dummyReflectable->getField("unionArray");
    ASSERT_FALSE(walkFilter.beforeArray(unionArrayReflectable, unionArrayFieldInfo));
    ASSERT_TRUE(walkFilter.afterArray(unionArrayReflectable, unionArrayFieldInfo));
}

TEST(RegexWalkFilterTest, regexUnsetCompoundMatch)
{
    RegexWalkFilter regexWalkFilter("nested");
    IWalkFilter& walkFilter = regexWalkFilter;

    std::vector<DummyUnion> unionArray;
    unionArray.resize(2);
    unionArray[0].setText("1");
    unionArray[1].setValue(2);
    DummyObject dummyObject;
    dummyObject.setIdentifier(13);
    dummyObject.setText("test");
    dummyObject.setUnionArray(std::move(unionArray));
    IReflectablePtr dummyReflectable = dummyObject.reflectable();

    const FieldInfo& nestedFieldInfo = dummyObject.typeInfo().getFields()[1];
    IReflectablePtr nestedReflectable = dummyReflectable->getField("nested");
    ASSERT_TRUE(walkFilter.beforeCompound(nestedReflectable, nestedFieldInfo));
    ASSERT_TRUE(walkFilter.afterCompound(nestedReflectable, nestedFieldInfo));
}

// TODO[Mi-L@]: how to test real null compounds and null arrays? E.g. optionals?

TEST(ArrayLengthWalkFilterTest, length0)
{
    ArrayLengthWalkFilter arrayLengthWalkFilter(0);
    IWalkFilter& walkFilter = arrayLengthWalkFilter;
    IReflectablePtr dummyReflectable = nullptr;
    const FieldInfo& dummyFieldInfo = DummyObject::typeInfo().getFields()[0];
    const FieldInfo& dummyArrayFieldInfo = DummyObject::typeInfo().getFields()[3];

    ASSERT_TRUE(walkFilter.beforeArray(dummyReflectable, dummyArrayFieldInfo));
    ASSERT_FALSE(walkFilter.beforeCompound(dummyReflectable, dummyFieldInfo, 0));
    ASSERT_FALSE(walkFilter.afterCompound(dummyReflectable, dummyFieldInfo, 0));
    ASSERT_FALSE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo, 1));
    ASSERT_FALSE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo, 1));
    ASSERT_TRUE(walkFilter.afterArray(dummyReflectable, dummyArrayFieldInfo));

    ASSERT_TRUE(walkFilter.beforeCompound(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo));
    ASSERT_TRUE(walkFilter.beforeArray(dummyReflectable, dummyArrayFieldInfo));
    ASSERT_FALSE(walkFilter.beforeValue(dummyReflectable, dummyFieldInfo, 0));
    ASSERT_FALSE(walkFilter.afterValue(dummyReflectable, dummyFieldInfo, 0));
    ASSERT_TRUE(walkFilter.afterArray(dummyReflectable, dummyArrayFieldInfo));
    ASSERT_TRUE(walkFilter.afterCompound(dummyReflectable, dummyFieldInfo));
}

} // namespace zserio