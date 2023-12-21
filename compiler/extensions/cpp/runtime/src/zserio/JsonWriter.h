#ifndef ZSERIO_JSON_WRITER_H_INC
#define ZSERIO_JSON_WRITER_H_INC

#include <ostream>

#include "zserio/AllocatorHolder.h"
#include "zserio/IWalkObserver.h"
#include "zserio/JsonEncoder.h"
#include "zserio/OptionalHolder.h"
#include "zserio/TypeInfoUtil.h"

namespace zserio
{

/**
 * Walker observer which dumps zserio objects to JSON format.
 */
template <typename ALLOC = std::allocator<uint8_t>>
class BasicJsonWriter : public IBasicWalkObserver<ALLOC>, public AllocatorHolder<ALLOC>
{
public:
    using AllocatorHolder<ALLOC>::get_allocator;

    /**
     * Default item separator used when indent is not set.
     */
    static constexpr const char* DEFAULT_ITEM_SEPARATOR = ", ";

    /**
     * Default item separator used when indent is set.
     */
    static constexpr const char* DEFAULT_ITEM_SEPARATOR_WITH_INDENT = ",";

    /**
     * Default key separator.
     */
    static constexpr const char* DEFAULT_KEY_SEPARATOR = ": ";

    /**
     * Configuration for writing of enumerable types.
     */
    enum class EnumerableFormat
    {
        /** Print as JSON integral value. */
        NUMBER,
        /**
         * Print as JSON string according to the following rules:
         *
         * 1. Enums
         *   * when an exact match with an enumerable item is found, the item name is used - e.g. "FIRST",
         *   * when no exact match is found, it's an invalid value, the integral value is converted to string
         *     and an appropriate comment is included - e.g. \"10 /<span>*</span> no match <span>*</span>/\".
         *
         * 2. Bitmasks
         *   * when an exact mach with or-ed bitmask values is found, it's used - e.g. "READ | WRITE",
         *   * when no exact match is found, but some or-ed values match, the integral value is converted
         *     to string and the or-ed values are included in a comment - e.g.
         *     \"127 /<span>*</span> READ | CREATE <span>*</span>/\",
         *   * when no match is found at all, the integral value is converted to string and an appropriate
         *     comment is included - e.g. \"13 /<span>*</span> no match <span>*</span>/\".
         */
        STRING
    };
    /**
     * Default configuration for enumerable types.
     */
    static constexpr EnumerableFormat DEFAULT_ENUMERABLE_FORMAT = EnumerableFormat::STRING;

    /**
     * Constructor.
     *
     * \param out Stream to use for writing.
     * \param allocator Allocator to use.
     */
    explicit BasicJsonWriter(std::ostream& out, const ALLOC& allocator = ALLOC());

    /**
     * Constructor.
     *
     * \param out Stream to use for writing.
     * \param indent Indent as a number of ' ' to be used for indentation.
     * \param allocator Allocator to use.
     */
    BasicJsonWriter(std::ostream& out, uint8_t indent, const ALLOC& allocator = ALLOC());

    /**
     * Constructor.
     *
     * \param out Stream to use for writing.
     * \param indent Indent as a string to be used for indentation.
     * \param allocator Allocator to use.
     */
    BasicJsonWriter(std::ostream& out, const string<ALLOC>& indent, const ALLOC& allocator = ALLOC());

    /**
     * Method generated by default.
     */
    ~BasicJsonWriter() override = default;

    /**
     * Copying and moving is disallowed!
     * \{
     */
    BasicJsonWriter(const BasicJsonWriter& other) = delete;
    BasicJsonWriter& operator=(const BasicJsonWriter& other) = delete;

    BasicJsonWriter(BasicJsonWriter&& other) = delete;
    BasicJsonWriter& operator=(BasicJsonWriter&& other) = delete;
    /**
     * \}
     */

    /**
     * Sets custom item separator.
     *
     * Use with caution since setting of a wrong separator can lead to invalid JSON output.
     *
     * \param itemSeparator Item separator to set.
     */
    void setItemSeparator(const string<ALLOC>& itemSeparator);

    /**
     * Sets custom key separator.
     *
     * Use with caution since setting of a wrong separator can lead to invalid JSON output.
     *
     * \param keySeparator Key separator to set.
     */
    void setKeySeparator(const string<ALLOC>& keySeparator);

    /**
     * Sets preferred formatting for enumerable types.
     *
     * @param enumerableFormat Enumerable format to use.
     */
    void setEnumerableFormat(EnumerableFormat enumerableFormat);

    void beginRoot(const IBasicReflectableConstPtr<ALLOC>& compound) override;
    void endRoot(const IBasicReflectableConstPtr<ALLOC>& compound) override;

    void beginArray(
            const IBasicReflectableConstPtr<ALLOC>& array, const BasicFieldInfo<ALLOC>& fieldInfo) override;
    void endArray(
            const IBasicReflectableConstPtr<ALLOC>& array, const BasicFieldInfo<ALLOC>& fieldInfo) override;

    void beginCompound(const IBasicReflectableConstPtr<ALLOC>& compound, const BasicFieldInfo<ALLOC>& fieldInfo,
            size_t elementIndex) override;
    void endCompound(const IBasicReflectableConstPtr<ALLOC>& compound, const BasicFieldInfo<ALLOC>& fieldInfo,
            size_t elementIndex) override;

    void visitValue(const IBasicReflectableConstPtr<ALLOC>& value, const BasicFieldInfo<ALLOC>& fieldInfo,
            size_t elementIndex) override;

private:
    BasicJsonWriter(std::ostream& out, InplaceOptionalHolder<string<ALLOC>>&& optionalIndent,
            const ALLOC& allocator = ALLOC());

    void beginItem();
    void endItem();
    void beginObject();
    void endObject();
    void beginArray();
    void endArray();

    void writeIndent();
    void writeKey(StringView key);
    void writeValue(const IBasicReflectableConstPtr<ALLOC>& reflectable);
    void writeBitBuffer(const BasicBitBuffer<ALLOC>& bitBuffer);
    void writeBytes(Span<const uint8_t> value);
    void writeStringifiedEnum(const IBasicReflectableConstPtr<ALLOC>& reflectable);
    void writeStringifiedBitmask(const IBasicReflectableConstPtr<ALLOC>& reflectable);

    std::ostream& m_out;
    InplaceOptionalHolder<string<ALLOC>> m_indent;
    string<ALLOC> m_itemSeparator;
    string<ALLOC> m_keySeparator;
    EnumerableFormat m_enumerableFormat = DEFAULT_ENUMERABLE_FORMAT;

    bool m_isFirst = true;
    size_t m_level = 0;
};

/** Typedef to JsonWriter provided for convenience - using default std::allocator<uint8_t>. */
/** \{ */
using JsonWriter = BasicJsonWriter<>;
/** \} */

template <typename ALLOC>
BasicJsonWriter<ALLOC>::BasicJsonWriter(std::ostream& out, const ALLOC& allocator) :
        BasicJsonWriter(out, NullOpt, allocator)
{}

template <typename ALLOC>
BasicJsonWriter<ALLOC>::BasicJsonWriter(std::ostream& out, uint8_t indent, const ALLOC& allocator) :
        BasicJsonWriter(out, string<ALLOC>(indent, ' ', allocator), allocator)
{}

template <typename ALLOC>
BasicJsonWriter<ALLOC>::BasicJsonWriter(
        std::ostream& out, const string<ALLOC>& indent, const ALLOC& allocator) :
        BasicJsonWriter(out, InplaceOptionalHolder<string<ALLOC>>(indent), allocator)
{}

template <typename ALLOC>
BasicJsonWriter<ALLOC>::BasicJsonWriter(
        std::ostream& out, InplaceOptionalHolder<string<ALLOC>>&& optionalIndent, const ALLOC& allocator) :
        AllocatorHolder<ALLOC>(allocator),
        m_out(out),
        m_indent(optionalIndent),
        m_itemSeparator(
                m_indent.hasValue() ? DEFAULT_ITEM_SEPARATOR_WITH_INDENT : DEFAULT_ITEM_SEPARATOR, allocator),
        m_keySeparator(DEFAULT_KEY_SEPARATOR, allocator)
{}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::setItemSeparator(const string<ALLOC>& itemSeparator)
{
    m_itemSeparator = itemSeparator;
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::setKeySeparator(const string<ALLOC>& keySeparator)
{
    m_keySeparator = keySeparator;
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::setEnumerableFormat(EnumerableFormat enumerableFormat)
{
    m_enumerableFormat = enumerableFormat;
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::beginRoot(const IBasicReflectableConstPtr<ALLOC>&)
{
    beginObject();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::endRoot(const IBasicReflectableConstPtr<ALLOC>&)
{
    endObject();
    m_out.flush();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::beginArray(
        const IBasicReflectableConstPtr<ALLOC>&, const BasicFieldInfo<ALLOC>& fieldInfo)
{
    beginItem();

    writeKey(fieldInfo.schemaName);

    beginArray();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::endArray(const IBasicReflectableConstPtr<ALLOC>&, const BasicFieldInfo<ALLOC>&)
{
    endArray();

    endItem();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::beginCompound(
        const IBasicReflectableConstPtr<ALLOC>&, const BasicFieldInfo<ALLOC>& fieldInfo, size_t elementIndex)
{
    beginItem();

    if (elementIndex == WALKER_NOT_ELEMENT)
        writeKey(fieldInfo.schemaName);

    beginObject();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::endCompound(
        const IBasicReflectableConstPtr<ALLOC>&, const BasicFieldInfo<ALLOC>&, size_t)
{
    endObject();

    endItem();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::visitValue(const IBasicReflectableConstPtr<ALLOC>& value,
        const BasicFieldInfo<ALLOC>& fieldInfo, size_t elementIndex)
{
    beginItem();

    if (elementIndex == WALKER_NOT_ELEMENT)
        writeKey(fieldInfo.schemaName);

    writeValue(value);

    endItem();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::beginItem()
{
    if (!m_isFirst)
        m_out.write(m_itemSeparator.data(), static_cast<std::streamsize>(m_itemSeparator.size()));

    if (m_indent.hasValue())
        m_out.put('\n');

    writeIndent();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::endItem()
{
    m_isFirst = false;
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::beginObject()
{
    m_out.put('{');

    m_isFirst = true;
    m_level += 1;
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::endObject()
{
    if (m_indent.hasValue())
        m_out.put('\n');

    m_level -= 1;

    writeIndent();

    m_out.put('}');
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::beginArray()
{
    m_out.put('[');

    m_isFirst = true;
    m_level += 1;
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::endArray()
{
    if (m_indent.hasValue())
        m_out.put('\n');

    m_level -= 1;

    writeIndent();

    m_out.put(']');
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::writeIndent()
{
    if (m_indent.hasValue())
    {
        const auto& indent = m_indent.value();
        if (!indent.empty())
        {
            for (size_t i = 0; i < m_level; ++i)
                m_out.write(indent.data(), static_cast<std::streamsize>(indent.size()));
        }
    }
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::writeKey(StringView key)
{
    JsonEncoder::encodeString(m_out, key);
    m_out.write(m_keySeparator.data(), static_cast<std::streamsize>(m_keySeparator.size()));
    m_out.flush();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::writeValue(const IBasicReflectableConstPtr<ALLOC>& reflectable)
{
    if (!reflectable)
    {
        JsonEncoder::encodeNull(m_out);
        return;
    }

    const IBasicTypeInfo<ALLOC>& typeInfo = reflectable->getTypeInfo();
    switch (typeInfo.getCppType())
    {
    case CppType::BOOL:
        JsonEncoder::encodeBool(m_out, reflectable->getBool());
        break;
    case CppType::INT8:
    case CppType::INT16:
    case CppType::INT32:
    case CppType::INT64:
        JsonEncoder::encodeIntegral(m_out, reflectable->toInt());
        break;
    case CppType::UINT8:
    case CppType::UINT16:
    case CppType::UINT32:
    case CppType::UINT64:
        JsonEncoder::encodeIntegral(m_out, reflectable->toUInt());
        break;
    case CppType::FLOAT:
        JsonEncoder::encodeFloatingPoint(m_out, static_cast<double>(reflectable->getFloat()));
        break;
    case CppType::DOUBLE:
        JsonEncoder::encodeFloatingPoint(m_out, reflectable->getDouble());
        break;
    case CppType::BYTES:
        writeBytes(reflectable->getBytes());
        break;
    case CppType::STRING:
        JsonEncoder::encodeString(m_out, reflectable->getStringView());
        break;
    case CppType::BIT_BUFFER:
        writeBitBuffer(reflectable->getBitBuffer());
        break;
    case CppType::ENUM:
        if (m_enumerableFormat == EnumerableFormat::STRING)
            writeStringifiedEnum(reflectable);
        else if (TypeInfoUtil::isSigned(typeInfo.getUnderlyingType().getCppType()))
            JsonEncoder::encodeIntegral(m_out, reflectable->toInt());
        else
            JsonEncoder::encodeIntegral(m_out, reflectable->toUInt());
        break;
    case CppType::BITMASK:
        if (m_enumerableFormat == EnumerableFormat::STRING)
            writeStringifiedBitmask(reflectable);
        else
            JsonEncoder::encodeIntegral(m_out, reflectable->toUInt());
        break;
    default:
        throw CppRuntimeException("JsonWriter: Unexpected not-null value of type '")
                << typeInfo.getSchemaName() << "'!";
    }

    m_out.flush();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::writeBitBuffer(const BasicBitBuffer<ALLOC>& bitBuffer)
{
    beginObject();
    beginItem();
    writeKey("buffer"_sv);
    beginArray();
    Span<const uint8_t> buffer = bitBuffer.getData();
    for (uint8_t element : buffer)
    {
        beginItem();
        JsonEncoder::encodeIntegral(m_out, element);
        endItem();
    }
    endArray();
    endItem();
    beginItem();
    writeKey("bitSize"_sv);
    JsonEncoder::encodeIntegral(m_out, bitBuffer.getBitSize());
    endItem();
    endObject();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::writeBytes(Span<const uint8_t> value)
{
    beginObject();
    beginItem();
    writeKey("buffer"_sv);
    beginArray();
    for (uint8_t byte : value)
    {
        beginItem();
        JsonEncoder::encodeIntegral(m_out, byte);
        endItem();
    }
    endArray();
    endItem();
    endObject();
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::writeStringifiedEnum(const IBasicReflectableConstPtr<ALLOC>& reflectable)
{
    const auto& typeInfo = reflectable->getTypeInfo();
    const uint64_t enumValue = TypeInfoUtil::isSigned(typeInfo.getUnderlyingType().getCppType())
            ? static_cast<uint64_t>(reflectable->toInt())
            : reflectable->toUInt();
    for (const auto& itemInfo : typeInfo.getEnumItems())
    {
        if (itemInfo.value == enumValue)
        {
            // exact match
            JsonEncoder::encodeString(m_out, itemInfo.schemaName);
            return;
        }
    }

    // no match
    string<ALLOC> stringValue = TypeInfoUtil::isSigned(typeInfo.getUnderlyingType().getCppType())
            ? toString(reflectable->toInt(), get_allocator())
            : toString(reflectable->toUInt(), get_allocator());
    stringValue.append(" /* no match */");
    JsonEncoder::encodeString(m_out, stringValue);
}

template <typename ALLOC>
void BasicJsonWriter<ALLOC>::writeStringifiedBitmask(const IBasicReflectableConstPtr<ALLOC>& reflectable)
{
    string<ALLOC> stringValue(get_allocator());
    const auto& typeInfo = reflectable->getTypeInfo();
    const uint64_t bitmaskValue = reflectable->toUInt();
    uint64_t valueCheck = 0;
    for (const auto& itemInfo : typeInfo.getBitmaskValues())
    {
        if ((itemInfo.value != 0 && (bitmaskValue & itemInfo.value) == itemInfo.value) ||
                (itemInfo.value == 0 && bitmaskValue == 0))
        {
            valueCheck |= itemInfo.value;
            if (!stringValue.empty())
                stringValue += " | ";
            stringValue += toString(itemInfo.schemaName, get_allocator());
        }
    }

    if (stringValue.empty())
    {
        // no match
        stringValue.append(toString(bitmaskValue, get_allocator()));
        stringValue.append(" /* no match */");
    }
    else if (bitmaskValue != valueCheck)
    {
        // partial match
        stringValue =
                toString(bitmaskValue, get_allocator())
                        .append(" /* partial match: ")
                        .append(stringValue)
                        .append(" */");
    }
    // else exact match

    JsonEncoder::encodeString(m_out, stringValue);
}

} // namespace zserio

#endif // ZSERIO_JSON_WRITER_H_INC
