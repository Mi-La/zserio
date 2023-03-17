#ifndef ZSERIO_CPP_RUNTIME_EXCEPTION_H_INC
#define ZSERIO_CPP_RUNTIME_EXCEPTION_H_INC

#include <type_traits>
#include <exception>
#include <string>
#include <vector>

#include "zserio/StringConvertUtil.h"
#include "zserio/Traits.h"

namespace zserio
{

/**
 * Exception thrown when an error within the Zserio C++ runtime library occurs.
 */
class CppRuntimeException : public std::exception
{
public:
    /**
     * Constructor.
     *
     * \param message Description of the error.
     */
    explicit CppRuntimeException(const char* message = "");

    /**
     * Method generated by default.
     * \{
     */
    ~CppRuntimeException() override = default;

    CppRuntimeException(const CppRuntimeException& other) = default;
    CppRuntimeException& operator=(const CppRuntimeException& other) = default;

    CppRuntimeException(CppRuntimeException&& other) = default;
    CppRuntimeException& operator=(CppRuntimeException&& other) = default;
    /**
     * \}
     */

    const char* what() const noexcept override;

    /**
     * Appends a message to the description.
     *
     * \param message Description of the error to append.
     */
    void append(const char* message);

    /**
     * Appends a message of a known length to the description.
     *
     * \param message Description of the error to append.
     * \param messageLen Length of the message.
     */
    void append(const char* message, size_t messageLen);

private:
    void appendImpl(const char* message, size_t numCharsToAppend);

    // Note: If you move this to public section, old MSVC 2015 compiler will fail with internal compiler error!
    static constexpr size_t BUFFER_SIZE = 512;

    char m_buffer[BUFFER_SIZE]; // note that fixed sized array is deeply copied on copy operations and its OK
    size_t m_len = 0;
};

/**
 * Appends a message to the exception's description.
 *
 * \param exception Exception to modify.
 * \param message Description of the error to append.
 *
 * \return Reference to the exception to allow operator chaining.
 */
CppRuntimeException& operator<<(CppRuntimeException& exception, const char* message);

/**
 * Appends a bool value to the exception's description.
 *
 * \param exception Exception to modify.
 * \param value Bool value to append.
 *
 * \return Reference to the exception to allow operator chaining.
 */
CppRuntimeException& operator<<(CppRuntimeException& exception, bool value);

/**
 * Appends a float value to the exception's description.
 *
 * \param exception Exception to modify.
 * \param value Float value to append.
 *
 * \return Reference to the exception to allow operator chaining.
 */
CppRuntimeException& operator<<(CppRuntimeException& exception, float value);

/**
 * Appends a double value to the exception's description.
 *
 * \param exception Exception to modify.
 * \param value Double value to append.
 *
 * \return Reference to the exception to allow operator chaining.
 */
CppRuntimeException& operator<<(CppRuntimeException& exception, double value);

/**
 * Appends an integral value to the exception's description.
 *
 * \param exception Exception to modify.
 * \param value Integral value to append.
 *
 * \return Reference to the exception to allow operator chaining.
 */
template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
CppRuntimeException& operator<<(CppRuntimeException& exception, T value)
{
    char buffer[24];
    const char* stringValue = convertIntToString(buffer, value);
    return exception << stringValue;
}

/**
 * Appends any object which implement getValue() method (e.g. bitmask) to the exception's description.
 *
 * \param exception Exception to modify.
 * \param value Object with getValue() method to append.
 *
 * \return Reference to the exception to allow operator chaining.
 */
template <typename T, typename std::enable_if<is_bitmask<T>::value, int>::type = 0>
CppRuntimeException& operator<<(CppRuntimeException& exception, T value)
{
    exception << value.getValue();
    return exception;
}

/**
 * Appends a string value to the exception's description.
 *
 * \param exception Exception to modify.
 * \param value String value to append.
 *
 * \return Reference to the exception to allow operator chaining.
 */
template <typename ALLOC>
CppRuntimeException& operator<<(CppRuntimeException& exception,
        const std::basic_string<char, std::char_traits<char>, ALLOC>& value)
{
    exception.append(value.c_str(), value.size());
    return exception;
}

/**
 * Appends a vector value to the exception's description.
 *
 * \param exception Exception to modify.
 * \param value Vector value to append.
 *
 * \return Reference to the exception to allow operator chaining.
 */
template <typename T, typename ALLOC>
CppRuntimeException& operator<<(CppRuntimeException& exception, const std::vector<T, ALLOC>& value)
{
    return exception << "vector([...], " << value.size() << ")";
}

namespace detail
{

// inspired by C++ ostreams - see https://cplusplus.github.io/LWG/issue1203
template <typename EXCEPTION, typename VALUE,
        typename = typename std::enable_if<std::is_base_of<CppRuntimeException, EXCEPTION>::value, int>::type,
        typename = decltype(std::declval<EXCEPTION&>() << std::declval<const VALUE&>())>
using CppRuntimeExceptionRValueInsertion = EXCEPTION&&;

} // namespace detail

/**
 * Appends any value for which operator<< is implemented to the exception's description.
 *
 * Overload for rvalue to enable operator<< on a temporary object, .e.g. CppRuntimeException() << "value".
 * Moreover note that this overload preserves the concrete type of the exception!
 *
 * \param exception Exception to modify.
 * \param value Value to append.
 *
 * \return R-value reference to the original exception to allow operator chaining.
 */
template <typename CPP_RUNTIME_EXCEPTION, typename T>
detail::CppRuntimeExceptionRValueInsertion<CPP_RUNTIME_EXCEPTION, T>
operator<<(CPP_RUNTIME_EXCEPTION&& exception, const T& value)
{
    exception << value;
    return std::move(exception);
}

} // namespace zserio

#endif // ifndef ZSERIO_CPP_RUNTIME_EXCEPTION_H_INC
