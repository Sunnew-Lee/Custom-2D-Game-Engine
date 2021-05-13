/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 4/18/2021
-----------------------------------------------------------------*/

#include "Bunny.h"
#include "..\Engine\Sprite.h"		// Sprite
#include "GameObjectTypes.h"

Bunny::Bunny(math::vec2 pos) : GameObject(pos) {
	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
}

GameObjectType Bunny::GetObjectType()
{
	return GameObjectType::Bunny;
}

std::string Bunny::GetObjectTypeName()
{
	return std::string("Bunny");
}
