#pragma once

#include <mk1/math/math.h>

namespace mk1::math {

struct Color {
    constexpr Color(const uint8_t _r, const uint8_t _g, const uint8_t _b)
        : r(_r), g(_g), b(_b), a(0xFF)
    {
    }


    constexpr Color(const uint8_t _r, const uint8_t _g, const uint8_t _b,
                    const uint8_t _a)
        : r(_r), g(_g), b(_b), a(_a)
    {
    }


    constexpr Color(const float3& color)
        : r((uint8_t)math::clamp(color.x * 255.0f, 0.0f, 255.0f)),
          g((uint8_t)math::clamp(color.y * 255.0f, 0.0f, 255.0f)),
          b((uint8_t)math::clamp(color.z * 255.0f, 0.0f, 255.0f)), a(0xFF)
    {
    }


    constexpr Color(const float4& color)
        : r((uint8_t)math::clamp(color.x * 255.0f, 0.0f, 255.0f)),
          g((uint8_t)math::clamp(color.y * 255.0f, 0.0f, 255.0f)),
          b((uint8_t)math::clamp(color.z * 255.0f, 0.0f, 255.0f)),
          a((uint8_t)math::clamp(color.w * 255.0f, 0.0f, 255.0f))
    {
    }


    constexpr float4 to_float4() const
    {
        return {((float)r) / 255.0f, ((float)g) / 255.0f, ((float)b) / 255.0f,
                ((float)a) / 255.0f};
    }


    constexpr float3 to_float3() const
    {
        return {((float)r) / 255.0f, ((float)g) / 255.0f, ((float)b) / 255.0f};
    }


    constexpr uint32_t to_argb() const { return pack(a, r, g, b); }
    constexpr uint32_t to_rgba() const { return pack(r, g, b, a); }
    constexpr uint32_t to_abgr() const { return pack(a, b, g, r); }
    constexpr uint32_t to_xrgb() const { return pack(0xFF, r, g, b); }
    constexpr uint32_t to_rgbx() const { return pack(r, g, b, 0xFF); }
    constexpr uint32_t to_xbgr() const { return pack(0xFF, b, g, r); }
    uint8_t r, g, b, a;

  private:
    constexpr uint32_t pack(const uint8_t b1, const uint8_t b2,
                            const uint8_t b3, const uint8_t b4) const
    {
        return (uint32_t(b1) << 24) | (uint32_t(b2) << 16) | (uint32_t(b3) << 8)
               | uint32_t(b4);
    }
};

static_assert(sizeof(Color) == sizeof(uint32_t),
              "sizeof(color) != sizeof(uint32_t)");
static_assert(offsetof(Color, r) == 0, "incorrect packing of Color::r");
static_assert(offsetof(Color, g) == 1, "incorrect packing of Color::g");
static_assert(offsetof(Color, b) == 2, "incorrect packing of Color::b");
static_assert(offsetof(Color, a) == 3, "incorrect packing of Color::a");
}

namespace mk1 {

using math::Color;
}
