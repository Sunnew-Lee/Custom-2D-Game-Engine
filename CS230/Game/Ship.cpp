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
	:GameObject(startPos, 0, {0.75,0.75}), is_accelerating{ false },
	rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W)
{
	sprite.Load("assets/Ship.spt");
	sprite_flame_1.Load("assets/flame.spt");
	sprite_flame_2.Load("assets/flame.spt");
}

void Ship::Update(double dt)
{
	sprite.Update(dt);
	sprite_flame_1.Update(dt);
	sprite_flame_2.Update(dt);

	if (rotateCounterKey.IsKeyDown() == true)
	{
		UpdateRotation(rotate_speed * dt);
	}
	if (rotateClockKey.IsKeyDown() == true)
	{
		UpdateRotation(-(rotate_speed * dt));
	}
	if (accelerateKey.IsKeyDown() == true)
	{
		if (is_accelerating == false)
		{
			sprite_flame_1.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			sprite_flame_2.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			is_accelerating = true;
		}
		UpdateVelocity(math::RotateMatrix::RotateMatrix(GetRotation()) * math::vec2(0, accel * dt));
	}
	else if (accelerateKey.IsKeyReleased() == true)
	{
		sprite_flame_1.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		sprite_flame_2.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		is_accelerating = false;
	}

	UpdateVelocity(-(GetVelocity() * Ship::drag * dt));

	UpdatePosition(GetVelocity() * dt);
	TestForWrap();
}

void Ship::Draw(math::TransformMatrix cameraMatrix)
{
	sprite_flame_1.Draw(cameraMatrix * GetMatrix() * math::TranslateMatrix::TranslateMatrix(sprite.GetHotSpot(1)));
	sprite_flame_2.Draw(cameraMatrix * GetMatrix() * math::TranslateMatrix::TranslateMatrix(sprite.GetHotSpot(2)));
	sprite.Draw(cameraMatrix * GetMatrix());
}

void Ship::TestForWrap()
{
	const double hotspot_x = sprite.GetFrameSize().x / 2;
	const double hotspot_y = sprite.GetFrameSize().y / 2;

	if (GetPosition().x + hotspot_x < 0)
	{
		SetPosition(math::vec2{ Engine::GetWindow().GetSize().x + hotspot_x ,GetPosition().y});
	}

	if (GetPosition().x > Engine::GetWindow().GetSize().x + hotspot_x)
	{
		SetPosition(math::vec2{ -hotspot_x ,GetPosition().y });
	}

	if (GetPosition().y + hotspot_y < 0)
	{
		SetPosition(math::vec2{ GetPosition().x,Engine::GetWindow().GetSize().y + hotspot_y });
	}

	if (GetPosition().y > Engine::GetWindow().GetSize().y + hotspot_y)
	{
		SetPosition(math::vec2{ GetPosition().x,-hotspot_y });
	}
}
