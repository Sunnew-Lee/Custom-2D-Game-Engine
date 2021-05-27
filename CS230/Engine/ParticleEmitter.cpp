/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 05/25/2021
-----------------------------------------------------------------*/
#include "ParticleEmitter.h"
#include "GameObjectManager.h"		// GameObjectManager
#include "Engine.h"					// Engine::GetGSComponent
#include "Sprite.h"					// Sprite

CS230::ParticleEmitter::ParticleEmitter(double lifetime) :lifetime(lifetime), particleIndexToUse(0)
{}

CS230::ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}

void CS230::ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);
	Engine::GetGSComponent<GameObjectManager>()->Add(particleData);
}

void CS230::ParticleEmitter::Emit(int number, math::vec2 position, math::vec2 emitterVelocity, math::vec2 emitVector, double spread)
{
	for (int i{ 0 }; i < number; i++)
	{
		if (particleIndexToUse >= particleMemoryPool.size())
		{
			particleIndexToUse = 0;
		}

		if (particleMemoryPool[particleIndexToUse]->IsAlive() == true)
		{
			Engine::GetLogger().LogError("Potential Issue!: Memory Pool Override");
			return;
		}
		//(rand() % (1024+1) / 1024.0) * spread - spread * 0.5		==> ((0~1024) / 1024.0) * PI/2 - PI/4 ==> (0~PI/2) - PI/4 ==> -PI/4 ~ PI/4
		double rand_spread = ((rand() % (1024 + 1) / 1024.0) * spread) - spread * 0.5;
		math::vec2 particle_vel{ math::RotateMatrix{rand_spread}*emitVector + emitterVelocity };

		//(rand() % (1024+1) / 2048.0) + 0.5		==> ((0~1024) / 2048.0) + 0.5 ==> (0 ~ 0.5) + 0.5 ==> 0.5 ~ 1.0
		particle_vel *= { ((rand() % (1024 + 1) / 2048.0) + 0.5) };
		particleMemoryPool[particleIndexToUse]->Revive(position, particle_vel, lifetime);
		particleIndexToUse++;
	}
}

CS230::ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile): GameObject(), life(0)
{
	AddGOComponent(new CS230::Sprite(spriteFile, this));
}

void CS230::ParticleEmitter::Particle::Revive(math::vec2 Position, math::vec2 Velocity, double Life)
{
	this->life = Life;
	this->SetPosition(Position);
	this->SetVelocity(Velocity);
	this->GetGOComponent<Sprite>()->PlayAnimation(0);
}

void CS230::ParticleEmitter::Particle::Update(double dt)
{
	if (this->IsAlive() == true)
	{
		this->life -= dt;
		GameObject::Update(dt);
	}
}

void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix)
{
	if (this->IsAlive() == true)
	{
		GameObject::Draw(matrix);
	}
}
