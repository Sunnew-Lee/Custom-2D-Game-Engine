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
#include "..\Engine\Engine.h"			// GetWindow(), GetGSComponent()
#include "Flame_Anims.h"				// Flame_Anim
#include "ScreenWrap.h"					// ScreenWrap
#include "..\Engine\Collision.h"		// CircleCollision
#include "..\Engine\ShowCollision.h"	// ShowCollision
#include "GameObjectTypes.h"			// GameObjectType::Ship
#include "Ship_Anims.h"					// Ship_Anim::Explode_Anim

Ship::Ship(math::vec2 startPos)
	:GameObject(startPos, 0, {0.75,0.75}), is_accelerating{ false }, sprite_flame_1("assets/flame.spt", this), sprite_flame_2("assets/flame.spt", this), isDead(false),
	rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W)
{
	AddGOComponent(new CS230::Sprite("assets/Ship.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
}

void Ship::Update(double dt)
{
	if (IsDead() == false)
	{
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
	}

	UpdateVelocity(-(GetVelocity() * Ship::drag * dt));
	UpdatePosition(GetVelocity() * dt);

	sprite_flame_1.Update(dt);
	sprite_flame_2.Update(dt);
	UpdateGOComponents(dt);
}

void Ship::Draw(math::TransformMatrix cameraMatrix)
{
	sprite_flame_1.Draw(cameraMatrix * GetMatrix() * math::TranslateMatrix::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	sprite_flame_2.Draw(cameraMatrix * GetMatrix() * math::TranslateMatrix::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	GetGOComponent<CS230::Sprite>()->Draw(cameraMatrix * GetMatrix());

	if (Engine::GetGSComponent<ShowCollision>() != nullptr)
	{
		if (Engine::GetGSComponent<ShowCollision>()->IsEnabled() == true)
		{
			if (GetGOComponent<CS230::Collision>() != nullptr)
			{
				GetGOComponent<CS230::Collision>()->Draw(cameraMatrix);
			}
		}
	}
}

GameObjectType Ship::GetObjectType()
{
	return GameObjectType::Ship;
}

std::string Ship::GetObjectTypeName()
{
	return std::string("Ship");
}

bool Ship::CanCollideWith(GameObjectType )
{
	return true;
}

void Ship::ResolveCollision(CS230::GameObject* )
{

	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
	RemoveGOComponent<CS230::Collision>();
	sprite_flame_1.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	sprite_flame_2.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	isDead = true;
}
