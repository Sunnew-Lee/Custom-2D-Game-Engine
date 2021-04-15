/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/15/2021
-----------------------------------------------------------------*/
#include "Ship.h"
#include "..\Engine\Engine.h"   // GetLogger()

Ship::Ship(math::vec2 startPos)
	:startPos(startPos), position(startPos), velocity(0), cur_rotation(0), is_accelerating{ false },
	rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W)
{}

void Ship::Load()
{
	sprite.Load("assets/Ship.png", { math::ivec2(50,41), math::ivec2(-15,-41), math::ivec2(15,-41) });
	sprite_flame_1.Load("assets/flame.png", math::ivec2(8, 16));
	sprite_flame_2.Load("assets/flame.png", math::ivec2(8, 16));
	position = startPos;
	velocity = 0;
	cur_rotation = 0;
}

void Ship::Update(double dt)
{
	if (rotateCounterKey.IsKeyDown() == true)
	{
		cur_rotation += rotate_speed * dt;
	}
	if (rotateClockKey.IsKeyDown() == true)
	{
		cur_rotation += -rotate_speed * dt;
	}
	if (accelerateKey.IsKeyDown() == true)
	{
		if (is_accelerating == false)
		{
			Engine::GetLogger().LogDebug("Accelerating");
			is_accelerating = true;
		}
		velocity += math::RotateMatrix::RotateMatrix(cur_rotation) * math::vec2(0, accel * dt);
	}
	else if (accelerateKey.IsKeyReleased() == true)
	{
		Engine::GetLogger().LogDebug("Stopped Accelerating");
		is_accelerating = false;
	}

	
	velocity -= (velocity * Ship::drag * dt);

	position += velocity * dt;
	TestForWrap();

	objectMatrix = math::TranslateMatrix::TranslateMatrix(position) * math::RotateMatrix::RotateMatrix(cur_rotation) * math::ScaleMatrix::ScaleMatrix(math::vec2(0.75, 0.75));
}

void Ship::Draw()
{
	sprite_flame_1.Draw(objectMatrix * math::TranslateMatrix::TranslateMatrix(sprite.GetHotSpot(1)));
	sprite_flame_2.Draw(objectMatrix * math::TranslateMatrix::TranslateMatrix(sprite.GetHotSpot(2)));
	sprite.Draw(objectMatrix);
}

void Ship::TestForWrap()
{
	const double hotspot_x = sprite.GetTextureSize().x / 2;
	const double hotspot_y = sprite.GetTextureSize().y / 2;

	if (position.x + hotspot_x < 0)
	{
		position.x = Engine::GetWindow().GetSize().x + hotspot_x;
	}

	if (position.x > Engine::GetWindow().GetSize().x + hotspot_x)
	{
		position.x = -hotspot_x;
	}

	if (position.y + hotspot_y < 0)
	{
		position.y = Engine::GetWindow().GetSize().y + hotspot_y;
	}

	if (position.y > Engine::GetWindow().GetSize().y + hotspot_y)
	{
		position.y = -hotspot_y;
	}
}
