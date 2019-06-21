/**
 * Automatically generated by Zserio C++ extension version 1.2.0.
 */

#ifndef STRING_H
#define STRING_H

#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/BitFieldUtil.h>
#include <zserio/CppRuntimeException.h>
#include <zserio/StringConvertUtil.h>
#include <zserio/PreWriteAction.h>
#include <string>


class String
{
public:
    String();
    explicit String(zserio::BitStreamReader& in);

    // new in cpp11
    template <typename ZSERIO_T_str>
    explicit String(ZSERIO_T_str&& str_)
    :   m_str_(std::forward<ZSERIO_T_str>(str_))
    {}

    std::string& getStr();
    const std::string& getStr() const;
    void setStr(const std::string& str_);
    void setStr(std::string&& str_);

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t initializeOffsets(size_t bitPosition);

    bool operator==(const String& other) const;
    int hashCode() const;

    void read(zserio::BitStreamReader& in);
    void write(zserio::BitStreamWriter& out,
            zserio::PreWriteAction preWriteAction = zserio::ALL_PRE_WRITE_ACTIONS);

private:
    std::string m_str_;
};


#endif // STRING_H
