/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/23/2021
-----------------------------------------------------------------*/
#include "Ball.h"
#include "..\Engine\Camera.h"		// GetPosition()
#include "..\Engine\Engine.h"		// GetLogger()
#include "Ball_Anims.h"				// Ball_Anim
#include "Gravity.h"				// Gravity
#include "..\Engine\Sprite.h"		// Sprite
#include "GameObjectTypes.h"		// GameObjectType::Floor
#include "../Engine/Collision.h"	// RectCollision

Ball::Ball(math::vec2 startPos) : GameObject(startPos) {
	AddGOComponent(new CS230::Sprite("assets/Ball.spt", this));
	currState = &stateBounce;
	currState->Enter(this);
}

GameObjectType Ball::GetObjectType()
{
	return GameObjectType::Ball;
}

std::string Ball::GetObjectTypeName()
{
	return std::string("Ball");
}

bool Ball::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Floor) {
		return true;
	}
	return false;
}

void Ball::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Floor) {
		CS230::RectCollision* collideRect =
			static_cast<CS230::RectCollision*>(objectB->GetGOComponent<CS230::RectCollision>());
		SetPosition({ GetPosition().x, collideRect->GetWorldCoorRect().Top() });
		SetVelocity({ GetVelocity().x, 0 });
		ChangeState(&stateLand);
	}
}

void Ball::State_Bounce::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
	ball->SetVelocity(math::vec2{ ball->GetVelocity().x,ball->bounceVelocity });
}
void Ball::State_Bounce::Update(GameObject* object, double dt)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->UpdateVelocity(math::vec2{ 0,-(Engine::GetGSComponent<Gravity>()->GetValue() * dt) });
}
void Ball::State_Bounce::TestForExit(GameObject* )
{}

void Ball::State_Land::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}
void Ball::State_Land::Update(GameObject* , double )
{
}
void Ball::State_Land::TestForExit(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	if (ball->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		ball->ChangeState(&ball->stateBounce);
	}
}