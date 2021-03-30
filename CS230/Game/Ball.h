/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"           // Sprite
#include "..\Engine\Vec2.h"             // math::vec2
#include "..\Engine\TransformMatrix.h"  // math::TransformMatrix

class Ball {
public:
    Ball(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix cameraMatrix);

private:
    CS230::Sprite sprite;
    math::vec2 initPosition;
    math::vec2 position;
    math::vec2 velocity;
    math::TransformMatrix objectMatrix;

    static constexpr double bounceVelocity{ 750 };
};