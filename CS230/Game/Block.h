/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.h
Project: CS230
Author: Kevin Wright
Creation date: 2/21/2021
-----------------------------------------------------------------*/

#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class GameObjectManager;
enum class GameObjectType;

class Block : public CS230::GameObject {
public:
    Block(GameObject* player);
    void Update(double dt) override;
    std::string GetObjectTypeName() { return "Ball Robot"; }
    virtual GameObjectType GetObjectType() override { return GameObjectType::BallRobot; }
    virtual bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;
private:
    int life;
    GameObject* player;
    static constexpr double PI = 3.1415926535897932384626433832795;
};