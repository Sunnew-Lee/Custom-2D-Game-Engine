/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 05/20/2021
-----------------------------------------------------------------*/

#include "Laser.h"
#include "..\Engine\Sprite.h"		// Sprite
#include "..\Engine\Engine.h"		// GetWindow()

Laser::Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 laserVelocity) :GameObject(pos, rotation, scale)
{
	AddGOComponent(new CS230::Sprite("assets/Laser.spt", this));
	this->SetVelocity( laserVelocity );
}

void Laser::Update(double dt)
{
	GameObject::Update(dt);
	const double hotspot_x = this->GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2;
	const double hotspot_y = this->GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2;

	if (this->GetPosition().x + hotspot_x < 0 || this->GetPosition().x > Engine::GetWindow().GetSize().x + hotspot_x ||
		this->GetPosition().y + hotspot_y < 0 || this->GetPosition().y > Engine::GetWindow().GetSize().y + hotspot_y)
	{
		this->Set_Using_Object(false);
	}

}

bool Laser::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Meteor || objectBType == GameObjectType::EnemyShip)
	{
		return true;
	}
	return false;
}

void Laser::ResolveCollision(GameObject* objectB)
{
	objectB->ResolveCollision(this);
	this->Set_Using_Object(false);
}
