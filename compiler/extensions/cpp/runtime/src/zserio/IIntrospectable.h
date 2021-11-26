#ifndef ZSERIO_I_INTROSPECTABLE_H_INC
#define ZSERIO_I_INTROSPECTABLE_H_INC

#include <memory>

#include "zserio/ITypeInfo.h"
#include "zserio/BitBuffer.h"
#include "zserio/String.h"
#include "zserio/RebindAlloc.h"
#include "zserio/AnyHolder.h"
#include "zserio/BitStreamWriter.h"

namespace zserio
{

// TODO[Mi-L@]:
// IBasicIntrospectable is just an *VIEW* to Zserio objects and users are responsible for objects lifetime!
template <typename ALLOC = std::allocator<uint8_t>>
class IBasicIntrospectable
{
public:
    using Ptr = std::shared_ptr<IBasicIntrospectable>;

    virtual ~IBasicIntrospectable() {};

    virtual const ITypeInfo& getTypeInfo() const = 0;
    virtual bool isArray() const = 0;

    virtual Ptr getField(StringView name) const = 0;
    virtual void setField(StringView name, const AnyHolder<ALLOC>& value) = 0;
    virtual Ptr getParameter(StringView name) const = 0;
    virtual Ptr callFunction(StringView name) const = 0;

    virtual StringView getChoice() const = 0;

    virtual Ptr find(StringView path) const = 0;
    virtual Ptr operator[](StringView path) const = 0;

    virtual size_t size() const = 0;
    virtual Ptr at(size_t index) const = 0;
    virtual Ptr operator[](size_t index) const = 0;

    virtual bool getBool() const = 0;
    virtual int8_t getInt8() const = 0;
    virtual int16_t getInt16() const = 0;
    virtual int32_t getInt32() const = 0;
    virtual int64_t getInt64() const = 0;
    virtual uint8_t getUInt8() const = 0;
    virtual uint16_t getUInt16() const = 0;
    virtual uint32_t getUInt32() const = 0;
    virtual uint64_t getUInt64() const = 0;
    virtual float getFloat() const = 0;
    virtual double getDouble() const = 0;
    virtual const string<RebindAlloc<ALLOC, char>>& getString() const = 0;
    virtual const BasicBitBuffer<ALLOC>& getBitBuffer() const = 0;

    virtual int64_t toInt() const = 0;
    virtual uint64_t toUInt() const = 0;
    virtual double toDouble() const = 0;
    virtual string<RebindAlloc<ALLOC, char>> toString(const ALLOC& allocator = ALLOC()) const = 0;

    virtual void write(BitStreamWriter& writer) = 0;
};

using IIntrospectable = IBasicIntrospectable<>;
using IIntrospectablePtr = IIntrospectable::Ptr;

/**
 * Gets introspectable view for the given enum item.
 *
 * \param value Enum value to introspect.
 * \param allocator Allocator to use for introspectable allocation.
 *
 * \return Enum introspectable view.
 */
template <typename T, typename ALLOC = std::allocator<uint8_t>>
typename IBasicIntrospectable<ALLOC>::Ptr enumIntrospectable(T value, const ALLOC& allocator = ALLOC());

} // namespace zserio

#endif // ZSERIO_I_INTROSPECTABLE_H_INC
