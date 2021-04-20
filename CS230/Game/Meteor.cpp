/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 4/18/2021
-----------------------------------------------------------------*/
#include "Meteor.h"
#include "..\Engine\Engine.h"	// GetWindow()

Meteor::Meteor() : GameObject({ 0, 0 }) {
	constexpr double PI{3.1415926535};
	sprite.Load("assets/Meteor.spt");

	// vec2{ (0~window_size.x), (0~window_size.y) }
	SetPosition(math::vec2{ static_cast<double>(rand() % (Engine::GetWindow().GetSize().x + 1)), static_cast<double>(rand() % (Engine::GetWindow().GetSize().y + 1)) });
	// (rand() % (1024 + 1)) / 512.0)			==> (0~1024)/512.0 ==> 0~2.0
	SetRotation(PI * ((rand() % (1024 + 1)) / 512.0));
	// rand() % ((100 + 1) - (-100)) + (-100)	==> (0~200) - 100 ==> -100~100
	SetVelocity(math::vec2{ static_cast<double>((rand() % 201) - 100), static_cast<double>((rand() % 201) - 100) });
	// (rand() % (1024+1) / 4096.0) + 0.75		==> (0~1024)/4096.0 + 0.75 ==> (0~0.25) + 0.75 ==> 0.75~1.0 
	SetScale(math::vec2{ (rand() % (1024+1) / 4096.0) + 0.75 });

}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	TestForWrap();
}

void Meteor::TestForWrap()
{
	const double hotspot_x = sprite.GetFrameSize().x / 2;
	const double hotspot_y = sprite.GetFrameSize().y / 2;

	if (GetPosition().x + hotspot_x < 0)
	{
		SetPosition(math::vec2{ Engine::GetWindow().GetSize().x + hotspot_x ,GetPosition().y });
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
