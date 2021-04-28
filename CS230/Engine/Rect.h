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
    struct [[nodiscard]] rect2 {
        vec2 bottomLeft{ 0.0, 0.0 };
        vec2 topRight{ 0.0, 0.0 };

        constexpr vec2 Size() const noexcept { return { topRight.x - bottomLeft.x, std::abs(topRight.y - bottomLeft.y) }; }
    };
    struct [[nodiscard]] irect2 {
        ivec2 bottomLeft{ 0, 0 };
        ivec2 topRight{ 0, 0 };

        constexpr ivec2 Size() const noexcept { return { topRight.x - bottomLeft.x, std::abs(topRight.y - bottomLeft.y) }; }
    };

}
