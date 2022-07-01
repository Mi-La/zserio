#include "gtest/gtest.h"

#include <sstream>

#include "zserio/DebugStringUtil.h"
#include "zserio/Reflectable.h"
#include "zserio/pmr/PolymorphicAllocator.h"

namespace zserio
{

namespace
{

template <typename ALLOC = std::allocator<uint8_t>>
struct DummyObject
{
    using allocator_type = ALLOC;

    explicit DummyObject(const ALLOC& allocator = ALLOC()) :
            m_text_("test", allocator)
    {}

    explicit DummyObject(const string<ALLOC>& text_, const ALLOC& = ALLOC()) :
            m_text_(text_)
    {}

    static const IBasicTypeInfo<ALLOC>& typeInfo()
    {
        static const std::array<BasicFieldInfo<ALLOC>, 1> fields{BasicFieldInfo<ALLOC>{
            "text"_sv, BuiltinTypeInfo<ALLOC>::getString(),
            {}, {}, {}, {}, false, {}, {}, false, {}, false, false
        }};

        static const StructTypeInfo<ALLOC> typeInfo{
            "Dummy"_sv,
            [](const ALLOC& allocator) -> IBasicReflectablePtr<ALLOC> {
                return std::allocate_shared<ReflectableOwner<DummyObject>>(allocator, allocator);
            },
            {}, {}, fields, {}, {}
        };

        return typeInfo;
    }

    IBasicReflectableConstPtr<ALLOC> reflectable(const ALLOC& allocator = ALLOC()) const
    {
        class Reflectable : public ReflectableConstAllocatorHolderBase<ALLOC>
        {
        public:
            using ReflectableConstAllocatorHolderBase<ALLOC>::get_allocator;
            using ReflectableConstAllocatorHolderBase<ALLOC>::getField;
            using ReflectableConstAllocatorHolderBase<ALLOC>::getParameter;
            using ReflectableConstAllocatorHolderBase<ALLOC>::callFunction;

            explicit Reflectable(const DummyObject& owner, const ALLOC& allocator) :
                    ReflectableConstAllocatorHolderBase<ALLOC>(typeInfo(), allocator),
                    m_owner(owner)
            {}

            virtual IBasicReflectableConstPtr<ALLOC> getField(StringView name) const override
            {
                if (name == makeStringView("text"))
                {
                    return BasicReflectableFactory<ALLOC>::getString(m_owner.getText(), get_allocator());
                }
                throw CppRuntimeException("Field '") + name + "' doesn't exist in 'DummyNested'!";
            }

            virtual void write(BitStreamWriter&) const override
            {
            }

            virtual size_t bitSizeOf(size_t) const override
            {
                return 0;
            }

        private:
            const DummyObject& m_owner;
        };

        return std::allocate_shared<Reflectable>(allocator, *this, allocator);
    }

    IBasicReflectablePtr<ALLOC> reflectable(const ALLOC& allocator = ALLOC())
    {
        class Reflectable : public ReflectableConstAllocatorHolderBase<ALLOC>
        {
        public:
            using ReflectableConstAllocatorHolderBase<ALLOC>::get_allocator;
            using ReflectableConstAllocatorHolderBase<ALLOC>::getField;
            using ReflectableConstAllocatorHolderBase<ALLOC>::getParameter;
            using ReflectableConstAllocatorHolderBase<ALLOC>::callFunction;

            explicit Reflectable(DummyObject& owner, const ALLOC& allocator) :
                    ReflectableConstAllocatorHolderBase<ALLOC>(typeInfo(), allocator),
                    m_owner(owner)
            {}

            virtual IBasicReflectablePtr<ALLOC> getField(StringView name) override
            {
                if (name == makeStringView("text"))
                {
                    return BasicReflectableFactory<ALLOC>::getString(m_owner.getText(), get_allocator());
                }
                throw CppRuntimeException("Field '") + name + "' doesn't exist in 'DummyNested'!";
            }

            virtual void setField(StringView name, const AnyHolder<ALLOC>& any) override
            {
                if (name == makeStringView("text"))
                {
                    m_owner.setText(any.template get<string<ALLOC>>());
                    return;
                }
                throw CppRuntimeException("Field '") + name + "' doesn't exist in 'DummyNested'!";
            }

            virtual void write(BitStreamWriter&) const override
            {
            }

            virtual size_t bitSizeOf(size_t) const override
            {
                return 0;
            }

        private:
            DummyObject& m_owner;
        };

        return std::allocate_shared<Reflectable>(allocator, *this, allocator);
    }

    void setText(const string<ALLOC>& text_)
    {
        m_text_ = text_;
    }

    const string<ALLOC>& getText() const
    {
        return m_text_;
    }

private:
    string<ALLOC> m_text_;
};

const std::string TEST_NAME = "DebugStringUtilTest";

} // namespace

TEST(DebugStringUtilTest, toJsonStreamDefault)
{
    std::ostringstream os;
    DummyObject<> dummyObject;
    toJsonStream(dummyObject, os);
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", os.str());

    // improve coverage
    IReflectablePtr reflectable = dummyObject.reflectable();
    ASSERT_TRUE(reflectable);
    ASSERT_EQ("test"_sv, reflectable->getField("text")->getStringView());
}

TEST(DebugStringUtilTest, toJsonStreamDefaultWithAlloc)
{
    std::ostringstream os;
    const DummyObject<> dummyObject;
    toJsonStream(dummyObject, os, std::allocator<uint8_t>());
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamDefaultWithPolymorphicAlloc)
{
    std::ostringstream os;
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    toJsonStream(dummyObject, os, pmr::PolymorphicAllocator<uint8_t>());
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamIndent2)
{
    std::ostringstream os;
    const DummyObject<> dummyObject;
    toJsonStream(dummyObject, os, 2);
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamIndent2WithAlloc)
{
    std::ostringstream os;
    const DummyObject<> dummyObject;
    toJsonStream(dummyObject, os, 2, std::allocator<uint8_t>());
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamIndent2WithPolymorphicAlloc)
{
    std::ostringstream os;
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    toJsonStream(dummyObject, os, 2, pmr::PolymorphicAllocator<uint8_t>());
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamFilter)
{
    std::ostringstream os;
    const DummyObject<> dummyObject;
    toJsonStream(dummyObject, os, DepthWalkFilter(0));
    ASSERT_EQ("{\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamFilterWithAlloc)
{
    std::ostringstream os;
    const DummyObject<> dummyObject;
    toJsonStream(dummyObject, os, DefaultWalkFilter(), std::allocator<uint8_t>());
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamFilterWithPolymorphicAlloc)
{
    std::ostringstream os;
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    toJsonStream(dummyObject, os, BasicDefaultWalkFilter<pmr::PolymorphicAllocator<uint8_t>>(),
            pmr::PolymorphicAllocator<uint8_t>());
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamIndent2Filter)
{
    std::ostringstream os;
    const DummyObject<> dummyObject;
    toJsonStream(dummyObject, os, 2, DefaultWalkFilter());
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamIndent2FilterWithAlloc)
{
    std::ostringstream os;
    const DummyObject<> dummyObject;
    toJsonStream(dummyObject, os, 2, DepthWalkFilter(0), std::allocator<uint8_t>());
    ASSERT_EQ("{\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStreamIndent2FilterWithPolymorphicAlloc)
{
    std::ostringstream os;
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    toJsonStream(dummyObject, os, 2, BasicDepthWalkFilter<pmr::PolymorphicAllocator<uint8_t>>(0),
            pmr::PolymorphicAllocator<uint8_t>());
    ASSERT_EQ("{\n}", os.str());
}

TEST(DebugStringUtilTest, toJsonStringDefault)
{
    const DummyObject<> dummyObject;
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", toJsonString(dummyObject));
}

TEST(DebugStringUtilTest, toJsonStringDefaultWithAlloc)
{
    const DummyObject<> dummyObject;
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", toJsonString(dummyObject, std::allocator<uint8_t>()));
}

TEST(DebugStringUtilTest, toJsonStringDefaultWithPolymorphicAlloc)
{
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", toJsonString(dummyObject, pmr::PolymorphicAllocator<uint8_t>()));
}

TEST(DebugStringUtilTest, toJsonStringIndent2)
{
    const DummyObject<> dummyObject;
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", toJsonString(dummyObject, 2));
}

TEST(DebugStringUtilTest, toJsonStringIndent2WithAlloc)
{
    const DummyObject<> dummyObject;
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", toJsonString(dummyObject, 2, std::allocator<uint8_t>()));
}

TEST(DebugStringUtilTest, toJsonStringIndent2WithPolymorphicAlloc)
{
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    ASSERT_EQ("{\n  \"text\": \"test\"\n}",
            toJsonString(dummyObject, 2, pmr::PolymorphicAllocator<uint8_t>()));
}

TEST(DebugStringUtilTest, toJsonStringFilter)
{
    const DummyObject<> dummyObject;
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", toJsonString(dummyObject, DefaultWalkFilter()));
}

TEST(DebugStringUtilTest, toJsonStringFilterWithAlloc)
{
    const DummyObject<> dummyObject;
    ASSERT_EQ("{\n    \"text\": \"test\"\n}",
            toJsonString(dummyObject, DefaultWalkFilter(), std::allocator<uint8_t>()));
}

TEST(DebugStringUtilTest, toJsonStringFilterWithPolymorphicAlloc)
{
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    ASSERT_EQ("{\n    \"text\": \"test\"\n}",
            toJsonString(dummyObject, BasicDefaultWalkFilter<pmr::PolymorphicAllocator<uint8_t>>(),
                    pmr::PolymorphicAllocator<uint8_t>()));
}

TEST(DebugStringUtilTest, toJsonStringIndent2Filter)
{
    const DummyObject<> dummyObject;
    ASSERT_EQ("{\n}", toJsonString(dummyObject, 2, DepthWalkFilter(0)));
}

TEST(DebugStringUtilTest, toJsonStringIndent2FilterWithAlloc)
{
    const DummyObject<> dummyObject;
    ASSERT_EQ("{\n  \"text\": \"test\"\n}",
            toJsonString(dummyObject, 2, DefaultWalkFilter(), std::allocator<uint8_t>()));
}

TEST(DebugStringUtilTest, toJsonStringIndent2FilterWithPolymorphicAlloc)
{
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    ASSERT_EQ("{\n  \"text\": \"test\"\n}",
            toJsonString(dummyObject, 2, BasicDefaultWalkFilter<pmr::PolymorphicAllocator<uint8_t>>(),
                    pmr::PolymorphicAllocator<uint8_t>()));
}

TEST(DebugStringUtilTest, toJsonFileDefault)
{
    const DummyObject<> dummyObject;
    const std::string fileName = "DebugStringUtilTest_default.json";
    toJsonFile(dummyObject, fileName);

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileDefaultWithAlloc)
{
    const DummyObject<> dummyObject;
    const std::string fileName = "DebugStringUtilTest_defaultWithAlloc.json";
    toJsonFile(dummyObject, fileName, std::allocator<uint8_t>());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileDefaultWithPolymorphicAlloc)
{
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    const string<pmr::PolymorphicAllocator<char>> fileName =
            "DebugStringUtilTest_defaultWithPolymorphicAlloc.json";
    toJsonFile(dummyObject, fileName, pmr::PolymorphicAllocator<uint8_t>());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileIndent2)
{
    const DummyObject<> dummyObject;
    const std::string fileName = "DebugStringUtilTest_indent2.json";
    toJsonFile(dummyObject, fileName, 2);

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileIndent2WithAlloc)
{
    const DummyObject<> dummyObject;
    const std::string fileName = "DebugStringUtilTest_indent2WithAlloc.json";
    toJsonFile(dummyObject, fileName, 2, std::allocator<uint8_t>());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileIndent2WithPolymorphicAlloc)
{
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    const string<pmr::PolymorphicAllocator<char>> fileName =
            "DebugStringUtilTest_indent2WithPolymorphicAlloc.json";
    toJsonFile(dummyObject, fileName, 2, pmr::PolymorphicAllocator<uint8_t>());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileFilter)
{
    const DummyObject<> dummyObject;
    const std::string fileName = "DebugStringUtilTest_filter.json";
    toJsonFile(dummyObject, fileName, DefaultWalkFilter());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileFilterWithAlloc)
{
    const DummyObject<> dummyObject;
    DefaultWalkFilter defaultWalkFilter;
    const std::string fileName = "DebugStringUtilTest_filterWithAlloc.json";
    toJsonFile(dummyObject, fileName, defaultWalkFilter, std::allocator<uint8_t>());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileFilterWithPolymorphicAlloc)
{
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    BasicDefaultWalkFilter<pmr::PolymorphicAllocator<uint8_t>> defaultWalkFilter;
    const string<pmr::PolymorphicAllocator<char>> fileName =
            "DebugStringUtilTest_filterWithPolymorphicAlloc.json";
    toJsonFile(dummyObject, fileName, defaultWalkFilter, pmr::PolymorphicAllocator<uint8_t>());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n    \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileIndent2Filter)
{
    const DummyObject<> dummyObject;
    DepthWalkFilter depthWalkFilter(0);
    const std::string fileName = "DebugStringUtilTest_indent2Filter.json";
    toJsonFile(dummyObject, fileName, 2, depthWalkFilter);

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileIndent2FilterWithAlloc)
{
    const DummyObject<> dummyObject;
    DefaultWalkFilter defaultWalkFilter;
    const std::string fileName = "DebugStringUtilTest_indent2FilterWithAlloc.json";
    toJsonFile(dummyObject, fileName, 2, defaultWalkFilter, std::allocator<uint8_t>());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, toJsonFileIndent2FilterWithPolymorphicAlloc)
{
    const DummyObject<pmr::PolymorphicAllocator<uint8_t>> dummyObject;
    BasicDefaultWalkFilter<pmr::PolymorphicAllocator<uint8_t>> defaultWalkFilter;
    const string<pmr::PolymorphicAllocator<char>> fileName =
            "DebugStringUtilTest_indent2FilterWithPolymorphicAlloc.json";
    toJsonFile(dummyObject, fileName, 2, defaultWalkFilter, pmr::PolymorphicAllocator<uint8_t>());

    std::ifstream is(fileName.c_str());
    std::stringstream ss;
    ss << is.rdbuf();
    ASSERT_EQ("{\n  \"text\": \"test\"\n}", ss.str());
}

TEST(DebugStringUtilTest, fromJsonStream)
{
    std::istringstream ss("{\n  \"text\": \"something\"\n}");
    IReflectablePtr reflectable = fromJsonStream(DummyObject<>::typeInfo(), ss);
    ASSERT_TRUE(reflectable);

    ASSERT_EQ("something"_sv, reflectable->getField("text")->getStringView());
}

TEST(DebugStringUtilTest, fromJsonStreamTemplate)
{
    std::istringstream ss("{\n  \"text\": \"something\"\n}");
    IReflectablePtr reflectable = fromJsonStream<DummyObject<>>(ss);
    ASSERT_TRUE(reflectable);

    ASSERT_EQ("something"_sv, reflectable->getField("text")->getStringView());
}

TEST(DebugStringUtilTest, fromJsonString)
{
    std::string jsonString("{\n  \"text\": \"something\"\n}");
    IReflectablePtr reflectable = fromJsonString(DummyObject<>::typeInfo(), jsonString);
    ASSERT_TRUE(reflectable);

    ASSERT_EQ("something"_sv, reflectable->getField("text")->getStringView());
}

TEST(DebugStringUtilTest, fromJsonStringTemplate)
{
    std::string jsonString("{\n  \"text\": \"something\"\n}");
    IReflectablePtr reflectable = fromJsonString<DummyObject<>>(jsonString);
    ASSERT_TRUE(reflectable);

    ASSERT_EQ("something"_sv, reflectable->getField("text")->getStringView());
}

TEST(DebugStringUtilTest, fromJsonFile)
{
    const char* fileName = "DebugStringUtilTest_fromJsonFile.json";
    {
        std::ofstream os(fileName);
        os << "{\n  \"text\": \"something\"\n}";
    }

    IReflectablePtr reflectable = fromJsonFile(DummyObject<>::typeInfo(), fileName);
    ASSERT_TRUE(reflectable);

    ASSERT_EQ("something"_sv, reflectable->getField("text")->getStringView());
}

TEST(DebugStringUtilTest, fromJsonFileTemplate)
{
    const char* fileName = "DebugStringUtilTest_fromJsonFile.json";
    {
        std::ofstream os(fileName);
        os << "{\n  \"text\": \"something\"\n}";
    }

    IReflectablePtr reflectable = fromJsonFile<DummyObject<>>(fileName);
    ASSERT_TRUE(reflectable);

    ASSERT_EQ("something"_sv, reflectable->getField("text")->getStringView());
}

} // namespace zserio
