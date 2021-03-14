/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/15/2021
-----------------------------------------------------------------*/
#include "Ship.h"

Ship::Ship(math::vec2 startPos)
	:startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::A), moveRightKey(CS230::InputKey::Keyboard::D), moveUpKey(CS230::InputKey::Keyboard::W), moveDownKey(CS230::InputKey::Keyboard::S)
{}

void Ship::Load()
{
	sprite.Load("assets/Ship.png");
	position = startPos;
}

void Ship::Update()
{
	if (moveLeftKey.IsKeyDown())
	{
		position.x -= 5.;
	}
	if (moveRightKey.IsKeyDown())
	{
		position.x += 5.;
	}
	if (moveUpKey.IsKeyDown())
	{
		position.y += 5.;
	}
	if (moveDownKey.IsKeyDown())
	{
		position.y -= 5.;
	}
}

void Ship::Draw()
{
	sprite.Draw(position);
}
