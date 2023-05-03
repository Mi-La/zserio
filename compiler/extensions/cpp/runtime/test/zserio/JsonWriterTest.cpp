#include "gtest/gtest.h"

#include <sstream>

#include "zserio/JsonWriter.h"
#include "zserio/TypeInfo.h"
#include "zserio/Reflectable.h"

namespace zserio
{

class JsonWriterTest : public ::testing::Test
{
public:
    JsonWriterTest() :
            BOOL_FIELD_INFO{"boolField"_sv, BuiltinTypeInfo<>::getBool(),
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            INT_FIELD_INFO{"intField"_sv, BuiltinTypeInfo<>::getInt32(),
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            FLOAT_FIELD_INFO{"floatField"_sv, BuiltinTypeInfo<>::getFloat32(),
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            DOUBLE_FIELD_INFO{"doubleField"_sv, BuiltinTypeInfo<>::getFloat64(),
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            TEXT_FIELD_INFO{"text"_sv, BuiltinTypeInfo<>::getString(),
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            IDENTIFIER_FIELD_INFO{"identifier", BuiltinTypeInfo<>::getUInt32(),
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            EXTERN_DATA_FIELD_INFO{"externData"_sv, BuiltinTypeInfo<>::getBitBuffer(),
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            BYTES_DATA_FIELD_INFO{"bytesData"_sv, BuiltinTypeInfo<>::getBytes(),
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            DUMMY_TYPE_INFO{"Dummy"_sv, nullptr, {}, {}, {}, {}, {}},
            NESTED_FIELD_INFO{"nested"_sv, DUMMY_TYPE_INFO,
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            ARRAY_FIELD_INFO{"array", BuiltinTypeInfo<>::getUInt32(),
                    {}, {}, {}, {}, false, {}, {}, true, {}, false, false},
            ENUM_ITEMS{
                    ItemInfo{"ZERO"_sv, static_cast<uint64_t>(0)},
                    ItemInfo{"One"_sv, static_cast<uint64_t>(1)},
                    ItemInfo{"MINUS_ONE"_sv, static_cast<uint64_t>(-1)}},
            ENUM_TYPE_INFO{"DummyEnum"_sv, BuiltinTypeInfo<>::getInt8(), {}, ENUM_ITEMS},
            ENUM_FIELD_INFO{"enumField"_sv, ENUM_TYPE_INFO,
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false},
            BITMASK_ITEMS{
                    ItemInfo{"ZERO"_sv, static_cast<uint64_t>(0)},
                    ItemInfo{"One"_sv, static_cast<uint64_t>(1)},
                    ItemInfo{"TWO"_sv, static_cast<uint64_t>(2)}},
            BITMASK_TYPE_INFO{"DummyBitmask"_sv, BuiltinTypeInfo<>::getUInt32(), {}, BITMASK_ITEMS},
            BITMASK_FIELD_INFO{"bitmaskField"_sv, BITMASK_TYPE_INFO,
                    {}, {}, {}, {}, false, {}, {}, false, {}, false, false}
    {}

protected:
    void walkNested(IWalkObserver& observer)
    {
        observer.beginRoot(nullptr);
        observer.visitValue(ReflectableFactory::getUInt32(13), IDENTIFIER_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.beginCompound(nullptr, NESTED_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(ReflectableFactory::getString("test"_sv), TEXT_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.endCompound(nullptr, NESTED_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.endRoot(nullptr);
    }

    void walkArray(IWalkObserver& observer)
    {
        observer.beginRoot(nullptr);
        observer.beginArray(nullptr, ARRAY_FIELD_INFO);
        observer.visitValue(ReflectableFactory::getUInt32(1), ARRAY_FIELD_INFO, 0);
        observer.visitValue(ReflectableFactory::getUInt32(2), ARRAY_FIELD_INFO, 1);
        observer.endArray(nullptr, ARRAY_FIELD_INFO);
        observer.endRoot(nullptr);
    }

    const FieldInfo BOOL_FIELD_INFO;
    const FieldInfo INT_FIELD_INFO;
    const FieldInfo FLOAT_FIELD_INFO;
    const FieldInfo DOUBLE_FIELD_INFO;
    const FieldInfo TEXT_FIELD_INFO;
    const FieldInfo IDENTIFIER_FIELD_INFO;
    const FieldInfo EXTERN_DATA_FIELD_INFO;
    const FieldInfo BYTES_DATA_FIELD_INFO;
    const StructTypeInfo<std::allocator<uint8_t>> DUMMY_TYPE_INFO;
    const FieldInfo NESTED_FIELD_INFO;
    const FieldInfo ARRAY_FIELD_INFO;
    const std::array<ItemInfo, 3> ENUM_ITEMS;
    const EnumTypeInfo<std::allocator<uint8_t>> ENUM_TYPE_INFO;
    const FieldInfo ENUM_FIELD_INFO;
    const std::array<ItemInfo, 3> BITMASK_ITEMS;
    const BitmaskTypeInfo<std::allocator<uint8_t>> BITMASK_TYPE_INFO;
    const FieldInfo BITMASK_FIELD_INFO;
};

TEST_F(JsonWriterTest, empty)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);

    ASSERT_EQ("", os.str());
}

TEST_F(JsonWriterTest, nullValue)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);
    IWalkObserver& observer = jsonWriter;

    observer.visitValue(nullptr, TEXT_FIELD_INFO, WALKER_NOT_ELEMENT);

    // note that this is not valid json
    ASSERT_EQ("\"text\": null", os.str());
}

TEST_F(JsonWriterTest, textValue)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);
    IWalkObserver& observer = jsonWriter;

    observer.visitValue(ReflectableFactory::getString("test"_sv), TEXT_FIELD_INFO, WALKER_NOT_ELEMENT);

    // note that this is not valid json
    ASSERT_EQ("\"text\": \"test\"", os.str());
}

TEST_F(JsonWriterTest, boolValue)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);
    IWalkObserver& observer = jsonWriter;

    observer.visitValue(ReflectableFactory::getBool(true), BOOL_FIELD_INFO, WALKER_NOT_ELEMENT);

    // note that this is not valid json
    ASSERT_EQ("\"boolField\": true", os.str());
}

TEST_F(JsonWriterTest, intValue)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);
    IWalkObserver& observer = jsonWriter;

    observer.visitValue(ReflectableFactory::getInt32(INT32_MIN), INT_FIELD_INFO, WALKER_NOT_ELEMENT);

    // note that this is not valid json
    ASSERT_EQ("\"intField\": " + std::to_string(INT32_MIN), os.str());
}

TEST_F(JsonWriterTest, floatValue)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);
    IWalkObserver& observer = jsonWriter;

    observer.visitValue(ReflectableFactory::getFloat32(3.5F), FLOAT_FIELD_INFO, WALKER_NOT_ELEMENT);

    // note that this is not valid json
    ASSERT_EQ("\"floatField\": 3.5", os.str());
}

TEST_F(JsonWriterTest, doubleValue)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);
    IWalkObserver& observer = jsonWriter;

    observer.visitValue(ReflectableFactory::getFloat64(9.875), DOUBLE_FIELD_INFO, WALKER_NOT_ELEMENT);

    // note that this is not valid json
    ASSERT_EQ("\"doubleField\": 9.875", os.str());
}

TEST_F(JsonWriterTest, enumValue)
{
    class DummyEnumReflectable : public ReflectableBase<std::allocator<uint8_t>>
    {
    public:
        explicit DummyEnumReflectable(int8_t value, const EnumTypeInfo<std::allocator<uint8_t>>& typeInfo) :
                ReflectableBase<std::allocator<uint8_t>>(typeInfo),
                m_value(value)
        {}

        size_t bitSizeOf(size_t) const override
        {
            return 0;
        }

        void write(BitStreamWriter&) const override
        {
        }

        AnyHolder<> getAnyValue(const std::allocator<uint8_t>& allocator) const override
        {
            return AnyHolder<>(m_value, allocator);
        }

        AnyHolder<> getAnyValue(const std::allocator<uint8_t>& allocator) override
        {
            return AnyHolder<>(m_value, allocator);
        }

        int64_t toInt() const override
        {
            return m_value;
        }

    private:
        int8_t m_value;
    };

    IReflectableConstPtr reflectableZeroConst = std::make_shared<DummyEnumReflectable>(0, ENUM_TYPE_INFO);
    ASSERT_EQ(0, reflectableZeroConst->getAnyValue().get<int8_t>()); // improve coverage
    IReflectablePtr reflectableZero = std::make_shared<DummyEnumReflectable>(0, ENUM_TYPE_INFO);
    ASSERT_EQ(0, reflectableZero->getAnyValue().get<int8_t>()); // improve coverage
    IReflectablePtr reflectableOne = std::make_shared<DummyEnumReflectable>(1, ENUM_TYPE_INFO);
    IReflectablePtr reflectableTwo = std::make_shared<DummyEnumReflectable>(2, ENUM_TYPE_INFO);
    IReflectablePtr reflectableMinusOne = std::make_shared<DummyEnumReflectable>(-1, ENUM_TYPE_INFO);

    {
        std::ostringstream os;
        JsonWriter jsonWriter(os);
        IWalkObserver& observer = jsonWriter;
        observer.visitValue(reflectableZero, ENUM_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableOne, ENUM_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableTwo, ENUM_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableMinusOne, ENUM_FIELD_INFO, WALKER_NOT_ELEMENT);

        // note that this is not valid json
        ASSERT_EQ(
                "\"enumField\": \"ZERO\", "
                "\"enumField\": \"One\", "
                "\"enumField\": \"2 /* no match */\", "
                "\"enumField\": \"MINUS_ONE\"", os.str());


        // just improve coverage
        ASSERT_EQ(0, reflectableZero->bitSizeOf());
        BitBuffer bitBuffer(0);
        BitStreamWriter writer(bitBuffer);
        ASSERT_NO_THROW(reflectableZero->write(writer));
    }

    {
        std::ostringstream os;
        JsonWriter jsonWriter(os);
        jsonWriter.setEnumerableFormat(JsonWriter::EnumerableFormat::NUMBER);
        IWalkObserver& observer = jsonWriter;
        observer.visitValue(reflectableZero, ENUM_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableTwo, ENUM_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableMinusOne, ENUM_FIELD_INFO, WALKER_NOT_ELEMENT);

        // note that this is not valid json
        ASSERT_EQ("\"enumField\": 0, \"enumField\": 2, \"enumField\": -1", os.str());
    }
}

TEST_F(JsonWriterTest, bitmaskValue)
{
    class DummyBitmaskReflectable : public ReflectableBase<std::allocator<uint8_t>>
    {
    public:
        explicit DummyBitmaskReflectable(uint8_t value,
                const BitmaskTypeInfo<std::allocator<uint8_t>>& typeInfo) :
                ReflectableBase<std::allocator<uint8_t>>(typeInfo),
                m_value(value)
        {}

        size_t bitSizeOf(size_t) const override
        {
            return 0;
        }

        void write(BitStreamWriter&) const override
        {
        }

        AnyHolder<> getAnyValue(const std::allocator<uint8_t>& allocator) const override
        {
            return AnyHolder<>(m_value, allocator);
        }

        AnyHolder<> getAnyValue(const std::allocator<uint8_t>& allocator) override
        {
            return AnyHolder<>(m_value, allocator);
        }

        uint64_t toUInt() const override
        {
            return m_value;
        }

    private:
        uint8_t m_value;
    };

    IReflectableConstPtr reflectableZeroConst = std::make_shared<DummyBitmaskReflectable>(0, BITMASK_TYPE_INFO);
    ASSERT_EQ(0, reflectableZeroConst->getAnyValue().get<uint8_t>()); // improve coverage
    IReflectablePtr reflectableZero = std::make_shared<DummyBitmaskReflectable>(0, BITMASK_TYPE_INFO);
    ASSERT_EQ(0, reflectableZero->getAnyValue().get<uint8_t>()); // improve coverage
    IReflectablePtr reflectableTwo = std::make_shared<DummyBitmaskReflectable>(2, BITMASK_TYPE_INFO);
    IReflectablePtr reflectableThree = std::make_shared<DummyBitmaskReflectable>(3, BITMASK_TYPE_INFO);
    IReflectablePtr reflectableFour = std::make_shared<DummyBitmaskReflectable>(4, BITMASK_TYPE_INFO);
    IReflectablePtr reflectableSeven = std::make_shared<DummyBitmaskReflectable>(7, BITMASK_TYPE_INFO);

    {
        std::ostringstream os;
        JsonWriter jsonWriter(os);
        IWalkObserver& observer = jsonWriter;
        observer.visitValue(reflectableZero, BITMASK_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableTwo, BITMASK_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableThree, BITMASK_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableFour, BITMASK_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableSeven, BITMASK_FIELD_INFO, WALKER_NOT_ELEMENT);

        // note that this is not valid json
        ASSERT_EQ(
                "\"bitmaskField\": \"ZERO\", "
                "\"bitmaskField\": \"TWO\", "
                "\"bitmaskField\": \"One | TWO\", "
                "\"bitmaskField\": \"4 /* no match */\", "
                "\"bitmaskField\": \"7 /* partial match: One | TWO */\"", os.str());

        // just improve coverage
        ASSERT_EQ(0, reflectableZero->bitSizeOf());
        BitBuffer bitBuffer(0);
        BitStreamWriter writer(bitBuffer);
        ASSERT_NO_THROW(reflectableZero->write(writer));
    }

    {
        std::ostringstream os;
        JsonWriter jsonWriter(os);
        jsonWriter.setEnumerableFormat(JsonWriter::EnumerableFormat::NUMBER);
        IWalkObserver& observer = jsonWriter;
        observer.visitValue(reflectableZero, BITMASK_FIELD_INFO, WALKER_NOT_ELEMENT);
        observer.visitValue(reflectableSeven, BITMASK_FIELD_INFO, WALKER_NOT_ELEMENT);

        // note that this is not valid json
        ASSERT_EQ("\"bitmaskField\": 0, \"bitmaskField\": 7", os.str());
    }
}

TEST_F(JsonWriterTest, compound)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);
    IWalkObserver& observer = jsonWriter;

    observer.beginRoot(nullptr);
    observer.visitValue(ReflectableFactory::getUInt32(13), IDENTIFIER_FIELD_INFO, WALKER_NOT_ELEMENT);
    observer.visitValue(ReflectableFactory::getString("test"_sv), TEXT_FIELD_INFO, WALKER_NOT_ELEMENT);
    BitBuffer bitBuffer({0xFF, 0x1F}, 13);
    observer.visitValue(ReflectableFactory::getBitBuffer(bitBuffer), EXTERN_DATA_FIELD_INFO,
            WALKER_NOT_ELEMENT);
    vector<uint8_t> bytesData{{0xCA, 0xFE}};
    observer.visitValue(ReflectableFactory::getBytes(bytesData), BYTES_DATA_FIELD_INFO, WALKER_NOT_ELEMENT);
    observer.endRoot(nullptr);

    ASSERT_EQ("{\"identifier\": 13, \"text\": \"test\", "
            "\"externData\": {\"buffer\": [255, 31], \"bitSize\": 13}, "
            "\"bytesData\": {\"buffer\": [202, 254]}}", os.str());
}

TEST_F(JsonWriterTest, nestedCompound)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);

    walkNested(jsonWriter);

    ASSERT_EQ("{\"identifier\": 13, \"nested\": {\"text\": \"test\"}}", os.str());
}

TEST_F(JsonWriterTest, array)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);

    walkArray(jsonWriter);

    ASSERT_EQ("{\"array\": [1, 2]}", os.str());
}

TEST_F(JsonWriterTest, arrayWithIndent)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os, 2);

    walkArray(jsonWriter);

    ASSERT_EQ("{\n  \"array\": [\n    1,\n    2\n  ]\n}", os.str());
}

TEST_F(JsonWriterTest, emptyIndent)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os, "");

    walkNested(jsonWriter);

    ASSERT_EQ("{\n\"identifier\": 13,\n\"nested\": {\n\"text\": \"test\"\n}\n}", os.str());
}

TEST_F(JsonWriterTest, strIndent)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os, "  ");

    walkNested(jsonWriter);

    ASSERT_EQ("{\n  \"identifier\": 13,\n  \"nested\": {\n    \"text\": \"test\"\n  }\n}", os.str());
}

TEST_F(JsonWriterTest, intIndent)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os, 2);

    walkNested(jsonWriter);

    ASSERT_EQ("{\n  \"identifier\": 13,\n  \"nested\": {\n    \"text\": \"test\"\n  }\n}", os.str());
}

TEST_F(JsonWriterTest, compactSeparators)
{
    std::ostringstream os;
    JsonWriter jsonWriter(os);
    jsonWriter.setItemSeparator(",");
    jsonWriter.setKeySeparator(":");

    walkNested(jsonWriter);

    ASSERT_EQ("{\"identifier\":13,\"nested\":{\"text\":\"test\"}}", os.str());
}

} // namespace zserio
