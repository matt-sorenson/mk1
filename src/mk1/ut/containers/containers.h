#pragma once

#include <mk1/ut/containers/IntrusiveList.h>

#define MK1_CONTAINERS_CONTIGUOUS_CONST(type, data_member, size)               \
    const type* data() const { return (data_member); }                         \
    const type* begin() const { return (data_member); }                        \
    const type* cbegin() const { return (data_member); }                       \
    const type* end() const { return (data_member) + (size); }                 \
    const type* cend() const { return (data_member) + (size); }                \
    constexpr const type& operator[](const size_t idx) const                   \
    {                                                                          \
        return (data_member)[idx];                                             \
    }

#define MK1_CONTAINERS_CONTIGUOUS(type, data_member, size)                     \
    MK1_CONTAINERS_CONTIGUOUS_CONST(type, data_member, size)                   \
    type* data() { return (data_member); }                                     \
    type* begin() { return (data_member); }                                    \
    type* end() { return (data_member) + (size); }                             \
    type& operator[](const size_t idx) { return (data_member)[idx]; }
