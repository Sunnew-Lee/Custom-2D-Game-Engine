/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.h
Project: CS230
Author: Kevin Wright
Creation date: 6/14/2021
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\GameObject.h"
#include "..\Engine\Sprite.h"

enum class GameObjectType;

class BadRobot : public CS230::GameObject {
public:
	BadRobot(GameObject* player);
	void Update(double dt);
	void Draw(math::TransformMatrix displayMatrix);

	GameObjectType GetObjectType() override;
	std::string GetObjectTypeName() override;
	bool CanCollideWith(GameObjectType collideAgainstType) override;
	void ResolveCollision(GameObject* collidedWith);

	bool IsDead() { return isDead; }
private:
	int counter;
	static constexpr double respawn_time = 3;
	int life;
	int rand_time;
	double life_time;
	double timer;
	GameObject* player;
	bool isDead;
};