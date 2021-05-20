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
#include "..\Engine\Engine.h"				// GetWindow()
#include "ScreenWrap.h"						// ScreenWrap
#include "..\Engine\Sprite.h"				// Sprite
#include "GameObjectTypes.h"				// GameObjectType::Laser
#include "..\Engine\GameObjectManager.h"	// CS230::GameObjectManager
#include "Meteor_Anims.h"					// Meteor_Anim::Fade_Anim
#include "..\Engine\Collision.h"			// CS230::Collision
#include "Score.h"							// Score

Meteor::Meteor() : GameObject({ 0, 0 }), health(100), size(1)
{
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));

	// vec2{ (0~window_size.x), (0~window_size.y) }
	SetPosition(math::vec2{ static_cast<double>(rand() % (Engine::GetWindow().GetSize().x + 1)), static_cast<double>(rand() % (Engine::GetWindow().GetSize().y + 1)) });
	// (rand() % (1024 + 1)) / 512.0)			==> (0~1024)/512.0 ==> 0~2.0
	SetRotation(PI * ((rand() % (1024 + 1)) / 512.0));
	// rand() % ((100 + 1) - (-100)) + (-100)	==> (0~200) - 100 ==> -100~100
	SetVelocity(math::vec2{ static_cast<double>((rand() % 201) - 100), static_cast<double>((rand() % 201) - 100) });
	// (rand() % (1024+1) / 4096.0) + 0.75		==> (0~1024)/4096.0 + 0.75 ==> (0~0.25) + 0.75 ==> 0.75~1.0 
	SetScale(math::vec2{ (rand() % (1024 + 1) / 4096.0) + 0.75 });
	this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
}

Meteor::Meteor(Meteor& original) : GameObject(original.GetPosition()), health(100), size(original.size + 1)
{
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));

	SetRotation(original.GetRotation());
	SetVelocity(original.GetVelocity());
	switch (size)
	{
	case 2:
		// (rand() % (1024+1) / 4096.0) + 0.5		==> (0~1024)/4096.0 + 0.75 ==> (0~0.25) + 0.5 ==> 0.5~0.75
		SetScale(math::vec2{ (rand() % (1024 + 1) / 4096.0) + 0.5 });
		break;
	case 3:
		// (rand() % (1024+1) / 4096.0) + 0.25		==> (0~1024)/4096.0 + 0.25 ==> (0~0.25) + 0.5 ==> 0.25~0.5
		SetScale(math::vec2{ (rand() % (1024 + 1) / 4096.0) + 0.25 });
		break;
	}
	this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	if (this->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Meteor_Anim::Fade_Anim))
	{
		if (this->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
		{
			this->Set_Using_Object(false);
		}
	}
}

GameObjectType Meteor::GetObjectType()
{
	return GameObjectType::Meteor;
}

std::string Meteor::GetObjectTypeName()
{
	return std::string("Meteor");
}

void Meteor::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Laser)
	{
		this->health -= 10;

		if (this->health <= 0)
		{
			if (this->size != 3)
			{
				Meteor* meteor1(new Meteor(*this));
				Meteor* meteor2(new Meteor(*this));

				meteor1->SetVelocity(math::RotateMatrix::RotateMatrix(PI / 6) * this->GetVelocity());
				meteor2->SetVelocity(math::RotateMatrix::RotateMatrix(-PI / 6) * this->GetVelocity());
				Engine::GetGSComponent<CS230::GameObjectManager>()->Add(meteor1);
				Engine::GetGSComponent<CS230::GameObjectManager>()->Add(meteor2);

				this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
				this->RemoveGOComponent<CS230::Collision>();
				Engine::GetGSComponent<Score>()->AddScore(100 * this->size);
			}
			else if (this->size == 3)
			{
				this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
				this->RemoveGOComponent<CS230::Collision>();
				Engine::GetGSComponent<Score>()->AddScore(100 * this->size);
			}
		}
		else
		{
			this->UpdateVelocity(objectB->GetVelocity() * 0.01);
		}
	}
}
