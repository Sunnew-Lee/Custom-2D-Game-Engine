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
#include "GameObjectTypes.h"		// GameObjectType::Hero
#include "Bunny_Anims.h"			// Bunny_Anim::None_Anim
#include "..\Engine\Collision.h"	// Collision
#include "..\Engine\Engine.h"		// Engine::GetGSComponent<>()
#include "Score.h"					// Score

Bunny::Bunny(math::vec2 pos) : GameObject(pos) {
	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
	this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::None_Anim));
}

GameObjectType Bunny::GetObjectType()
{
	return GameObjectType::Bunny;
}

std::string Bunny::GetObjectTypeName()
{
	return std::string("Bunny");
}

void Bunny::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		this->RemoveGOComponent<CS230::Collision>();
		this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
		Engine::GetGSComponent<Score>()->AddScore(100);
	}
}
