/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 5/03/2021
-----------------------------------------------------------------*/
#include "ScreenWrap.h"
#include "..\Engine\GameObject.h"		// GetGOComponent()
#include "..\Engine\Engine.h"			// GetWindow()
#include "..\Engine\Sprite.h"			// Sprite

void ScreenWrap::Update(double)
{
	const double hotspot_x = object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2;
	const double hotspot_y = object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2;

	if (object.GetPosition().x + hotspot_x < 0)
	{
		object.SetPosition(math::vec2{ Engine::GetWindow().GetSize().x + hotspot_x ,object.GetPosition().y });
	}

	if (object.GetPosition().x > Engine::GetWindow().GetSize().x + hotspot_x)
	{
		object.SetPosition(math::vec2{ -hotspot_x ,object.GetPosition().y });
	}

	if (object.GetPosition().y + hotspot_y < 0)
	{
		object.SetPosition(math::vec2{ object.GetPosition().x,Engine::GetWindow().GetSize().y + hotspot_y });
	}

	if (object.GetPosition().y > Engine::GetWindow().GetSize().y + hotspot_y)
	{
		object.SetPosition(math::vec2{ object.GetPosition().x,-hotspot_y });
	}
}
