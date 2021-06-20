/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Enemy.cpp
Project: CS230
Author: Kevin Wright
Creation date: 3/1/2021
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"	//Logger, Window
#include "..\Engine\GameObject.h"		//GetCollision
#include "..\Engine\Collision.h"		
#include "..\Engine\ShowCollision.h"
#include "../Engine/GameObjectManager.h"
#include "BadRobot.h"
#include "Score.h"
#include "Flame_Anims.h"
#include "Ship_Anims.h"
#include "GameObjectTypes.h"
#include "BallRobot.h"
#include "Life.h"
#include "My_Player.h"
#include "GameParticles.h"

BadRobot::BadRobot(GameObject* player) : player(player), counter(0), timer(0), life(6), life_time(0), rand_time(3), isDead(false) {
	AddGOComponent(new CS230::Sprite("assets/BadRobot.spt", this));
	SetPosition(math::vec2{ static_cast<double>(rand() % static_cast<int>(Engine::GetWindow().GetSize().x * 0.75) + Engine::GetWindow().GetSize().x * 0.125) , Engine::GetWindow().GetSize().y * 0.9 });
	SetScale({ 2,2 });
	SetVelocity({ static_cast<double>((rand() % 751) - 375), 0 });
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
}

void BadRobot::Update(double dt) {
	timer += dt;
	life_time += dt;
	if (IsDead() == false) {
		if (life_time >= respawn_time)
		{
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(
				new BallRobot(player, GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)),
					GetRotation(), GetScale(), -BallRobot::BallRobotVelocity));
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(
				new BallRobot(player, GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)),
					GetRotation(), GetScale(), -BallRobot::BallRobotVelocity));
			life_time = 0;
		}
		if (timer >= rand_time)
		{
			double x_vel = static_cast<double>((rand() % 276) + 100);
			if (GetVelocity().x >= 0)
			{
				SetVelocity({ -x_vel, 0 });
			}
			else
			{
				SetVelocity({ x_vel, 0 });
			}
			rand_time = (rand() % 4) + 1;
			timer = 0;
		}
	}
	UpdatePosition(GetVelocity() * dt);
	UpdateGOComponents(dt);
}

void BadRobot::Draw(math::TransformMatrix cameraMatrix) {
	math::TransformMatrix shipScreenMatrix = cameraMatrix * GetMatrix();
	GetGOComponent<CS230::Sprite>()->Draw(shipScreenMatrix);

	ShowCollision* showCollisionPtr = Engine::GetGSComponent<ShowCollision>();
	if (showCollisionPtr != nullptr && showCollisionPtr->IsEnabled() == true) {
		CS230::Collision* collisionPtr = GetGOComponent<CS230::Collision>();
		if (collisionPtr != nullptr) {
			collisionPtr->Draw(cameraMatrix);
		}
	}
}

GameObjectType BadRobot::GetObjectType() {
	return GameObjectType::BadRobot;
}

std::string BadRobot::GetObjectTypeName() {
	return "Bad_Robot";
}

bool BadRobot::CanCollideWith(GameObjectType objectBType) {
	if (objectBType == GameObjectType::Floor) {
		return true;
	}
	else {
		return false;
	}
}

void BadRobot::ResolveCollision(GameObject* collidedWith) {
	switch (collidedWith->GetObjectType()) {
	case GameObjectType::Floor:
		if (GetPosition().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x <= 90)
		{
			SetPosition({ 90. + GetGOComponent<CS230::Sprite>()->GetFrameSize().x , GetPosition().y });
			timer = 5;
		}
		else if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x >= Engine::GetWindow().GetSize().x - 90)
		{
			SetPosition({ 1350. - GetGOComponent<CS230::Sprite>()->GetFrameSize().x , GetPosition().y });
			timer = 5;
		}
		break;
	case GameObjectType::Ammo:
		Engine::GetGameStateManager().GetGSComponent<HitEmitter>()->Emit(1, collidedWith->GetPosition(), { 0, 0 }, { 0,0 }, 0);
		if (--life <= 0)
		{
			Engine::GetGSComponent<Score>()->AddScore(300);
			isDead = true;
			Destroy();
			RemoveGOComponent<CS230::Collision>();
		}
		break;
	}
}