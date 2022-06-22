#ifndef ZSERIO_JSON_READER_H_INC
#define ZSERIO_JSON_READER_H_INC

#include <istream>

#include "zserio/JsonParser.h"
#include "zserio/OptionalHolder.h"
#include "zserio/ZserioTreeCreator.h"

namespace zserio
{

template <typename ALLOC = std::allocator<uint8_t>>
class BasicJsonReader
{
public:
    explicit BasicJsonReader(std::istream& in, const ALLOC& allocator = ALLOC()) :
            m_creatorAdapter(allocator), m_parser(in, m_creatorAdapter, allocator)
    {}

    IBasicReflectablePtr<ALLOC> read(const IBasicTypeInfo<ALLOC>& typeInfo)
    {
        m_creatorAdapter.setType(typeInfo);

        try
        {
            m_parser.parse();
        }
        catch (const JsonParserException&)
        {
            throw;
        }
        catch (const CppRuntimeException& e)
        {
            throw CppRuntimeException(e.what()) + " (JsonParser line " + m_parser.getLine() + ")";
        }

        return m_creatorAdapter.get();
    }

private:
    class BitBufferAdapter : public BasicJsonParser<ALLOC>::IObserver, AllocatorHolder<ALLOC>
    {
    public:
        using AllocatorHolder<ALLOC>::get_allocator;

        explicit BitBufferAdapter(const ALLOC& allocator) :
                AllocatorHolder<ALLOC>(allocator), m_state(VISIT_KEY), m_buffer(allocator), m_bitSize(0)
        {}

        BitBufferAdapter(BitBufferAdapter& other) = delete;
        BitBufferAdapter& operator=(BitBufferAdapter& other) = delete;

        BitBufferAdapter(BitBufferAdapter&& other) :
                m_state(other.m_state), m_buffer(std::move(other.m_buffer)), m_bitSize(other.m_bitSize)
        {}

        BitBufferAdapter& operator=(BitBufferAdapter&& other)
        {
            m_state = other.m_state;
            m_buffer = std::move(other.m_buffer);
            m_bitSize = other.m_bitSize;

            return *this;
        }

        BasicBitBuffer<ALLOC> get() const;

        virtual void beginObject() override;
        virtual void endObject() override;
        virtual void beginArray() override;
        virtual void endArray() override;
        virtual void visitKey(StringView key) override;
        virtual void visitValue(std::nullptr_t) override;
        virtual void visitValue(bool boolValue) override;
        virtual void visitValue(int64_t intValue) override;
        virtual void visitValue(uint64_t uintValue) override;
        virtual void visitValue(double doubleValue) override;
        virtual void visitValue(StringView stringValue) override;

    private:
        enum State : uint8_t
        {
            VISIT_KEY,
            BEGIN_ARRAY_BUFFER,
            VISIT_VALUE_BUFFER,
            VISIT_VALUE_BITSIZE
        };

        State m_state;
        vector<uint8_t, ALLOC> m_buffer;
        size_t m_bitSize;
    };

    class CreatorAdapter : public BasicJsonParser<ALLOC>::IObserver, AllocatorHolder<ALLOC>
    {
    public:
        using AllocatorHolder<ALLOC>::get_allocator;

        explicit CreatorAdapter(const ALLOC& allocator) :
                AllocatorHolder<ALLOC>(allocator)
        {}

        void setType(const IBasicTypeInfo<ALLOC>& typeInfo);
        IBasicReflectablePtr<ALLOC> get() const;

        virtual void beginObject() override;
        virtual void endObject() override;
        virtual void beginArray() override;
        virtual void endArray() override;
        virtual void visitKey(StringView key) override;
        virtual void visitValue(std::nullptr_t) override;
        virtual void visitValue(bool boolValue) override;
        virtual void visitValue(int64_t intValue) override;
        virtual void visitValue(uint64_t uintValue) override;
        virtual void visitValue(double doubleValue) override;
        virtual void visitValue(StringView stringValue) override;

    private:
        template <typename T>
        void setValue(T&& value);

        template <typename T>
        void convertValue(T&& value) const;

        InplaceOptionalHolder<BasicZserioTreeCreator<ALLOC>> m_creator;
        vector<string<ALLOC>, ALLOC> m_keyStack;
        IBasicReflectablePtr<ALLOC> m_object;
        InplaceOptionalHolder<BitBufferAdapter> m_bitBufferAdapter;
    };

    CreatorAdapter m_creatorAdapter;
    BasicJsonParser<ALLOC> m_parser;
};

template <typename ALLOC>
BasicBitBuffer<ALLOC> BasicJsonReader<ALLOC>::BitBufferAdapter::get() const
{
    if (m_state != VISIT_KEY)
        throw CppRuntimeException("JsonReader: Unexpected end in BitBuffer!");

    return BasicBitBuffer<ALLOC>(std::move(m_buffer), m_bitSize);
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::beginObject()
{
    throw CppRuntimeException("JsonReader: Unexpected beginObject in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::endObject()
{
    throw CppRuntimeException("JsonReader: Unexpected endObject in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::beginArray()
{
    if (m_state == BEGIN_ARRAY_BUFFER)
        m_state = VISIT_VALUE_BUFFER;
    else
        throw CppRuntimeException("JsonReader: Unexpected beginArray in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::endArray()
{
    if (m_state == VISIT_VALUE_BUFFER)
        m_state = VISIT_KEY;
    else
        throw CppRuntimeException("JsonReader: Unexpected endArray in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::visitKey(StringView key)
{
    if (m_state == VISIT_KEY)
    {
        if (key == "buffer"_sv)
            m_state = BEGIN_ARRAY_BUFFER;
        else if (key == "bitSize"_sv)
            m_state = VISIT_VALUE_BITSIZE;
        else
            throw CppRuntimeException("JsonReader: Unexpected key '") + key + "' in BitBuffer!";
    }
    else
    {
        throw CppRuntimeException("JsonReader: Unexpected visitKey in BitBuffer!");
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::visitValue(std::nullptr_t)
{
    throw CppRuntimeException("JsonReader: Unexpected visitValue (null) in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::visitValue(bool)
{
    throw CppRuntimeException("JsonReader: Unexpected visitValue (bool) in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::visitValue(int64_t)
{
    throw CppRuntimeException("JsonReader: Unexpected visitValue (int) in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::visitValue(uint64_t uintValue)
{
    if (m_state == VISIT_VALUE_BUFFER)
    {
        if (uintValue > UINT8_MAX)
            throw CppRuntimeException("JsonReader: Byte value overflow in BitBuffer!");
        m_buffer.push_back(static_cast<uint8_t>(uintValue));
    }
    else if (m_state == VISIT_VALUE_BITSIZE)
    {
        if (uintValue > SIZE_MAX)
            throw CppRuntimeException("JsonReader: Bit size value overflow in BitBuffer!");
        m_bitSize = static_cast<size_t>(uintValue);
        m_state = VISIT_KEY;
    }
    else
    {
        throw CppRuntimeException("JsonReader: Unexpected visitValue in BitBuffer!");
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::visitValue(double)
{
    throw CppRuntimeException("JsonReader: Unexpected visitValue (double) in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::BitBufferAdapter::visitValue(StringView)
{
    throw CppRuntimeException("JsonReader: Unexpected visitValue (string) in BitBuffer!");
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::setType(const IBasicTypeInfo<ALLOC>& typeInfo)
{
    m_creator = ZserioTreeCreator(typeInfo, get_allocator());
}

template <typename ALLOC>
IBasicReflectablePtr<ALLOC> BasicJsonReader<ALLOC>::CreatorAdapter::get() const
{
    if (!m_object)
        throw CppRuntimeException("JsonReader: Zserio tree not created!");

    return m_object;
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::beginObject()
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->beginObject();
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        if (m_keyStack.empty())
        {
            m_creator->beginRoot();
        }
        else
        {
            if (!m_keyStack.back().empty())
            {
                if (m_creator->getFieldType(m_keyStack.back()).getCppType() == CppType::BIT_BUFFER)
                    m_bitBufferAdapter = BitBufferAdapter(get_allocator());
                else
                    m_creator->beginCompound(m_keyStack.back());
            }
            else
            {
                if (m_creator->getElementType().getCppType() == CppType::BIT_BUFFER)
                    m_bitBufferAdapter = BitBufferAdapter(get_allocator());
                else
                    m_creator->beginCompoundElement();
            }
        }
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::endObject()
{
    if (m_bitBufferAdapter)
    {
        const auto& bitBuffer = m_bitBufferAdapter->get();
        setValue(bitBuffer);
        m_bitBufferAdapter.reset();
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        if (m_keyStack.empty())
        {
            m_object = m_creator->endRoot();
            m_creator.reset();
        }
        else
        {
            if (!m_keyStack.back().empty())
            {
                m_creator->endCompound();
                m_keyStack.pop_back();
            }
            else
            {
                m_creator->endCompoundElement();
            }
        }
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::beginArray()
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->beginArray();
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        if (m_keyStack.empty())
            throw CppRuntimeException("JsonReader: ZserioTreeCreator expects json object!");

        m_creator->beginArray(m_keyStack.back());

        m_keyStack.push_back("");
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::endArray()
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->endArray();
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        m_creator->endArray();

        m_keyStack.pop_back(); // finish array
        m_keyStack.pop_back(); // finish field
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::visitKey(StringView key)
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->visitKey(key);
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        m_keyStack.push_back(stringViewToString(key, get_allocator()));
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::visitValue(std::nullptr_t nullValue)
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->visitValue(nullValue);
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        setValue(nullValue);
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::visitValue(bool boolValue)
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->visitValue(boolValue);
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        setValue(boolValue);
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::visitValue(int64_t intValue)
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->visitValue(intValue);
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        setValue(intValue);
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::visitValue(uint64_t uintValue)
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->visitValue(uintValue);
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        setValue(uintValue);
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::visitValue(double doubleValue)
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->visitValue(doubleValue);
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        setValue(doubleValue);
    }
}

template <typename ALLOC>
void BasicJsonReader<ALLOC>::CreatorAdapter::visitValue(StringView stringValue)
{
    if (m_bitBufferAdapter)
    {
        m_bitBufferAdapter->visitValue(stringValue);
    }
    else
    {
        if (!m_creator)
            throw CppRuntimeException("JsonReader: Adapter not initialized!");

        setValue(stringValue);
    }
}

template <typename ALLOC>
template <typename T>
void BasicJsonReader<ALLOC>::CreatorAdapter::setValue(T&& value)
{
    if (m_keyStack.empty())
        throw CppRuntimeException("JsonReader: ZserioTreeCreator expects json object!");

    if (!m_keyStack.back().empty())
    {
        m_creator->setValue(m_keyStack.back(), std::forward<T>(value));
        m_keyStack.pop_back();
    }
    else
    {
        m_creator->addValueElement(std::forward<T>(value));
    }
}

using JsonReader = BasicJsonReader<>;

} // namespace zserio

#endif // ZSERIO_JSON_READER_H_INC
