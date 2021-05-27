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
#include "Bunny_Anims.h"			// Bunny_Anim::None_Anim
#include "..\Engine\Collision.h"	// Collision
#include "..\Engine\Engine.h"		// Engine::GetGSComponent<>()
#include "Score.h"					// Score
#include "Hero.h"					// heroPtr

Bunny::Bunny(math::vec2 pos, std::vector<double> patrolNodes, Hero* heroPtr) : GameObject(pos), patrolNodes(patrolNodes), heroPtr(heroPtr), currPatrolNode(0) {
	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
	this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
	this->currState = &statePatrol;
	this->currState->Enter(this);
	
}

void Bunny::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		ChangeState(&stateDead);
	}
}

void Bunny::State_Patrol::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);

	if (bunny->currPatrolNode > bunny->patrolNodes.size() - 1)
	{
		bunny->currPatrolNode = 0;
	}

	if (bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode])
	{
		bunny->SetScale(math::vec2{ 1 });
		bunny->SetVelocity(math::vec2{ velocity,0 });

	}
	else if (bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode])
	{
		bunny->SetScale(math::vec2{ -1,1 });
		bunny->SetVelocity(math::vec2{ -velocity,0 });
	}
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
}

void Bunny::State_Patrol::Update(GameObject* object, double)
{
	Bunny* bunny = static_cast<Bunny*>(object);

	if (bunny->GetVelocity().x < 0 && bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode] ||
		bunny->GetVelocity().x > 0 && bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode])
	{
		bunny->currPatrolNode++;
		bunny->ChangeState(&bunny->statePatrol);
	}
}

void Bunny::State_Patrol::TestForExit(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);

	if (bunny->GetVelocity().x > 0 && bunny->heroPtr->GetPosition().y == bunny->GetPosition().y)
	{
		if (bunny->heroPtr->GetPosition().x >= bunny->GetPosition().x && bunny->heroPtr->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode])
		{
			bunny->ChangeState(&bunny->stateAttack);
		}
	}
	else if (bunny->GetVelocity().x < 0 && bunny->heroPtr->GetPosition().y == bunny->GetPosition().y)
	{
		if (bunny->heroPtr->GetPosition().x <= bunny->GetPosition().x && bunny->heroPtr->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode])
		{
			bunny->ChangeState(&bunny->stateAttack);
		}
	}
}

void Bunny::State_Attack::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->SetVelocity(bunny->GetVelocity() * 2);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Attack_Anim));
}

void Bunny::State_Attack::Update(GameObject* object, double )
{
	Bunny* bunny = static_cast<Bunny*>(object);

	if (bunny->GetVelocity().x < 0 && bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode] || 
		bunny->GetVelocity().x > 0 && bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode])
	{
		bunny->currPatrolNode++;
		bunny->ChangeState(&bunny->statePatrol);
	}
}

void Bunny::State_Attack::TestForExit(GameObject* )
{}

void Bunny::State_Dead::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);

	Engine::GetGSComponent<Score>()->AddScore(100);
	bunny->SetVelocity(math::vec2{ 0 });
	bunny->RemoveGOComponent<CS230::Collision>();
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
}

void Bunny::State_Dead::Update(GameObject* , double )
{}

void Bunny::State_Dead::TestForExit(GameObject* )
{}
