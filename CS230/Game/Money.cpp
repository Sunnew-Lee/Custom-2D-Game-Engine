/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Money.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 06/19/2021
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "Money.h"
#include "../Engine/Collision.h"
#include "Ship_Anims.h"
#include "Score.h"

Money::Money(math::vec2 pos, math::vec2 velocity) : GameObject(pos) {
    SetVelocity(velocity);
    SetScale({ 5,5 });
    AddGOComponent(new CS230::Sprite("assets/Money.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
}

void Money::Update(double dt) {
    GameObject::Update(dt);

    if (GetPosition().y > Engine::GetWindow().GetSize().y + (GetGOComponent<CS230::Sprite>()->GetFrameSize().y) / 2.0) {
        Destroy();
        return;
    }
    else if (GetPosition().y < 0 - (GetGOComponent<CS230::Sprite>()->GetFrameSize().y) / 2.0) {
        Destroy();
        return;
    }
}

bool Money::CanCollideWith(GameObjectType objectBType) {
    if (objectBType == GameObjectType::My_Player) {
        return true;
    }
    else {
        return false;
    }
}

void Money::ResolveCollision(GameObject* objectB) {
    math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
    math::rect2 RobotRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
    switch (objectB->GetObjectType()) {
    case GameObjectType::My_Player:
        Engine::GetGSComponent<Score>()->AddScore(1000);
        RemoveGOComponent<CS230::Collision>();
        Destroy();
        break;
    }
}