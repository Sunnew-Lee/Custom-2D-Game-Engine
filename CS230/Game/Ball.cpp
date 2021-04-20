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
#include "Level1.h"				// gravity, floor
#include "..\Engine\Camera.h"	// GetPosition()
#include "..\Engine\Engine.h"	// GetLogger()
#include "Ball_Anims.h"			// Ball_Anim

Ball::Ball(math::vec2 startPos) : GameObject(startPos) {
	sprite.Load("assets/Ball.spt");
	currState = &stateBounce;
	currState->Enter(this);
}

void Ball::State_Bounce::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->sprite.PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
	ball->SetVelocity(math::vec2{ ball->GetVelocity().x,ball->bounceVelocity });
}
void Ball::State_Bounce::Update(GameObject* object, double dt)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->UpdateVelocity(math::vec2{ 0,-(Level1::gravity * dt) });
}
void Ball::State_Bounce::TestForExit(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	if (ball->GetPosition().y < Level1::floor) {
		ball->SetPosition({ ball->GetPosition().x, Level1::floor });
		ball->SetVelocity({ 0, 0 });
		ball->ChangeState(&ball->stateLand);
	}
}

void Ball::State_Land::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->sprite.PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
	ball->SetVelocity(math::vec2{ 0 });
	ball->SetPosition(math::vec2{ ball->GetPosition().x,Level1::floor });
}
void Ball::State_Land::Update(GameObject* , double )
{
}
void Ball::State_Land::TestForExit(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	if (ball->sprite.IsAnimationDone() == true)
	{
		ball->ChangeState(&ball->stateBounce);
	}
}