/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: My_Player.h
Project: CS230
Author: sunwoo.lee
Creation date: 06/19/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class My_Player : public CS230::GameObject {
public:
	My_Player(math::vec2 startPos);
	void Update(double dt);
	void Draw(math::TransformMatrix displayMatrix);

	GameObjectType GetObjectType() override { return GameObjectType::My_Player; }
	std::string GetObjectTypeName() override { return "My Player"; }
	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(CS230::GameObject* objectB) override;
	bool IsDead() { return isDead; }
	void AddCounter() { counter++; }
	void AddPower() { power++; }
private:
	int counter;
	double timer;
	int power;
	static constexpr double Delay_time = 0.25;
	double hurtTimer;
	bool draw_player;
	bool isDead;
	static constexpr double accel = 600;
	static constexpr double drag = 1;
	static constexpr double maxXVelocity = 750;

	CS230::InputKey fireLazerKey;
	CS230::InputKey moveLeftKey;
	CS230::InputKey moveRightKey;
};