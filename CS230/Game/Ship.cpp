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
#include "..\Engine\Engine.h"   // GetWindow()
#include "Flame_Anims.h"		// Flame_Anim

Ship::Ship(math::vec2 startPos)
	:startPos(startPos), position(startPos), velocity(0), cur_rotation(0), is_accelerating{ false },
	rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W)
{}

void Ship::Load()
{
	sprite.Load("assets/Ship.spt");
	sprite_flame_1.Load("assets/flame.spt");
	sprite_flame_2.Load("assets/flame.spt");
	position = startPos;
	velocity = 0;
	cur_rotation = 0;
	is_accelerating = false;
}

void Ship::Update(double dt)
{
	sprite.Update(dt);
	sprite_flame_1.Update(dt);
	sprite_flame_2.Update(dt);
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
			sprite_flame_1.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			sprite_flame_2.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			is_accelerating = true;
		}
		velocity += math::RotateMatrix::RotateMatrix(cur_rotation) * math::vec2(0, accel * dt);
	}
	else if (accelerateKey.IsKeyReleased() == true)
	{
		sprite_flame_1.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		sprite_flame_2.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
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
	const double hotspot_x = sprite.GetFrameSize().x / 2;
	const double hotspot_y = sprite.GetFrameSize().y / 2;

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
