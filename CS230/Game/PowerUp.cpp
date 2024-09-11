/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PowerUp.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 06/19/2021
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "PowerUp.h"
#include "../Engine/Collision.h"
#include "Ship_Anims.h"
#include "My_Player.h"

PowerUp::PowerUp(GameObject* player, math::vec2 pos, math::vec2 velocity) : player(player), GameObject(pos) {
    SetVelocity(velocity);
    SetScale({ 5,5 });
    AddGOComponent(new CS230::Sprite("assets/PowerUp.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
}

void PowerUp::Update(double dt) {
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

bool PowerUp::CanCollideWith(GameObjectType objectBType) {
    if (objectBType == GameObjectType::My_Player) {
        return true;
    }
    else {
        return false;
    }
}

void PowerUp::ResolveCollision(GameObject* objectB) {
    math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
    math::rect2 RobotRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
    switch (objectB->GetObjectType()) {
    case GameObjectType::My_Player:
        static_cast<My_Player*>(player)->AddPower();
        RemoveGOComponent<CS230::Collision>();
        Destroy();
        break;
    }
}