/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: sunwoo.lee
Creation date: 03/15/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"           // Sprite
#include "..\Engine\Input.h"            // InputKey
#include "..\Engine\Vec2.h"             // math::vec2
#include "..\Engine\TransformMatrix.h"  // math::TransformMatrix


class Ship {
public:
    Ship(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw();

private:
    void TestForWrap();

    CS230::Sprite sprite;
    math::vec2 startPos;
    math::vec2 position;
    math::vec2 velocity;
    math::TransformMatrix objectMatrix;

    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey moveUpKey;
    CS230::InputKey moveDownKey;

    static constexpr double accel = 400;
    static constexpr double drag = 1.0f;
};