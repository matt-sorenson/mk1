#pragma once

namespace mk1 {

typedef std::string string;

bool is_valid_utf8(const char* str, const size_t len);
bool starts_with_utf8_bom(const char* str, const size_t len);

string to_utf8(const char16_t* str, const size_t len);
string to_utf8(const char32_t* str, const size_t len);

std::u16string to_utf16(const char* str, const size_t len);
std::u16string to_utf16(const char32_t* str, const size_t len);

std::u32string to_utf32(const char* str, const size_t len);
std::u32string to_utf32(const char16_t* str, const size_t len);

inline bool is_valid_utf8(const char* str);
inline bool starts_with_utf8_bom(const char* str);

inline bool is_valid_utf8(const string& str);
inline bool starts_with_utf8_bom(const string& str);

template <typename T>
string to_utf8(const T* str);
template <typename T>
std::u16string to_utf16(const T* str);
template <typename T>
std::u32string to_utf32(const T* str);

template <typename T>
string to_utf8(const std::basic_string<T>& str);
template <typename T>
std::u16string to_utf16(const std::basic_string<T>& str);
template <typename T>
std::u32string to_utf32(const std::basic_string<T>& str);

} // namespace mk1

#include <mk1/utf.cpp.inl>
