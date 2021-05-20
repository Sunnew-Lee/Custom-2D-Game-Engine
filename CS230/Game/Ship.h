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
#include "..\Engine\Input.h"            // InputKey
#include "..\Engine\GameObject.h"
#include "..\Engine\Sprite.h"           // Sprite


class Ship : public CS230::GameObject {
public:
    Ship(math::vec2 startPos);
    void Update(double dt) override;
    void Draw(math::TransformMatrix cameraMatrix) override;
    GameObjectType GetObjectType() override;
    std::string GetObjectTypeName() override;
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(CS230::GameObject* objectB) override;
    bool IsDead() { return isDead; }

private:
    CS230::Sprite sprite_flame_1;
    CS230::Sprite sprite_flame_2;
    bool is_accelerating;
    bool isDead;

    CS230::InputKey rotateCounterKey;
    CS230::InputKey rotateClockKey;
    CS230::InputKey accelerateKey;
    CS230::InputKey shootLaserKey;

    static constexpr double accel = 400;
    static constexpr double drag = 1.0f;
    static constexpr double rotate_speed = 2;
};