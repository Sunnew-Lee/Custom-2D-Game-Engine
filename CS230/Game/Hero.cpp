/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/15/2021
-----------------------------------------------------------------*/
#include "Hero.h"
#include "..\Engine\Engine.h"	// GetLogger(), GetWindow()
#include "Level1.h"				// gravity, floor
#include <string>				// to_string()
#include "..\Engine\Camera.h"	// GetPosition()
#include "Hero_Anims.h"			// Hero_Anim

Hero::Hero(math::vec2 startPos, const CS230::Camera& camera)
	:sprite(), startPos(startPos), camera(camera), position(startPos), velocity(0), isRunningLeft(false), currState(&stateIdle),
	moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), moveJumpKey(CS230::InputKey::Keyboard::Up)
{}

void Hero::Load()
{
	sprite.Load("assets/Hero.spt");
	position = startPos;
	velocity = 0;
	isRunningLeft = false;

	currState = &stateIdle;
	currState->Enter(this);
}

void Hero::Update(double dt)
{
	currState->Update(this, dt);
	position += velocity * dt;
	currState->TestForExit(this);
	sprite.Update(dt);

	if (position.x - sprite.GetFrameSize().x / 2 < camera.GetPosition().x)
	{
		velocity.x = 0;
		position.x = camera.GetPosition().x + sprite.GetFrameSize().x / 2;
	}
	else if (position.x + sprite.GetFrameSize().x / 2 > Engine::GetWindow().GetSize().x + camera.GetPosition().x)
	{
		velocity.x = 0;
		position.x = Engine::GetWindow().GetSize().x + camera.GetPosition().x - sprite.GetFrameSize().x / 2;
	}

	if (isRunningLeft == true)
	{
		objectMatrix = math::TranslateMatrix::TranslateMatrix(position) * math::ScaleMatrix::ScaleMatrix(math::vec2(-1.0, 1.0));
	}
	else
	{
		objectMatrix = math::TranslateMatrix::TranslateMatrix(position);
	}
}

void Hero::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(cameraMatrix*objectMatrix);
}

math::vec2 Hero::Get_Hero_Position()
{
	return position;
}

void Hero::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		velocity.x -= Acceleration_x * dt;
		if (velocity.x < -Max_Velocity_x)
		{
			velocity.x = -Max_Velocity_x;
		}
	}
	if (moveRightKey.IsKeyDown() == true)
	{
		velocity.x += Acceleration_x * dt;
		if (velocity.x > Max_Velocity_x)
		{
			velocity.x = Max_Velocity_x;
		}
	}

	if (moveLeftKey.IsKeyDown() == false && moveRightKey.IsKeyDown() == false)
	{
		if (velocity.x < 0)
		{
			velocity.x += Drag_x * dt;
			if (velocity.x > 0)
			{
				velocity.x = 0;
			}
		}
		else if (velocity.x > 0)
		{
			velocity.x -= Drag_x * dt;
			if (velocity.x < 0)
			{
				velocity.x = 0;
			}
		}
	}
}

void Hero::ChangeState(State* newState) {
	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}

void Hero::State_Idle::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
}
void Hero::State_Idle::Update(Hero* , double )
{
}
void Hero::State_Idle::TestForExit(Hero* hero)
{
	if (hero->moveJumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->moveLeftKey.IsKeyDown() == true || hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

void Hero::State_Running::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->isRunningLeft = true;
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->isRunningLeft = false;
	}
}
void Hero::State_Running::Update(Hero* hero, double dt)
{
	hero->UpdateXVelocity(dt);
}
void Hero::State_Running::TestForExit(Hero* hero)
{
	if (hero->moveJumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->velocity.x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->velocity.x > 0)
		{
			hero->ChangeState(&hero->stateSkidding);
		}
	}
	if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->velocity.x < 0)
		{
			hero->ChangeState(&hero->stateSkidding);
		}
	}
}

void Hero::State_Skidding::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}
void Hero::State_Skidding::Update(Hero* hero, double dt)
{
	if (hero->velocity.x > 0)
	{
		hero->velocity.x -= Drag_x * 2 * dt;
	}
	else if (hero->velocity.x < 0)
	{
		hero->velocity.x += Drag_x * 2 * dt;
	}
}
void Hero::State_Skidding::TestForExit(Hero* hero)
{
	if (hero->moveJumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->velocity.x <= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->velocity.x >= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveLeftKey.IsKeyDown() == false && hero->moveRightKey.IsKeyDown() == false)
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

void Hero::State_Jumping::Enter(Hero* hero) {
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->velocity.y = Hero::Jump_Velocity;   //Set the velocity.y
}
void Hero::State_Jumping::Update(Hero* hero, double dt) {
	hero->velocity.y -= Level1::gravity * dt;  //Apply Gravity
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}
void Hero::State_Jumping::TestForExit(Hero* hero) {
	if (hero->moveJumpKey.IsKeyDown() == false) {  //Jump Key not pressed
		hero->velocity.y = 0;
	}
	if (hero->velocity.y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}
void Hero::State_Falling::Update(Hero* hero, double dt)
{
	hero->velocity.y -= Level1::gravity * dt;
	hero->UpdateXVelocity(dt);
}
void Hero::State_Falling::TestForExit(Hero* hero)
{
	if (hero->position.y <= Level1::floor)
	{
		hero->velocity.y = 0;
		hero->position.y = Level1::floor;


		if (hero->velocity.x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else 
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else if (hero->velocity.x < 0)
		{
			if (hero->moveRightKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else
		{
			hero->ChangeState(&hero->stateIdle);
		}
	}
}