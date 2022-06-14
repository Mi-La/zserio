#ifndef ZSERIO_ZSERIO_TREE_CREATOR_H_INC
#define ZSERIO_ZSERIO_TREE_CREATOR_H_INC

#include "zserio/IReflectable.h"
#include "zserio/ITypeInfo.h"
#include "zserio/TypeInfoUtil.h"
#include "zserio/CppRuntimeException.h"

namespace zserio
{

namespace detail
{

template <typename T, typename U, typename ALLOC,
        typename std::enable_if<std::is_arithmetic<typename std::decay<U>::type>::value, int>::type = 0>
AnyHolder<ALLOC> makeAnyArithmeticValue(U value, const ALLOC& allocator)
{
    return AnyHolder<ALLOC>(static_cast<T>(value), allocator);
}

template <typename T, typename U, typename ALLOC,
        typename std::enable_if<!std::is_arithmetic<typename std::decay<U>::type>::value, int>::type = 0>
AnyHolder<ALLOC> makeAnyArithmeticValue(const U&, const ALLOC&)
{
    throw CppRuntimeException("ZserioTreeCreator: Trying to make integral any value from non-integral type!");
}

template <typename ALLOC>
AnyHolder<ALLOC> makeAnyStringValue(const string<ALLOC>& value, const ALLOC& allocator)
{
    return AnyHolder<ALLOC>(value, allocator);
}

template <typename ALLOC>
AnyHolder<ALLOC> makeAnyStringValue(string<ALLOC>&& value, const ALLOC& allocator)
{
    return AnyHolder<ALLOC>(std::move(value), allocator);
}

template <typename ALLOC>
AnyHolder<ALLOC> makeAnyStringValue(StringView value, const ALLOC& allocator)
{
    return AnyHolder<ALLOC>(stringViewToString(value, allocator), allocator);
}

template <typename ALLOC>
AnyHolder<ALLOC> makeAnyStringValue(const char* value, const ALLOC& allocator)
{
    return makeAnyStringValue(StringView(value), allocator);
}

template <typename T, typename ALLOC>
AnyHolder<ALLOC> makeAnyStringValue(const T&, const ALLOC&)
{
    throw CppRuntimeException("ZserioTreeCreator: Trying to make any string value from unsupported type!");
}

template <typename T, typename ALLOC>
AnyHolder<ALLOC> makeAnyValue(const IBasicTypeInfo<ALLOC>& typeInfo, T&& value, const ALLOC& allocator)
{
    switch (typeInfo.getCppType())
    {
    case CppType::BOOL:
        return makeAnyArithmeticValue<bool>(std::forward<T>(value), allocator);
    case CppType::UINT8:
        return makeAnyArithmeticValue<uint8_t>(std::forward<T>(value), allocator);
    case CppType::UINT16:
        return makeAnyArithmeticValue<uint16_t>(std::forward<T>(value), allocator);
    case CppType::UINT32:
        return makeAnyArithmeticValue<uint32_t>(std::forward<T>(value), allocator);
    case CppType::UINT64:
        return makeAnyArithmeticValue<uint64_t>(std::forward<T>(value), allocator);
    case CppType::INT8:
        return makeAnyArithmeticValue<int8_t>(std::forward<T>(value), allocator);
    case CppType::INT16:
        return makeAnyArithmeticValue<int16_t>(std::forward<T>(value), allocator);
    case CppType::INT32:
        return makeAnyArithmeticValue<int32_t>(std::forward<T>(value), allocator);
    case CppType::INT64:
        return makeAnyArithmeticValue<int64_t>(std::forward<T>(value), allocator);
    case CppType::FLOAT:
        return makeAnyArithmeticValue<float>(std::forward<T>(value), allocator);
    case CppType::DOUBLE:
        return makeAnyArithmeticValue<double>(std::forward<T>(value), allocator);
    case CppType::STRING:
        return makeAnyStringValue(std::forward<T>(value), allocator);
    default:
        return AnyHolder<ALLOC>(std::forward<T>(value), allocator);
    }
}

} // namespace detail

/**
 * Allows to build zserio object tree defined by the given type info.
 */
template <typename ALLOC>
class BasicZserioTreeCreator
{
public:
    /**
     * Constructor.
     *
     * \param typeInfo Type info defining the tree.
     */
    explicit BasicZserioTreeCreator(const IBasicTypeInfo<ALLOC>& typeInfo, const ALLOC& allocator = ALLOC());

    /**
     * Creates the top level compound element and move to state of building its children.
     */
    void beginRoot();

    /**
     * Finishes building and returns the created tree.
     *
     * \return Zserio object tree.
     *
     * \throw CppRuntimeException When the creator is not in state of building the root object.
     */
    IBasicReflectablePtr<ALLOC> endRoot();

    /**
     * Creates an array field within the current compound.
     *
     * \param name Name of the array field.
     *
     * \throw CppRuntimeException When the field doesn't exist or when the creator is not in a compound.
     */
    void beginArray(const std::string& name);

    /**
     * Finishes the array field.
     *
     * \throw CppRuntimeException When the creator is not in an array field.
     */
    void endArray();

    /**
     * Creates a compound field within the current compound.
     *
     * \param name Name of the compound field.
     *
     * \throw CppRuntimeException When the field doesn't exist or when the creator is not in a compound.
     */
    void beginCompound(const std::string& name);

    /**
     * Finishes the compound.
     *
     * \throw CppRuntimeException When the creator is not in a compound.
     */
    void endCompound();

    /**
     * Sets field value within the current compound.
     *
     * \param name Name of the field.
     * \param value Value to set.
     *
     * \throw CppRuntimeException When the field doesn't exist or when the creator is not in a compound.
     */
    template <typename T>
    void setValue(const std::string& name, T&& value);

    /**
     * Creates compound array element within the current array.
     *
     * \throw CppRuntimeException When the creator is not in an array of compounds.
     */
    void beginCompoundElement();

    /**
     * Finishes the compound element.
     *
     * \throw CppRuntimeException When the creator is not in a compound element.
     */
    void endCompoundElement();

    /**
     * Adds the value to the array.
     *
     * \param value Value to add.
     *
     * \throw CppRuntimeException When the creator is not in an array of simple values.
     */
    template <typename T>
    void addValueElement(T&& value);

private:
    enum class State : uint8_t
    {
        BEFORE_ROOT,
        IN_COMPOUND,
        IN_ARRAY
    };

    const IBasicTypeInfo<ALLOC>& getTypeInfo() const;
    const BasicFieldInfo<ALLOC>& findFieldInfo(const IBasicTypeInfo<ALLOC>& typeInfo, StringView name) const;

    template <typename T>
    AnyHolder<ALLOC> makeAnyValue(const IBasicTypeInfo<ALLOC>& typeInfo, T&& value) const;

    const char* state()
    {
        switch (m_state)
        {
        case State::BEFORE_ROOT:
            return "BEFORE_ROOT";
        case State::IN_COMPOUND:
            return "IN_COMPOUND";
        default: // State::IN_ARRAY:
            return "IN_ARRAY";
        }
    }

    const IBasicTypeInfo<ALLOC>& m_typeInfo;
    ALLOC m_allocator;
    std::vector<std::reference_wrapper<const BasicFieldInfo<ALLOC>>> m_fieldInfoStack;
    std::vector<IBasicReflectablePtr<ALLOC>> m_valueStack;
    State m_state = State::BEFORE_ROOT;
};

/** Typedef provided for convenience - using default std::allocator<uint8_t>. */
using ZserioTreeCreator = BasicZserioTreeCreator<std::allocator<std::uint8_t>>;

template <typename ALLOC>
BasicZserioTreeCreator<ALLOC>::BasicZserioTreeCreator(const IBasicTypeInfo<ALLOC>& typeInfo,
        const ALLOC& allocator) :
        m_typeInfo(typeInfo), m_allocator(allocator)
{}

template <typename ALLOC>
void BasicZserioTreeCreator<ALLOC>::beginRoot()
{
    if (m_state != State::BEFORE_ROOT)
        throw CppRuntimeException("ZserioTreeCreator: Cannot begin root in state '") + state() + "'!";

    m_valueStack.push_back(m_typeInfo.createInstance(m_allocator));
    m_state = State::IN_COMPOUND;
}

template <typename ALLOC>
IBasicReflectablePtr<ALLOC> BasicZserioTreeCreator<ALLOC>::endRoot()
{
    if (m_state != State::IN_COMPOUND || m_valueStack.size() != 1)
        throw CppRuntimeException("ZserioTreeCreator: Cannot end root in state '") + state() + "'!";

    m_state = State::BEFORE_ROOT;
    auto value = m_valueStack.back();
    m_valueStack.pop_back();
    return value;
}

template <typename ALLOC>
void BasicZserioTreeCreator<ALLOC>::beginArray(const std::string& name)
{
    if (m_state != State::IN_COMPOUND)
        throw CppRuntimeException("ZserioTreeCreator: Cannot begin array in state '") + state() + "'!";

    const auto& parentTypeInfo = getTypeInfo();
    const auto& fieldInfo = findFieldInfo(parentTypeInfo, name);
    if (!fieldInfo.isArray)
        throw CppRuntimeException("ZserioTreeCreator: Member '") + fieldInfo.schemaName + "' is not an array!";

    m_fieldInfoStack.push_back(fieldInfo);
    if (TypeInfoUtil::hasChoice(parentTypeInfo.getCppType()) || fieldInfo.isOptional)
    {
        // optional field, or field within choice or union -> create the new compound
        m_valueStack.push_back(m_valueStack.back()->createField(name));
    }
    else
    {
        m_valueStack.push_back(m_valueStack.back()->getField(name));
    }

    m_state = State::IN_ARRAY;
}

template <typename ALLOC>
void BasicZserioTreeCreator<ALLOC>::endArray()
{
    if (m_state != State::IN_ARRAY)
        throw CppRuntimeException("ZserioTreeCreator: Cannot end array in state '") + state() + "'!";

    m_fieldInfoStack.pop_back();
    m_valueStack.pop_back();
    m_state = State::IN_COMPOUND;
}

template <typename ALLOC>
void BasicZserioTreeCreator<ALLOC>::beginCompound(const std::string& name)
{
    if (m_state != State::IN_COMPOUND)
        throw CppRuntimeException("ZserioTreeCreator: Cannot begin compound in state '") + state() + "'!";

    const auto& parentTypeInfo = getTypeInfo();
    const auto& fieldInfo = findFieldInfo(parentTypeInfo, name);
    if (fieldInfo.isArray)
        throw CppRuntimeException("ZserioTreeCreator: Member '") + fieldInfo.schemaName + "' is an array!";

    if (!TypeInfoUtil::isCompound(fieldInfo.typeInfo.getCppType()))
        throw CppRuntimeException("ZserioTreeCreator: Member '") + fieldInfo.schemaName + "' is not a compound!";

    m_fieldInfoStack.push_back(fieldInfo);
    if (TypeInfoUtil::hasChoice(parentTypeInfo.getCppType()) || fieldInfo.isOptional)
    {
        // optional field, or field within choice or union -> create the new compound
        m_valueStack.push_back(m_valueStack.back()->createField(name));
    }
    else
    {
        m_valueStack.push_back(m_valueStack.back()->getField(name));
    }

    m_state = State::IN_COMPOUND;
}

template <typename ALLOC>
void BasicZserioTreeCreator<ALLOC>::endCompound()
{
    if (m_state != State::IN_COMPOUND || m_fieldInfoStack.empty())
    {
        throw CppRuntimeException("ZserioTreeCreator: Cannot end compound in state '") + state() +
                "'" + (m_fieldInfoStack.empty() ? ", expecting endRoot!" : "!'");
    }

    const BasicFieldInfo<ALLOC>& fieldInfo = m_fieldInfoStack.back();
    if (fieldInfo.isArray)
        throw CppRuntimeException("ZserioTreeCreator: Cannot end compound, it's an array element!");

    m_fieldInfoStack.pop_back();
    m_valueStack.pop_back();
}

template <typename ALLOC>
template <typename T>
void BasicZserioTreeCreator<ALLOC>::setValue(const std::string& name, T&& value)
{
    // TODO[Mi-L@]: How to set null value?!

    if (m_state != State::IN_COMPOUND)
        throw CppRuntimeException("ZserioTreeCreator: Cannot set value in state '") + state() + "'!";

    const BasicFieldInfo<ALLOC>& fieldInfo = findFieldInfo(getTypeInfo(), name);
    if (fieldInfo.isArray)
    {
        throw CppRuntimeException("ZserioTreeCreator: Expecting array in member '") +
                fieldInfo.schemaName + "'!";
    }

    m_valueStack.back()->setField(fieldInfo.schemaName,
            makeAnyValue(fieldInfo.typeInfo, std::forward<T>(value)));
}

template <typename ALLOC>
void BasicZserioTreeCreator<ALLOC>::beginCompoundElement()
{
    if (m_state != State::IN_ARRAY)
    {
        throw CppRuntimeException("ZserioTreeCreator: Cannot begin compound element in state '") +
                state() + "'!";
    }

    const BasicFieldInfo<ALLOC>& fieldInfo = m_fieldInfoStack.back();
    if (!TypeInfoUtil::isCompound(fieldInfo.typeInfo.getCppType()))
    {
        throw CppRuntimeException("ZserioTreeCreator: Member '") + fieldInfo.schemaName +
                "' is not a compound!";
    }

    auto compoundArray = m_valueStack.back();
    compoundArray->resize(compoundArray->size() + 1);
    m_valueStack.push_back(compoundArray->at(compoundArray->size() - 1));
    m_state = State::IN_COMPOUND;
}

template <typename ALLOC>
void BasicZserioTreeCreator<ALLOC>::endCompoundElement()
{
    if (m_state != State::IN_COMPOUND || m_fieldInfoStack.empty())
    {
        throw CppRuntimeException("ZserioTreeCreator: Cannot end compound element in state '") +
                state() + (m_fieldInfoStack.empty() ? ", expecting endRoot!" : "'!");
    }

    const BasicFieldInfo<ALLOC>& fieldInfo = m_fieldInfoStack.back();
    if (!fieldInfo.isArray)
        throw CppRuntimeException("ZserioTreeCreator: Cannot end compound element, not in array!");

    m_valueStack.pop_back();
    m_state = State::IN_ARRAY;
}

template <typename ALLOC>
template <typename T>
void BasicZserioTreeCreator<ALLOC>::addValueElement(T&& value)
{
    if (m_state != State::IN_ARRAY)
        throw CppRuntimeException("ZserioTreeCreator: Cannot add value element in state '") + state() + "'!";

    const BasicFieldInfo<ALLOC>& fieldInfo = m_fieldInfoStack.back();
    m_valueStack.back()->append(makeAnyValue(fieldInfo.typeInfo, std::forward<T>(value)));
}

template <typename ALLOC>
const IBasicTypeInfo<ALLOC>& BasicZserioTreeCreator<ALLOC>::getTypeInfo() const
{
    return m_fieldInfoStack.empty() ? m_typeInfo : m_fieldInfoStack.back().get().typeInfo;
}

template <typename ALLOC>
const BasicFieldInfo<ALLOC>& BasicZserioTreeCreator<ALLOC>::findFieldInfo(
        const IBasicTypeInfo<ALLOC>& typeInfo, StringView name) const
{
    Span<const BasicFieldInfo<ALLOC>> fields = typeInfo.getFields();
    auto found_it = find_if(fields.begin(), fields.end(),
            [name](const BasicFieldInfo<ALLOC>& field){ return field.schemaName == name; });
    if (found_it == fields.end())
    {
        throw CppRuntimeException("ZserioTreeCreator: Member '") + name +  "' not found in '" +
                typeInfo.getSchemaName() + "'!";
    }

    return *found_it;
}

template <typename ALLOC>
template <typename T>
AnyHolder<ALLOC> BasicZserioTreeCreator<ALLOC>::makeAnyValue(
        const IBasicTypeInfo<ALLOC>& typeInfo, T&& value) const
{
    return detail::makeAnyValue(typeInfo, std::forward<T>(value), m_allocator);
}

} // namespace zserio

#endif // ZSERIO_ZSERIO_TREE_CREATOR_H_INC
