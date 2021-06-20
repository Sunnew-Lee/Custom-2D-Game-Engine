/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: BallRobot.h
Project: CS230
Author: sunwoo.lee
Creation date: 06/19/2021
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class GameObjectManager;
enum class GameObjectType;

class BallRobot : public CS230::GameObject {
public:
    static constexpr math::vec2 BallRobotVelocity = math::vec2{ 0, 300 };

    BallRobot(GameObject* player, math::vec2 pos, double rotation, math::vec2 scale, math::vec2 ballrobotVelocity);
    void Update(double dt) override;
    std::string GetObjectTypeName() { return "Ball Robot"; }
    virtual GameObjectType GetObjectType() override { return GameObjectType::BallRobot; }
    virtual bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;
private:
    bool isDead;
    GameObject* player;
};