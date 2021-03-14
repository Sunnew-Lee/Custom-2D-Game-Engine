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

Hero::Hero(math::vec2 startPos)
	:startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right)
{}

void Hero::Load()
{
	sprite.Load("assets/Hero.png", math::ivec2{56,14});
	position = startPos;
}

void Hero::Update()
{
	if (moveLeftKey.IsKeyDown())
	{
		position.x -= 5.;
	}
	if (moveRightKey.IsKeyDown())
	{
		position.x += 5.;
	}
}

void Hero::Draw()
{
	sprite.Draw(position);
}
