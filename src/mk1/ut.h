#pragma once

// C Standard Library Includes
#include <climits>
#include <cmath>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// C++ Standard Library includes
#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#define MK1_UNUSED(x)

#define SAFE_DELETE(x)                                                         \
    {                                                                          \
        delete (x);                                                            \
        (x) = nullptr;                                                         \
    }
#define SAFE_DELETE_ARRAY(x)                                                   \
    {                                                                          \
        delete[](x);                                                           \
        (x) = nullptr;                                                         \
    }

#define COUNT_OF(x) (std::extent<decltype(x)>::value)

namespace mk1 {

using namespace std::literals::chrono_literals;
using namespace std::string_literals;
using std::to_string;

template <typename exception_t = std::runtime_error>
static void assert_throw(const bool expression, const char* msg)
{
    if (!expression) {
        throw exception_t(msg);
    }
}

template <typename exception_t = std::runtime_error>
static void assert_throw(const bool expression, const std::string& msg)
{
    if (!expression) {
        throw exception_t(msg);
    }
}

} // namespace mk1

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <fmt/core.h>
#undef _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <mk1/utf.h>
#include <mk1/math/math.h>
#include <mk1/ut/Logger.h>
#include <mk1/ut/Timer.h>
#include <mk1/ut/containers/containers.h>
#include <mk1/ut/enum_bitwise_helper.h>
