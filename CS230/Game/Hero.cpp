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
#include "..\Engine\Engine.h"	// GetLogger()
#include "Level1.h"				// gravity, floor
#include <string>				// to_string()

Hero::Hero(math::vec2 startPos)
	:sprite(), startPos(startPos), position(startPos), velocity(0), isJumping(false), isRising(false),
	moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), moveJumpKey(CS230::InputKey::Keyboard::Up)
{}

void Hero::Load()
{
	sprite.Load("assets/Hero.png", math::ivec2{56,14});
	position = startPos;
	velocity = 0;
	isJumping = false;
	isRising = false;
}

void Hero::Update(double dt)
{

	if (moveLeftKey.IsKeyDown() == true)
	{
		velocity.x -= Acceleration_x * dt;
		if (velocity.x > 0)
		{
			velocity.x -= Drag_x * dt;
			Engine::GetLogger().LogDebug("-Skidding");
		}
		else
		{
			if (velocity.x < -Max_Velocity_x)
			{
				velocity.x = -Max_Velocity_x;
				Engine::GetLogger().LogDebug("-Max velocity");
			}
			else
			{
				Engine::GetLogger().LogDebug("-Accelerating");
			}
		}
	}

	else if (moveRightKey.IsKeyDown() == true)
	{
		velocity.x += Acceleration_x * dt;
		if (velocity.x < 0)
		{
			velocity.x += Drag_x * dt;
			Engine::GetLogger().LogDebug("+Skidding");
		}
		else
		{
			if (velocity.x > Max_Velocity_x)
			{
				velocity.x = Max_Velocity_x;
				Engine::GetLogger().LogDebug("+Max velocity");
			}
			else
			{
				Engine::GetLogger().LogDebug("+Accelerating");
			}
		}
	}

	if (moveLeftKey.IsKeyDown() == false && moveRightKey.IsKeyDown() == false)
	{
		if (velocity.x < 0)
		{
			velocity.x += Drag_x * dt;
			Engine::GetLogger().LogDebug("+Dragging");

			if (velocity.x > 0)
			{
				velocity.x = 0;
				Engine::GetLogger().LogDebug("Stopped");
			}
		}
		else if (velocity.x > 0)
		{
			velocity.x -= Drag_x * dt;
			Engine::GetLogger().LogDebug("-Dragging");

			if (velocity.x < 0)
			{
				velocity.x = 0;
				Engine::GetLogger().LogDebug("Stopped");
			}
		}
	}

	if (isJumping == true)
	{
		velocity.y -= Level1::gravity * dt;
		if (isRising == true)
		{
			if (velocity.y <= 0)
			{
				isRising = false;
				Engine::GetLogger().LogDebug("Top of Jump - YPos:" + std::to_string(position.y));
			}
			if (moveJumpKey.IsKeyReleased() == true)
			{
				velocity.y = 0;
				isRising = false;
				Engine::GetLogger().LogDebug("Top of Jump(Early) - YPos:" + std::to_string(position.y));
			}
		}
	}
	else if (moveJumpKey.IsKeyDown() == true)
	{
		velocity.y = Jump_Velocity;
		isJumping = true;
		isRising = true;
		Engine::GetLogger().LogDebug("Starting Jump - YPos:" + std::to_string(position.y));
	}
	position += velocity * dt;

	if (position.y < Level1::floor)
	{
		velocity.y = 0;
		position.y = Level1::floor;
		isJumping = false;
		Engine::GetLogger().LogDebug("Ending Jump - YPos:" + std::to_string(position.y));
	}

	
}

void Hero::Draw()
{
	sprite.Draw(position);
}
