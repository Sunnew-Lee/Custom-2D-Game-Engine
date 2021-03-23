/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: sunwoo.lee
Creation date: 03/15/2021
-----------------------------------------------------------------*/
#pragma once
#include <cmath>    // sqrt()
#include <limits>   // numeric_limits::epsilon()

namespace math
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    struct [[nodiscard]] vec2
    {
        double x{ 0. };
        double y{ 0. };

        constexpr vec2() noexcept = default;
        constexpr vec2(double value) noexcept :vec2(value, value) {};
        constexpr vec2(double x_value, double y_value) noexcept :x(x_value), y(y_value) {};


        constexpr vec2& operator+=(const vec2 right) noexcept;
        constexpr vec2& operator-=(const vec2 right) noexcept;

        constexpr vec2& operator*=(const double scale) noexcept;
        constexpr vec2& operator/=(const double scale) noexcept;

        [[nodiscard]] constexpr double LengthSquared() noexcept;
        inline vec2& Normalize() noexcept;

    };

    constexpr vec2 operator+(const vec2 left, const vec2 right) noexcept;
    constexpr vec2 operator-(const vec2 left, const vec2 right) noexcept;
    constexpr vec2 operator-(const vec2 right) noexcept;

    constexpr vec2 operator*(const double scale, const vec2 right) noexcept;
    constexpr vec2 operator*(const vec2 left, const double scale) noexcept;
    constexpr vec2 operator/(const vec2 left, const double scale) noexcept;

    [[nodiscard]] constexpr bool operator==(const vec2 left, const vec2 right) noexcept;
    [[nodiscard]] constexpr bool operator!=(const vec2 left, const vec2 right) noexcept;





    struct [[nodiscard]] ivec2
    {
        int x{ 0 };
        int y{ 0 };

        constexpr ivec2() noexcept = default;
        constexpr ivec2(int value) noexcept :ivec2(value, value) {};
        constexpr ivec2(int x_value, int y_value) noexcept :x(x_value), y(y_value) {};

        constexpr ivec2& operator+=(const ivec2 right) noexcept;
        constexpr ivec2& operator-=(const ivec2 right) noexcept;

        constexpr ivec2& operator*=(const int scale) noexcept;
        constexpr ivec2& operator/=(const int scale) noexcept;

        constexpr operator vec2() noexcept;
    };

    constexpr ivec2 operator+(const ivec2 left, const ivec2 right) noexcept;
    constexpr ivec2 operator-(const ivec2 left, const ivec2 right) noexcept;
    constexpr ivec2 operator-(const ivec2 right) noexcept;

    constexpr ivec2 operator*(const int scale, const ivec2 right) noexcept;
    constexpr ivec2 operator*(const ivec2 left, const int scale) noexcept;
    constexpr ivec2 operator/(const ivec2 left, const int scale) noexcept;


    constexpr vec2 operator*(const double scale, const ivec2 right) noexcept;
    constexpr vec2 operator*(const ivec2 left, const double scale) noexcept;
    constexpr vec2 operator/(const ivec2 left, const double scale) noexcept;

    [[nodiscard]] constexpr bool operator==(const ivec2 left, const ivec2 right) noexcept;
    [[nodiscard]] constexpr bool operator!=(const ivec2 left, const ivec2 right) noexcept;
}

#include "Vec2.inl"
