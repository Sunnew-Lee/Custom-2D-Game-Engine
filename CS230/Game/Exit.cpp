/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Exit.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 05/20/2021
-----------------------------------------------------------------*/
#include "Exit.h"
#include "..\Engine\Rect.h"			// math::irect
#include "..\Engine\Engine.h"		// GetGameStateManager()
#include "Screens.h"				// Screens::MainMenu
#include "..\Engine\Collision.h"	// RectCollision

Exit::Exit(math::irect2 rect) :GameObject(rect.point1)
{
	math::irect2 rect_new{ math::ivec2{ 0 }, rect.Size() };
	this->AddGOComponent(new CS230::RectCollision(rect_new, this));
}

void Exit::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}
