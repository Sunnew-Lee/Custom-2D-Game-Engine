/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: TODO
Creation date: TODO
-----------------------------------------------------------------*/
#pragma once
#include <cmath>
#include <limits>

namespace math
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    struct vec2
    {
        double x{ 0. };
        double y{ 0. };

        [[nodiscard]] constexpr vec2() noexcept = default;
        [[nodiscard]] constexpr vec2(double value) noexcept :vec2(value, value) {};
        [[nodiscard]] constexpr vec2(double x_value, double y_value) noexcept :x(x_value), y(y_value) {};


        constexpr vec2& operator+=(const vec2 right) noexcept;
        constexpr vec2& operator-=(vec2 right) noexcept;

        constexpr vec2& operator*=(double scale) noexcept;
        constexpr vec2& operator/=(double scale) noexcept;

        [[nodiscard]] constexpr double LengthSquared() noexcept;
        [[nodiscard]] inline vec2& Normalize() noexcept;

    };

    [[nodiscard]] constexpr vec2 operator+(const vec2 left, const vec2 right) noexcept;
    [[nodiscard]] constexpr vec2 operator-(vec2 left, vec2 right) noexcept;
    [[nodiscard]] constexpr vec2 operator-(vec2 right) noexcept;

    [[nodiscard]] constexpr vec2 operator*(double scale, vec2 right) noexcept;
    [[nodiscard]] constexpr vec2 operator*(vec2 left, double scale) noexcept;
    [[nodiscard]] constexpr vec2 operator/(vec2 left, double scale) noexcept;

    [[nodiscard]] constexpr bool operator==(vec2 left, vec2 right) noexcept;
    [[nodiscard]] constexpr bool operator!=(vec2 left, vec2 right) noexcept;





    struct ivec2
    {
        int x{ 0 };
        int y{ 0 };

        [[nodiscard]] constexpr ivec2() noexcept = default;
        [[nodiscard]] constexpr ivec2(int value) noexcept :ivec2(value, value) {};
        [[nodiscard]] constexpr ivec2(int x_value, int y_value) noexcept :x(x_value), y(y_value) {};

        constexpr ivec2& operator+=(ivec2 right) noexcept;
        constexpr ivec2& operator-=(ivec2 right) noexcept;

        constexpr ivec2& operator*=(int scale) noexcept;
        constexpr ivec2& operator/=(int scale) noexcept;

        [[nodiscard]] constexpr operator vec2() noexcept;
    };

    [[nodiscard]] constexpr ivec2 operator+(ivec2 left, ivec2 right) noexcept;
    [[nodiscard]] constexpr ivec2 operator-(ivec2 left, ivec2 right) noexcept;
    [[nodiscard]] constexpr ivec2 operator-(ivec2 right) noexcept;

    [[nodiscard]] constexpr ivec2 operator*(ivec2 scale, ivec2 right) noexcept;
    [[nodiscard]] constexpr ivec2 operator*(ivec2 left, int scale) noexcept;
    [[nodiscard]] constexpr ivec2 operator/(ivec2 left, int scale) noexcept;


    [[nodiscard]] constexpr vec2 operator*(double scale, ivec2 right) noexcept;
    [[nodiscard]] constexpr vec2 operator*(ivec2 left, double scale) noexcept;
    [[nodiscard]] constexpr vec2 operator/(ivec2 left, double scale) noexcept;

    [[nodiscard]] constexpr bool operator==(ivec2 left, ivec2 right) noexcept;
    [[nodiscard]] constexpr bool operator!=(ivec2 left, ivec2 right) noexcept;
}

#include "Vec2.inl"
