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
	:startPos(startPos), position(startPos), velocity(0),
	moveLeftKey(CS230::InputKey::Keyboard::A), moveRightKey(CS230::InputKey::Keyboard::D), moveUpKey(CS230::InputKey::Keyboard::W), moveDownKey(CS230::InputKey::Keyboard::S)
{}

void Ship::Load()
{
	sprite.Load("assets/Ship.png");
	position = startPos;
	velocity = 0;
}

void Ship::Update(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		velocity.x -= accel * dt;
	}
	if (moveRightKey.IsKeyDown() == true)
	{
		velocity.x += accel * dt;
	}
	if (moveUpKey.IsKeyDown() == true)
	{
		velocity.y += accel * dt;
	}
	if (moveDownKey.IsKeyDown() == true)
	{
		velocity.y -= accel * dt;
	}

	velocity -= (velocity * Ship::drag * dt);

	Engine::GetLogger().LogDebug("Velocity = " + std::to_string(velocity.x) + "," + std::to_string(velocity.y));
	position += velocity * dt;
	TestForWrap();
}

void Ship::Draw()
{
	sprite.Draw(position);
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
