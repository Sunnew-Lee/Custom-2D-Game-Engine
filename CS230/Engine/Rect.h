/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Rect.h
Author: sunwoo.lee
Creation date: 03/26/2021
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"   // math::vec2, math::ivec2

namespace math
{
    struct [[nodiscard]] rect2
    {
        vec2 bottomLeft{ 0. };
        vec2 topRight{ 0. };

        constexpr rect2() noexcept = default;
        constexpr rect2(vec2 vec) noexcept :rect2(vec, vec) {};
        constexpr rect2(vec2 bottomLeft_vec, vec2 topRight_vec) noexcept :bottomLeft(bottomLeft_vec), topRight(topRight_vec) {};

    };

    struct [[nodiscard]] irect2
    {
        ivec2 bottomLeft{ 0 };
        ivec2 topRight{ 0 };

        constexpr irect2() noexcept = default;
        constexpr irect2(ivec2 ivec) noexcept :irect2(ivec, ivec) {};
        constexpr irect2(ivec2 bottomLeft_ivec, ivec2 topRight_ivec) noexcept :bottomLeft(bottomLeft_ivec), topRight(topRight_ivec) {};

    };
}
