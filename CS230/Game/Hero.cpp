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
#include "Gravity.h"			// Gravity
#include "..\Engine\Sprite.h"	// Sprite

Hero::Hero(math::vec2 startPos)
	:GameObject(startPos),
	moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), moveJumpKey(CS230::InputKey::Keyboard::Up)
{
	AddGOComponent(new CS230::Sprite("assets/Hero.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
}

void Hero::Update(double dt)
{
	GameObject::Update(dt);

	if (GetPosition().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 < Engine::GetGSComponent<CS230::Camera>()->GetPosition().x)
	{
		SetVelocity(math::vec2{ 0, GetVelocity().y });
		SetPosition(math::vec2{ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2,GetPosition().y });
	}
	else if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 > Engine::GetWindow().GetSize().x + Engine::GetGSComponent<CS230::Camera>()->GetPosition().x)
	{
		SetVelocity(math::vec2{ 0, GetVelocity().y });
		SetPosition(math::vec2{ Engine::GetWindow().GetSize().x + Engine::GetGSComponent<CS230::Camera>()->GetPosition().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2,GetPosition().y });
	}
}

math::vec2 Hero::Get_Hero_Position()
{
	return GameObject::GetPosition();
}

void Hero::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		UpdateVelocity(math::vec2{ -(Acceleration_x * dt), 0 });
		if (GetVelocity().x < -Max_Velocity_x)
		{
			SetVelocity(math::vec2{ -(Max_Velocity_x), GetVelocity().y });
		}
	}
	if (moveRightKey.IsKeyDown() == true)
	{
		UpdateVelocity(math::vec2{ Acceleration_x * dt, 0 });
		if (GetVelocity().x > Max_Velocity_x)
		{
			SetVelocity(math::vec2{ Max_Velocity_x, GetVelocity().y });
		}
	}

	if (moveLeftKey.IsKeyDown() == false && moveRightKey.IsKeyDown() == false)
	{
		if (GetVelocity().x < 0)
		{
			UpdateVelocity(math::vec2{ Drag_x * dt, 0 });
			if (GetVelocity().x > 0)
			{
				SetVelocity(math::vec2{ 0, GetVelocity().y });
			}
		}
		else if (GetVelocity().x > 0)
		{
			UpdateVelocity(math::vec2{ -(Drag_x * dt), 0 });
			if (GetVelocity().x < 0)
			{
				SetVelocity(math::vec2{ 0, GetVelocity().y });
			}
		}
	}
}

void Hero::State_Idle::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
}
void Hero::State_Idle::Update(GameObject*, double )
{
}
void Hero::State_Idle::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveJumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->moveLeftKey.IsKeyDown() == true || hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

void Hero::State_Running::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->SetScale(math::vec2{ -1,1 });
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->SetScale(math::vec2{ 1,1 });
	}
}
void Hero::State_Running::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}
void Hero::State_Running::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveJumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->GetVelocity().x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x > 0)
		{
			hero->ChangeState(&hero->stateSkidding);
		}
	}
	if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x < 0)
		{
			hero->ChangeState(&hero->stateSkidding);
		}
	}
}

void Hero::State_Skidding::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}
void Hero::State_Skidding::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetVelocity().x > 0)
	{
		hero->UpdateVelocity(math::vec2{ -(Drag_x * 2 * dt), 0 });
	}
	else if (hero->GetVelocity().x < 0)
	{
		hero->UpdateVelocity(math::vec2{ Drag_x * 2 * dt, 0 });
	}
}
void Hero::State_Skidding::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveJumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x <= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x >= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveLeftKey.IsKeyDown() == false && hero->moveRightKey.IsKeyDown() == false)
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

void Hero::State_Jumping::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->SetVelocity(math::vec2{ hero->GetVelocity().x, Hero::Jump_Velocity });//Set the velocity.y
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity(math::vec2{ 0, -(Engine::GetGSComponent<Gravity>()->GetValue() * dt) });//Apply Gravity
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}
void Hero::State_Jumping::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveJumpKey.IsKeyDown() == false) {  //Jump Key not pressed
		hero->SetVelocity(math::vec2{ hero->GetVelocity().x, 0 });
	}
	if (hero->GetVelocity().y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}
void Hero::State_Falling::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity(math::vec2{ 0, -(Engine::GetGSComponent<Gravity>()->GetValue() * dt) });
	hero->UpdateXVelocity(dt);
}
void Hero::State_Falling::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetPosition().y <= Level1::floor)
	{
		hero->SetVelocity(math::vec2{ hero->GetVelocity().x, 0 });
		hero->SetPosition(math::vec2{ hero->GetPosition().x,  Level1::floor });

		if (hero->GetVelocity().x > 0)
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
		else if (hero->GetVelocity().x < 0)
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