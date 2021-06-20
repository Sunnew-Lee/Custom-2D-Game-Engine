/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/21/2021
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "BallRobot.h"
#include "Score.h"
#include "../Engine/Collision.h"
#include "Ship_Anims.h"
#include "Life.h"
#include "My_Player.h"

BallRobot::BallRobot(GameObject* player, math::vec2 pos, double rotation, math::vec2 scale, math::vec2 velocity) : player(player), GameObject(pos, rotation, scale) {
    SetVelocity(velocity);
    AddGOComponent(new CS230::Sprite("assets/BallRobot.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
    isDead = false;
}

void BallRobot::Update(double dt) {
    GameObject::Update(dt);

    if (GetPosition().y > Engine::GetWindow().GetSize().y + (GetGOComponent<CS230::Sprite>()->GetFrameSize().y) / 2.0) {
        if (isDead == false) { static_cast<My_Player*>(player)->AddCounter(); }
        Destroy();
        return;
    }
    else if (GetPosition().y < 0 - (GetGOComponent<CS230::Sprite>()->GetFrameSize().y) / 2.0) {
        if (isDead == false) { static_cast<My_Player*>(player)->AddCounter(); }
        Destroy();
        return;
    }
}

bool BallRobot::CanCollideWith(GameObjectType objectBType) {
    if (objectBType == GameObjectType::My_Player) {
        return true;
    }
    else {
        return false;
    }
}

void BallRobot::ResolveCollision(GameObject* objectB) {
    math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
    math::rect2 RobotRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
    switch (objectB->GetObjectType()) {
    case GameObjectType::Ammo:
        Engine::GetGSComponent<Score>()->AddScore(50);
    case GameObjectType::My_Player:
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
        RemoveGOComponent<CS230::Collision>();
        isDead = true;
        break;
    }
}