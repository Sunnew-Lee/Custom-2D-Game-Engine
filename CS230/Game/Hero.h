/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"    // InputKey
#include "..\Engine\Vec2.h"     // math::vec2

class Hero {
public:
    Hero(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw();

private:
    CS230::Sprite sprite;
    math::vec2 startPos;
    math::vec2 position;

    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey moveJumpKey;
    math::vec2 velocity;
    bool isJumping;
    bool isRising;

    static constexpr double Acceleration_x{ 500 };
    static constexpr double Drag_x{ 1000 };
    static constexpr double Max_Velocity_x{ 1000 };
    static constexpr double Jump_Velocity{ 1000 };
};