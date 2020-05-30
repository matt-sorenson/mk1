#include <mk1/ut.h>

#ifdef _MSC_VER
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#endif
#include <utf8.h>
#ifdef _MSC_VER
#undef _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#endif

#include <mk1/utf.h>

namespace mk1 {

bool is_valid_utf8(const char* str, const size_t len)
{
    return ::utf8::is_valid(str, str + len + 1);
}


bool starts_with_utf8_bom(const char* str, const size_t len)
{
    return ::utf8::starts_with_bom(str, str + len + 1);
}


string to_utf8(const char16_t* str, const size_t len)
{
    string out;
    ::utf8::utf16to8(str, str + len + 1, std::back_inserter(out));
    return out;
}


string to_utf8(const char32_t* str, const size_t len)
{
    string out;
    ::utf8::utf32to8(str, str + len + 1, std::back_inserter(out));
    return out;
}


std::u16string to_utf16(const char* str, const size_t len)
{
    std::u16string out;
    ::utf8::utf8to16(str, str + len + 1, std::back_inserter(out));
    return out;
}


std::u16string to_utf16(const char32_t* str, const size_t len)
{
    return to_utf16(to_utf8(str, len));
}


std::u32string to_utf32(const char* str, const size_t len)
{
    std::u32string out;
    ::utf8::utf8to32(str, str + len + 1, std::back_inserter(out));
    return out;
}


std::u32string to_utf32(const char16_t* str, const size_t len)
{
    return to_utf32(to_utf8(str, len));
}

} // namespace mk1
