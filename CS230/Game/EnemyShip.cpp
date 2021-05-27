/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 05/26/2021
-----------------------------------------------------------------*/
#include "EnemyShip.h"
#include "GameObjectTypes.h"			// GameObjectType::EnemyShip
#include "..\Engine\Collision.h"		// Collision
#include "..\Engine\Sprite.h"			// Spite
#include "..\Engine\Engine.h"			// GetGSComponent
#include "Ship_Anims.h"					// Ship_Anim::None_Anim
#include "Flame_Anims.h"				// Flame_Anim::Flame_Anim
#include "..\Engine\ShowCollision.h"	// ShowCollision
#include "Score.h"						// Score

EnemyShip::EnemyShip(GameObject* player): GameObject(), player(player), flameLeft("assets/flame.spt", this), flameRight("assets/flame.spt", this),isDead(false)
{
	static constexpr double PI{ 3.1415926535 };

	double rotate{ (rand() % (1024 + 1) / 512.0) * PI };
	this->SetRotation(rotate);
	this->SetPosition(player->GetPosition() + math::RotateMatrix(rotate) * math::vec2{ 0,(rand() % (1024 + 1) - 2048.0) });
	AddGOComponent(new CS230::Sprite("assets/EnemyShip.spt", this));
	this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
}

void EnemyShip::Update(double dt)
{
	math::vec2 vecToObject{ this->GetPosition() - player->GetPosition() };
	vecToObject = vecToObject.Normalize();
	math::vec2 enemyship = math::RotateMatrix::RotateMatrix(GetRotation()) * math::vec2{0,1};

	if(vecToObject.Cross(enemyship) > 0.05)
	{
		UpdateRotation(rotationRate * dt);
	}
	else if(vecToObject.Cross(enemyship) < -0.05)
	{
		UpdateRotation(-rotationRate * dt);
	}
	
	UpdateVelocity(math::RotateMatrix::RotateMatrix(GetRotation()) * math::vec2(0, accel * dt));

	UpdateVelocity(-(GetVelocity() * this->drag * dt));
	UpdatePosition(GetVelocity() * dt);

	flameLeft.Update(dt);
	flameRight.Update(dt);
	UpdateGOComponents(dt);
}

void EnemyShip::Draw(math::TransformMatrix displayMatrix)
{
	this->flameLeft.Draw(displayMatrix * GetMatrix() * math::TranslateMatrix::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	this->flameRight.Draw(displayMatrix * GetMatrix() * math::TranslateMatrix::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	this->GetGOComponent<CS230::Sprite>()->Draw(displayMatrix * GetMatrix());

	if (Engine::GetGSComponent<ShowCollision>() != nullptr)
	{
		if (Engine::GetGSComponent<ShowCollision>()->IsEnabled() == true)
		{
			if (GetGOComponent<CS230::Collision>() != nullptr)
			{
				GetGOComponent<CS230::Collision>()->Draw(displayMatrix);
			}
		}
	}
}


GameObjectType EnemyShip::GetObjectType()
{
	return GameObjectType::EnemyShip;
}

std::string EnemyShip::GetObjectTypeName()
{
	return std::string("EnemyShip");
}

bool EnemyShip::CanCollideWith(GameObjectType collideAgainstType)
{
	if (collideAgainstType == GameObjectType::Laser || collideAgainstType == GameObjectType::Ship)
	{
		return true;
	}

	return false;
}

void EnemyShip::ResolveCollision(GameObject* collidedWith)
{
	if (collidedWith->GetObjectType() == GameObjectType::Laser)
	{
		this->RemoveGOComponent<CS230::Collision>();
		this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		Engine::GetGSComponent<Score>()->AddScore(300);
		collidedWith->Set_Using_Object(false);
	}
}