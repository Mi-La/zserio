/**
 * Automatically generated by Zserio C++ extension version 1.2.0.
 */

#include <zserio/StringConvertUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/HashCodeUtil.h>
#include <zserio/BitPositionUtil.h>
#include <zserio/BitSizeOfCalculator.h>
#include <zserio/BitFieldUtil.h>

#include "Choice.h"


Choice::Choice() :
        m_isInitialized(false)
{
}

Choice::Choice(zserio::BitStreamReader& in,
        uint8_t selector_) :
        m_selector_(selector_),
        m_isInitialized(true)
{
    read(in);
}

Choice::Choice(const Choice& other) :
        m_objectChoice(other.m_objectChoice)
{
    if (other.m_isInitialized)
        initialize(other.m_selector_);
    else
        m_isInitialized = false;
}

Choice& Choice::operator=(const Choice& other)
{
    m_objectChoice = other.m_objectChoice;
    if (other.m_isInitialized)
        initialize(other.m_selector_);
    else
        m_isInitialized = false;

    return *this;
}

void Choice::initialize(
        uint8_t selector_)
{
    m_selector_ = selector_;
    m_isInitialized = true;
}

uint8_t Choice::getSelector() const
{
    if (!m_isInitialized)
        throw zserio::CppRuntimeException("Parameter selector of compound Choice "
                "is not initialized!");

    return m_selector_;
}

bool Choice::getValueBool() const
{
    return m_objectChoice.get<bool>();
}

void Choice::setValueBool(bool valueBool_)
{
    m_objectChoice.set(valueBool_);
}

uint16_t Choice::getValue16() const
{
    return m_objectChoice.get<uint16_t>();
}

void Choice::setValue16(uint16_t value16_)
{
    m_objectChoice.set(value16_);
}

uint64_t Choice::getValue64() const
{
    return m_objectChoice.get<uint64_t>();
}

void Choice::setValue64(uint64_t value64_)
{
    m_objectChoice.set(value64_);
}

size_t Choice::bitSizeOf(size_t bitPosition) const
{
    size_t endBitPosition = bitPosition;

    switch (getSelector())
    {
    case 0:
        endBitPosition += UINT8_C(1);
        break;
    case 1:
    case 2:
        endBitPosition += UINT8_C(16);
        break;
    default:
        endBitPosition += UINT8_C(64);
        break;
    }

    return endBitPosition - bitPosition;
}

size_t Choice::initializeOffsets(size_t bitPosition)
{
    size_t endBitPosition = bitPosition;

    switch (getSelector())
    {
    case 0:
        endBitPosition += UINT8_C(1);
        break;
    case 1:
    case 2:
        endBitPosition += UINT8_C(16);
        break;
    default:
        endBitPosition += UINT8_C(64);
        break;
    }

    return endBitPosition;
}

bool Choice::operator==(const Choice& other) const
{
    if (this == &other)
        return true;

    if (getSelector() != other.getSelector())
        return false;

    switch (getSelector())
    {
    case 0:
        return m_objectChoice.get<bool>() == other.m_objectChoice.get<bool>();
    case 1:
    case 2:
        return m_objectChoice.get<uint16_t>() == other.m_objectChoice.get<uint16_t>();
    default:
        return m_objectChoice.get<uint64_t>() == other.m_objectChoice.get<uint64_t>();
    }
}

int Choice::hashCode() const
{
    int result = zserio::HASH_SEED;

    result = zserio::calcHashCode(result, getSelector());
    switch (getSelector())
    {
    case 0:
        result = zserio::calcHashCode(result, m_objectChoice.get<bool>());
        break;
    case 1:
    case 2:
        result = zserio::calcHashCode(result, m_objectChoice.get<uint16_t>());
        break;
    default:
        result = zserio::calcHashCode(result, m_objectChoice.get<uint64_t>());
        break;
    }

    return result;
}

void Choice::read(zserio::BitStreamReader& in)
{
    switch (getSelector())
    {
    case 0:
        m_objectChoice = static_cast<bool>(in.readBool());
            break;
    case 1:
    case 2:
        m_objectChoice = static_cast<uint16_t>(in.readBits(UINT8_C(16)));
        break;
    default:
        m_objectChoice = static_cast<uint64_t>(in.readBits64(UINT8_C(64)));
        break;
    }
}

void Choice::write(zserio::BitStreamWriter& _out, zserio::PreWriteAction)
{
    switch (getSelector())
    {
    case 0:
        _out.writeBool(m_objectChoice.get<bool>());
        break;
    case 1:
    case 2:
        _out.writeBits(m_objectChoice.get<uint16_t>(), UINT8_C(16));
        break;
    default:
        _out.writeBits64(m_objectChoice.get<uint64_t>(), UINT8_C(64));
        break;
    }
}

