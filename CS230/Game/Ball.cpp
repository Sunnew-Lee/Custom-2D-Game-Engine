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

Ball::Ball(math::vec2 startPos)
	:initPosition(startPos), position(startPos)
{}

void Ball::Load()
{
	sprite.Load("assets/Ball.png", math::ivec2{ 42,0 });
	position = initPosition;
	velocity = 0;
}

void Ball::Update(double dt)
{
	velocity.y -= Level1::gravity * dt;
	position.y += velocity.y * dt;

	if (position.y < Level1::floor)
	{
		position.y = Level1::floor;
		velocity.y = bounceVelocity;
	}
}

void Ball::Draw()
{
	sprite.Draw(position);
}

