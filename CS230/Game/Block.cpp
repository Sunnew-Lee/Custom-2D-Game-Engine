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
#include "Block.h"
#include "../Engine/Collision.h"
#include "Ship_Anims.h"
#include "Life.h"
#include "../Engine/GameObjectManager.h"
#include "PowerUp.h"
#include "Money.h"
#include "Heart.h"
#include "GameParticles.h"

Block::Block(GameObject* player) : life(3), player(player), GameObject() {
    AddGOComponent(new CS230::Sprite("assets/Block.spt", this));
    SetPosition(math::vec2{ static_cast<double>(rand() % static_cast<int>(Engine::GetWindow().GetSize().x * 0.75) + Engine::GetWindow().GetSize().x * 0.125) , static_cast<double>(Engine::GetWindow().GetSize().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) });
    SetScale({ 1,1 });
    SetVelocity({ 0, -100 });
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
}

void Block::Update(double dt) {
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

bool Block::CanCollideWith(GameObjectType objectBType) {
    if (objectBType == GameObjectType::My_Player) {
        return true;
    }
    else {
        return false;
    }
}

void Block::ResolveCollision(GameObject* objectB) {
    math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
    math::rect2 RobotRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
    switch (objectB->GetObjectType()) {
    case GameObjectType::Ammo:    
        if (--life <= 0)
        {
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
            RemoveGOComponent<CS230::Collision>();
            objectB->Destroy();
            int rad = rand() % 100;
            if (rad < 10)
            {
                Engine::GetGSComponent<CS230::GameObjectManager>()->Add( new PowerUp(player, GetPosition(), GetVelocity()) );//powerup
            }
            else if (rad < 30)
            {
                Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Heart(GetPosition(), GetVelocity()));//heart
            }
            else if (rad < 75)
            {
                Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Money(GetPosition(), GetVelocity()));//money
            }
        }
        break;
    case GameObjectType::My_Player:
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
        RemoveGOComponent<CS230::Collision>();
        break;
    }
    Engine::GetGameStateManager().GetGSComponent<HitEmitter>()->Emit(1, objectB->GetPosition(), GetVelocity(), { 0,0 }, 0);
    Engine::GetGameStateManager().GetGSComponent<BlockBitEmitter>()->Emit(10, objectB->GetPosition(), GetVelocity(), GetVelocity(), PI * 2);
}