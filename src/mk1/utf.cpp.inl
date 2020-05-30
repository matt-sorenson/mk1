#pragma once

namespace mk1 {

inline string to_utf8(const char* str, const size_t len)
{
    return string{str, len};
}


inline std::u16string to_utf16(const char16_t* str, const size_t len)
{
    return std::u16string{str, len};
}


inline std::u32string to_utf32(const char32_t* str, const size_t len)
{
    return std::u32string{str, len};
}

bool is_valid_utf8(const char* str)
{
    return is_valid_utf8(str, std::char_traits<char>::length(str));
}


bool starts_with_utf8_bom(const char* str)
{
    return starts_with_utf8_bom(str, std::char_traits<char>::length(str));
}


bool is_valid_utf8(const string& str)
{
    return is_valid_utf8(str.data(), str.length());
}


bool starts_with_utf8_bom(const string& str)
{
    return starts_with_utf8_bom(str.data(), str.length());
}


template <typename T>
string to_utf8(const T* str)
{
    return to_utf8(str, std::char_traits<T>::length(str));
}


template <typename T>
std::u16string to_utf16(const T* str)
{
    return to_utf16(str, std::char_traits<T>::length(str));
}


template <typename T>
std::u32string to_utf32(const T* str)
{
    return to_utf32(str, std::char_traits<T>::length(str));
}


template <typename T>
string to_utf8(const std::basic_string<T>& str)
{
    static_assert(!std::is_same<char, T>::value,
                  "calling to_utf8 on a utf8 string");
    return to_utf8(str.data(), str.length());
}


template <typename T>
std::u16string to_utf16(const std::basic_string<T>& str)
{
    static_assert(!std::is_same<char16_t, T>::value,
                  "calling to_utf16 on a utf16 string");
    return to_utf16(str.data(), str.length());
}


template <typename T>
std::u32string to_utf32(const std::basic_string<T>& str)
{
    static_assert(!std::is_same<char32_t, T>::value,
                  "calling to_utf32 on a utf32 string");
    return to_utf32(str.data(), str.length());
}

} // namespace mk1
