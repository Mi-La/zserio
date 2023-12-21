#ifndef ZSERIO_STRING_VIEW_H_INC
#define ZSERIO_STRING_VIEW_H_INC

#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <utility>

#include "zserio/CppRuntimeException.h"
#include "zserio/RebindAlloc.h"
#include "zserio/String.h"
#include "zserio/StringConvertUtil.h"

namespace zserio
{

/**
 * Non-owning constant view to a string. The user of this class is responsible of making sure, that the
 * referenced string is valid as long as the view is alive. Inspired by C++17 std::basic_string_view.
 */
template <typename CharT, typename Traits = std::char_traits<CharT>>
class BasicStringView
{
public:
    using traits_type = Traits;
    using value_type = CharT;
    using pointer = CharT*;
    using const_pointer = const CharT*;
    using reference = CharT&;
    using const_reference = const CharT&;
    using const_iterator = const_pointer;
    using iterator = const_iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = const_reverse_iterator;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    /**
     * Constant used to indicate end of view or "not a position", depending on context.
     */
    static constexpr const size_type npos = static_cast<size_type>(-1);

    /**
     * Constructor. Initializes empty view.
     */
    constexpr BasicStringView() noexcept = default;

    /**
     * Constructor. Initializes string view to given null-terminated string.
     *
     * \param str Input null-terminated string.
     */
    BasicStringView(const const_pointer str) noexcept :
            m_data(str),
            m_size(Traits::length(str))
    {}

    /**
     * Constructor. Initializes string view to given string with given length.
     *
     * \param str Input string.
     * \param count Length of the view. Shall not be longer than the input string.
     */
    constexpr BasicStringView(const const_pointer str, const size_type count) noexcept :
            m_data(str),
            m_size(count)
    {}

    /**
     * Constructor. Initializes string view to given std::basic_string
     *
     * \param str Input string.
     */
    template <typename ALLOC>
    constexpr BasicStringView(const std::basic_string<CharT, Traits, ALLOC>& str) noexcept :
            m_data(str.data()),
            m_size(str.size())
    {}

    /**
     * Method generated by default.
     * \{
     */
    ~BasicStringView() = default;

    BasicStringView(const BasicStringView&) noexcept = default;
    BasicStringView& operator=(const BasicStringView&) noexcept = default;

    BasicStringView(BasicStringView&&) noexcept = default;
    BasicStringView& operator=(BasicStringView&&) noexcept = default;
    /**
     * \}
     */

    /**
     * Begin iteration.
     *
     * \return Iterator to the beginning of the referenced string.
     */
    constexpr const_iterator begin() const noexcept
    {
        return m_data;
    }

    /**
     * Begin iteration.
     *
     * \return Iterator to the beginning of the referenced string.
     */
    constexpr const_iterator cbegin() const noexcept
    {
        return begin();
    }

    /**
     * End iteration.
     *
     * \return Iterator one-past-end of the referenced string.
     */
    constexpr const_iterator end() const noexcept
    {
        return m_data + m_size;
    }

    /**
     * End iteration.
     *
     * \return Iterator one-past-end of the referenced string.
     */
    constexpr const_iterator cend() const noexcept
    {
        return end();
    }

    /**
     * Begin reverse iteration.
     *
     * \return Reverse iterator to the end of the referenced string.
     */
    constexpr const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    /**
     * Begin reverse iteration.
     *
     * \return Reverse iterator to the end of the referenced string.
     */
    constexpr const_reverse_iterator crbegin() const noexcept
    {
        return rbegin();
    }

    /**
     * End reverse iteration.
     *
     * \return Reverse iterator one-before-beginning of the referenced string.
     */
    constexpr const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    /**
     * End reverse iteration.
     *
     * \return Reverse iterator one-before-beginning of the referenced string.
     */
    constexpr const_reverse_iterator crend() const noexcept
    {
        return rend();
    }

    /**
     * Element access operator. Returns reference to the element of the referenced string at given index.
     *
     * \param pos Index of the element to access. Shall be less than size().
     * \return Reference to the string element at given index.
     */
    constexpr const_reference operator[](const size_type pos) const noexcept
    {
        return m_data[pos];
    }

    /**
     * Element access operator. Returns reference to the element of the referenced string at given index.
     *
     * \param pos Index of the element to access.
     * \return Reference to the string element at given index.
     *
     * \throw CppRuntimeException if pos is not less than size().
     */
    const_reference at(const size_type pos) const
    {
        if (pos >= size())
        {
            throw CppRuntimeException("StringView: Position ")
                    << pos << " out of range for view size " << size() << "!";
        }
        return m_data[pos];
    }

    /**
     * Get reference to the first element of the string. The string shall not be empty.
     *
     * \return Reference to the first element of the string.
     */
    constexpr const_reference front() const noexcept
    {
        return m_data[0];
    }

    /**
     * Get reference to the last element of the string. The string shall not be empty.
     *
     * \return Reference to the last element of the string.
     */
    constexpr const_reference back() const noexcept
    {
        return m_data[m_size - 1];
    }

    /**
     * Get pointer to the beginning of the referenced string.
     *
     * \return Pointer to the beginning of the referenced string.
     */
    constexpr const_pointer data() const noexcept
    {
        return m_data;
    }

    /**
     * Get referenced string length.
     *
     * \return The string length.
     */
    constexpr size_type size() const noexcept
    {
        return m_size;
    }

    /**
     * Get referenced string length.
     *
     * \return The string length.
     */
    constexpr size_type length() const noexcept
    {
        return size();
    }

    /**
     * Get max. allowed string length.
     *
     * \return Max. allowed string length.
     */
    constexpr size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max();
    }

    /**
     * Check if the string is empty.
     *
     * \return True if the string is empty, false otherwise.
     */
    constexpr bool empty() const noexcept
    {
        return size() == 0;
    }

    /**
     * Modify the string view so that it skips specified amount of elements at the beginning.
     *
     * \param n Number of elements to skip. Shall not be greater than size().
     */
    void remove_prefix(size_type n)
    {
        m_data += n;
        m_size -= n;
    }

    /**
     * Modify the string view so that it skips specified amount of elements at the end.
     *
     * \param n Number of elements to skip. Shall not be greater than size().
     */
    void remove_suffix(size_type n)
    {
        m_size -= n;
    }

    /**
     * Swap the content with another string view.
     *
     * \param other Another string view
     */
    void swap(BasicStringView& other) noexcept
    {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
    }

    /**
     * Copy the specified amount of elements from the string view to given buffer.
     *
     * \param dest Buffer where the substring should be copied.
     * \param count Number of elements to copy.
     * \param pos Offset in the string view, where the copy should begin.
     * \return Number of elements actually copied.
     *
     * \throw CppRuntimeException if pos is > size().
     */
    size_type copy(CharT* dest, size_type count, size_type pos = 0) const
    {
        if (pos > size())
        {
            throw CppRuntimeException("StringView: Position ")
                    << pos << " out of range for view size " << size() << "!";
        }
        const size_t rcount = std::min(count, size() - pos);
        Traits::copy(dest, data() + pos, rcount);
        return rcount;
    }

    /**
     * Calculate string sub-view.
     *
     * \param pos Position in this view, where the sub-view should start.
     * \param count Number of element in the sub-view.
     * \return Calculated sub-view.
     *
     * \throw CppRuntimeException if pos is > size().
     */
    BasicStringView substr(size_type pos = 0, size_type count = npos) const
    {
        if (pos > size())
        {
            throw CppRuntimeException("StringView: Position ")
                    << pos << " out of range for view size " << size() << "!";
        }
        const size_t rcount = std::min(count, size() - pos);
        return BasicStringView(m_data + pos, rcount);
    }

    /**
     * Compare this string view to other.
     *
     * \param other Second string view.
     * \return <0, if this view is considered less than the other, ==0, if both views are same,
     * >0, if this view is considered greater than the other.
     */
    int compare(BasicStringView other) const noexcept
    {
        const size_type rlen = std::min(size(), other.size());
        const int cmp = Traits::compare(data(), other.data(), rlen);

        if (cmp != 0)
            return cmp;

        if (size() < other.size())
            return -1;
        else if (size() > other.size())
            return 1;
        else
            return 0;
    }

    /**
     * Compare this string view to other.
     *
     * \param pos1 Start position in this view.
     * \param count1 Number of elements in the view.
     * \param other Second string view.
     * \return <0, if this view is considered less than the other, ==0, if both views are same,
     * >0, if this view is considered greater than the other.
     */
    int compare(size_type pos1, size_type count1, BasicStringView other) const
    {
        return substr(pos1, count1).compare(other);
    }

    /**
     * Compare this string view to other.
     *
     * \param pos1 Start position in this view.
     * \param count1 Number of elements in the view.
     * \param other Second string view.
     * \param pos2 Start position in the other view.
     * \param count2 Number of element in the other view.
     * \return <0, if this view is considered less than the other, ==0, if both views are same,
     * >0, if this view is considered greater than the other.
     */
    int compare(size_type pos1, size_type count1, BasicStringView other, size_type pos2, size_type count2) const
    {
        return substr(pos1, count1).compare(other.substr(pos2, count2));
    }

    /**
     * Compare this string view to other.
     *
     * \param str String to compare with.
     * \return <0, if this view is considered less than the other, ==0, if both views are same,
     * >0, if this view is considered greater than the other.
     */
    int compare(const CharT* str) const
    {
        return compare(BasicStringView(str));
    }

    /**
     * Compare this string view to other.
     *
     * \param pos1 Start position in this view.
     * \param count1 Number of elements in the view.
     * \param str String to compare with.
     * \return <0, if this view is considered less than the other, ==0, if both views are same,
     * >0, if this view is considered greater than the other.
     */
    int compare(size_type pos1, size_type count1, const CharT* str) const
    {
        return substr(pos1, count1).compare(BasicStringView(str));
    }

    /**
     * Compare this string view to other.
     *
     * \param pos1 Start position in this view.
     * \param count1 Number of elements in the view.
     * \param str String to compare with.
     * \param count2 Number of element in the str.
     * \return <0, if this view is considered less than the other, ==0, if both views are same,
     * >0, if this view is considered greater than the other.
     */
    int compare(size_type pos1, size_type count1, const CharT* str, size_type count2) const
    {
        return substr(pos1, count1).compare(BasicStringView(str, count2));
    }

    /**
     * Find position of given string view in this string view.
     *
     * \param str String to search.
     * \param pos Position where the start the search.
     * \return Index of the found string or npos if the string was not found.
     */
    size_type find(BasicStringView str, size_type pos = 0) const noexcept
    {
        if (pos >= size() || str.size() > size() - pos)
            return npos; // the string cannot be there

        if (str.size() == 0)
            return pos; // zero-sized search, this defaults to the match at the beginning

        const const_pointer startPtr = data() + pos; // where the searching will start
        const const_pointer endPtr = data() + (size() - str.size()) + 1; // where the searching will end

        // initial position
        const_pointer ptr = Traits::find(startPtr, static_cast<size_t>(endPtr - startPtr), str[0]);
        while (ptr)
        {
            // check if the searched string is present
            if (Traits::compare(ptr, str.data(), str.size()) == 0)
            {
                return static_cast<size_t>(ptr - data());
            }

            // go to next position
            ptr = Traits::find(ptr + 1, static_cast<size_t>(endPtr - ptr - 1), str[0]);
        }

        return npos;
    }

    /**
     * Find position of given char in this string view.
     *
     * \param ch Char to search.
     * \param pos Position where the start the search.
     * \return Index of the found char or npos if the string was not found.
     */
    size_type find(CharT ch, size_type pos = 0) const noexcept
    {
        return find(BasicStringView(std::addressof(ch), 1), pos);
    }

    /**
     * Find position of given string in this string view.
     *
     * \param str String to search.
     * \param pos Position where the start the search.
     * \param count Length of str.
     * \return Index of the found string or npos if the string was not found.
     */
    size_type find(const CharT* str, size_type pos, size_type count) const
    {
        return find(BasicStringView(str, count), pos);
    }

    /**
     * Find position of given null-terminated string in this string view.
     *
     * \param str String to search.
     * \param pos Position where the start the search.
     * \return Index of the found string or npos if the string was not found.
     */
    size_type find(const CharT* str, size_type pos = 0) const
    {
        return find(BasicStringView(str), pos);
    }

    /**
     * Find position of given string view in this string view, starting from the view end.
     *
     * \param str String to search.
     * \param pos Position where the start the search.
     * \return Index of the found string or npos if the string was not found.
     */
    size_type rfind(BasicStringView str, size_type pos = npos) const noexcept
    {
        if (str.size() > size())
            return npos;

        for (size_t p = std::min(static_cast<size_type>(size() - str.size()), pos) + 1; p > 0; --p)
        {
            if (Traits::compare(data() + p - 1, str.data(), str.size()) == 0)
                return p - 1;
        }

        return npos;
    }

    /**
     * Find position of given char in this string view, starting from the view end.
     *
     * \param ch Char to search.
     * \param pos Position where the start the search.
     * \return Index of the found char or npos if the string was not found.
     */
    size_type rfind(CharT ch, size_type pos = npos) const noexcept
    {
        return rfind(BasicStringView(std::addressof(ch), 1), pos);
    }

    /**
     * Find position of given null-terminated string in this string view, starting from the view end.
     *
     * \param str String to search.
     * \param pos Position where the start the search.
     * \return Index of the found string or npos if the string was not found.
     */
    size_type rfind(const CharT* str, size_type pos, size_type count) const
    {
        return rfind(BasicStringView(str, count), pos);
    }

    /**
     * Find position of given null-terminated string in this string view, starting from the view end.
     *
     * \param str String to search.
     * \param pos Position where the start the search.
     * \return Index of the found string or npos if the string was not found.
     */
    size_type rfind(const CharT* str, size_type pos = npos) const
    {
        return rfind(BasicStringView(str), pos);
    }

    /**
     * Find the position of the first character equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_first_of(BasicStringView str, size_type pos = 0) const noexcept
    {
        if (str.size() == 0 || pos >= size())
            return npos;

        for (size_type idx = pos; idx < size(); ++idx)
        {
            if (Traits::find(str.data(), str.size(), data()[idx]) != nullptr)
                return idx;
        }

        return npos;
    }

    /**
     * Find the position of the first character equal to the given character.
     *
     * \param ch Character to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_first_of(CharT ch, size_type pos = 0) const noexcept
    {
        return find_first_of(BasicStringView(std::addressof(ch), 1), pos);
    }

    /**
     * Find the position of the first character equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \param count Number of character in str.
     * \return Found position or npos if no such character was found.
     */
    size_type find_first_of(const CharT* str, size_type pos, size_type count) const
    {
        return find_first_of(BasicStringView(str, count), pos);
    }

    /**
     * Find the position of the first character equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_first_of(const CharT* str, size_type pos = 0) const
    {
        return find_first_of(BasicStringView(str), pos);
    }

    /**
     * Find the last character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_last_of(BasicStringView str, size_type pos = npos) const noexcept
    {
        if (str.empty() || empty())
            return npos;

        for (size_type idx = std::min(pos + 1, size()); idx > 0; --idx)
        {
            if (Traits::find(str.data(), str.size(), data()[idx - 1]) != nullptr)
                return idx - 1;
        }

        return npos;
    }

    /**
     * Find the last character not equal to the given character.
     *
     * \param ch Character to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_last_of(CharT ch, size_type pos = npos) const noexcept
    {
        return find_last_of(BasicStringView(std::addressof(ch), 1), pos);
    }

    /**
     * Find the last character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \param count Number of characters in str.
     * \return Found position or npos if no such character was found.
     */
    size_type find_last_of(const CharT* str, size_type pos, size_type count) const
    {
        return find_last_of(BasicStringView(str, count), pos);
    }

    /**
     * Find the last character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_last_of(const CharT* str, size_type pos = npos) const
    {
        return find_last_of(BasicStringView(str), pos);
    }

    /**
     * Finds the first character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_first_not_of(BasicStringView str, size_type pos = 0) const noexcept
    {
        if (str.size() == 0 || pos >= size())
            return npos;

        for (size_type idx = pos; idx < size(); ++idx)
        {
            if (Traits::find(str.data(), str.size(), data()[idx]) == nullptr)
                return idx;
        }

        return npos;
    }

    /**
     * Finds the first character not equal to the given character.
     *
     * \param ch Character to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_first_not_of(CharT ch, size_type pos = 0) const noexcept
    {
        return find_first_not_of(BasicStringView(std::addressof(ch), 1), pos);
    }

    /**
     * Finds the first character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \param count Number of characters in str.
     * \return Found position or npos if no such character was found.
     */
    size_type find_first_not_of(const CharT* str, size_type pos, size_type count) const
    {
        return find_first_not_of(BasicStringView(str, count), pos);
    }

    /**
     * Finds the first character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_first_not_of(const CharT* str, size_type pos = 0) const
    {
        return find_first_not_of(BasicStringView(str), pos);
    }

    /**
     * Find the last character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_last_not_of(BasicStringView str, size_type pos = npos) const noexcept
    {
        if (str.empty() || empty())
            return npos;

        for (size_type idx = std::min(pos + 1, size()); idx > 0; --idx)
        {
            if (Traits::find(str.data(), str.size(), data()[idx - 1]) == nullptr)
                return idx - 1;
        }

        return npos;
    }

    /**
     * Find the last character not equal to the given character.
     *
     * \param ch Character to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_last_not_of(CharT ch, size_type pos = npos) const noexcept
    {
        return find_last_not_of(BasicStringView(std::addressof(ch), 1), pos);
    }

    /**
     * Find the last character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \param count Number of characters in str.
     * \return Found position or npos if no such character was found.
     */
    size_type find_last_not_of(const CharT* str, size_type pos, size_type count) const
    {
        return find_last_not_of(BasicStringView(str, count), pos);
    }

    /**
     * Find the last character not equal to any of the characters in the given character sequence.
     *
     * \param str Sequence to search.
     * \param pos Position where to start the search.
     * \return Found position or npos if no such character was found.
     */
    size_type find_last_not_of(const CharT* str, size_type pos = npos) const
    {
        return find_last_not_of(BasicStringView(str), pos);
    }

private:
    const_pointer m_data = nullptr;
    size_type m_size = 0;
};

template <typename CharT, class Traits>
constexpr std::size_t const BasicStringView<CharT, Traits>::npos;

/**
 * Comparison operator.
 *
 * \param lhs Left hand side operator.
 * \param rhs Right hand side operator.
 * \return True if lhs is equal to rhs.
 */
template <typename CharT, class Traits>
constexpr bool operator==(BasicStringView<CharT, Traits> lhs, BasicStringView<CharT, Traits> rhs) noexcept
{
    return lhs.compare(rhs) == 0;
}

/**
 * Comparison operator.
 *
 * \param lhs Left hand side operator.
 * \param rhs Right hand side operator.
 * \return True if lhs is not equal to rhs.
 */
template <typename CharT, class Traits>
constexpr bool operator!=(BasicStringView<CharT, Traits> lhs, BasicStringView<CharT, Traits> rhs) noexcept
{
    return lhs.compare(rhs) != 0;
}

/**
 * Comparison operator.
 *
 * \param lhs Left hand side operator.
 * \param rhs Right hand side operator.
 * \return True if lhs is less than rhs.
 */
template <typename CharT, class Traits>
constexpr bool operator<(BasicStringView<CharT, Traits> lhs, BasicStringView<CharT, Traits> rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}

/**
 * Comparison operator.
 *
 * \param lhs Left hand side operator.
 * \param rhs Right hand side operator.
 * \return True if lhs is less or equal to rhs.
 */
template <typename CharT, class Traits>
constexpr bool operator<=(BasicStringView<CharT, Traits> lhs, BasicStringView<CharT, Traits> rhs) noexcept
{
    return lhs.compare(rhs) <= 0;
}

/**
 * Comparison operator.
 *
 * \param lhs Left hand side operator.
 * \param rhs Right hand side operator.
 * \return True if lhs is greater than rhs.
 */
template <typename CharT, class Traits>
constexpr bool operator>(BasicStringView<CharT, Traits> lhs, BasicStringView<CharT, Traits> rhs) noexcept
{
    return lhs.compare(rhs) > 0;
}

/**
 * Comparison operator.
 *
 * \param lhs Left hand side operator.
 * \param rhs Right hand side operator.
 * \return True if lhs is greater or equal to rhs.
 */
template <typename CharT, class Traits>
constexpr bool operator>=(BasicStringView<CharT, Traits> lhs, BasicStringView<CharT, Traits> rhs) noexcept
{
    return lhs.compare(rhs) >= 0;
}

/**
 * Convenience function that initializes a string view to given array of chars.
 *
 * \param str Input string in form of array of characters.
 * \return String view to given input string.
 */
template <typename CharT, size_t N>
constexpr BasicStringView<CharT> makeStringView(const CharT (&str)[N])
{
    static_assert(N != 0, "Zero length arrays C++ extension is not supported!");
    return BasicStringView<CharT>(str, str[N - 1] == CharT() ? (N - 1) : N);
}

/**
 * Convenience function that constructs string from a string view and allocator.
 *
 * \param stringView String view to convert.
 * \param allocator Allocator to use for the string construction.
 *
 * \return String constructed from the string view and allocator.
 */
template <typename CharT, typename Traits, typename ALLOC = std::allocator<char>>
std::basic_string<CharT, Traits, RebindAlloc<ALLOC, CharT>> stringViewToString(
        BasicStringView<CharT, Traits> stringView, const ALLOC& allocator = ALLOC())
{
    return std::basic_string<CharT, Traits, RebindAlloc<ALLOC, CharT>>(
            stringView.data(), stringView.size(), allocator);
}

/**
 * Append string view to string.
 *
 * \param first String to which the second string should be appended.
 * \param second String view to append to the first.
 * \return first.
 */
template <typename CharT, typename Traits, typename ALLOC = std::allocator<char>>
std::basic_string<CharT, Traits, ALLOC>& operator+=(
        std::basic_string<CharT, Traits, ALLOC>& first, BasicStringView<CharT, Traits> second)
{
    return first.append(second.data(), second.size());
}

/**
 * Specialization of BasicStringView for char.
 */
using StringView = BasicStringView<char, std::char_traits<char>>;

/**
 * Converts a string view to string using the given allocator. Defined for convenience.
 *
 * \param value String view to convert.
 * \param allocator Allocator to use for the string allocation.
 */
template <typename ALLOC>
string<ALLOC> toString(StringView value, const ALLOC& allocator = ALLOC())
{
    return stringViewToString(value, allocator);
}

/**
 * Allows to append StringView to CppRuntimeException.
 *
 * \param exception Exception to modify.
 * \param view String view.
 *
 * \return Reference to the exception to allow operator chaining.
 */
inline CppRuntimeException& operator<<(CppRuntimeException& exception, StringView view)
{
    exception.append(view.data(), view.size());
    return exception;
}

inline namespace literals
{

/**
 * User-defined literal for StringView.
 */
constexpr ::zserio::StringView operator"" _sv(const char* str, std::size_t len) noexcept
{
    return ::zserio::StringView(str, len);
}

} // namespace literals

} // namespace zserio

#endif // ZSERIO_STRING_VIEW_H_INC
