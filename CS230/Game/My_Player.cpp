/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"    //Engine::GetWindow
#include "../Engine/TransformMatrix.h"
#include "../Engine/Sprite.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"
#include "My_Player.h"
#include "Ammo.h"
#include "Flame_Anims.h"
#include "Ship_Anims.h"
#include "ScreenWrap.h"
#include "doodle/environment.hpp"
#include "Life.h"
#include "Score.h"

My_Player::My_Player(math::vec2 pos) : GameObject(pos, 0, { 2, 2 }), timer(10), counter(0),
moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right),
fireLazerKey(CS230::InputKey::Keyboard::Up), hurtTimer(0), draw_player(true), power(1), isDead(false) {
	AddGOComponent(new CS230::Sprite("assets/my_player.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
}

void My_Player::Update(double dt) {
	timer += dt;

	if (hurtTimer > 0) {
		hurtTimer -= dt;
		draw_player = !draw_player;
		if (hurtTimer <= 0) {
			hurtTimer = 0;
			draw_player = true;
		}
	}

	if (IsDead() == false) {
		if (counter >= 5)
		{
			Engine::GetGSComponent<Life>()->DecreseLife();
			counter = 0;
		}
		if (moveLeftKey.IsKeyDown() == true) {
			UpdateVelocity({ -accel * dt, 0 });		// apply acceleration
			if (GetVelocity().x < -maxXVelocity) {
				SetVelocity({ -maxXVelocity, GetVelocity().y });
			}
		}
		else if (moveRightKey.IsKeyDown() == true) {
			UpdateVelocity({ accel * dt, 0 });		// apply acceleration
			if (GetVelocity().x > maxXVelocity) {
				SetVelocity({ maxXVelocity, GetVelocity().y });
			}
		}
		
		if (fireLazerKey.IsKeyDown() == true && timer>Delay_time) {
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(
				new Ammo(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)),
					GetRotation(), GetScale() * power, math::RotateMatrix(GetRotation()) * Ammo::AmmoVelocity));
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(
				new Ammo(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)),
					GetRotation(), GetScale() * power, math::RotateMatrix(GetRotation()) * Ammo::AmmoVelocity));
			timer = 0;
		}
	}
	SetVelocity(GetVelocity() - GetVelocity() * My_Player::drag * dt);
	UpdatePosition(GetVelocity() * dt);

	UpdateGOComponents(dt);
}

void My_Player::Draw(math::TransformMatrix cameraMatrix) {
	if (draw_player == true)
	{
		CS230::GameObject::Draw(cameraMatrix);
	}
	
}

bool My_Player::CanCollideWith(GameObjectType objectBType) {
	if (objectBType == GameObjectType::Floor || objectBType == GameObjectType::BallRobot) {
		return true;
	}
	else {
		return false;
	}
}

void My_Player::ResolveCollision(CS230::GameObject* objectB) {
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 PlayerRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType()) {
	case GameObjectType::Floor:
		if (PlayerRect.Left() < collideRect.Left()) {
			UpdatePosition(math::vec2{ (collideRect.Left() - PlayerRect.Right()), 0.0 });
			SetVelocity({ 0, GetVelocity().y });
		}
		else {
			UpdatePosition(math::vec2{ (collideRect.Right() - PlayerRect.Left()), 0.0 });
			SetVelocity({ 0, GetVelocity().y });
		}
		break;
	case GameObjectType::PowerUp:
		objectB->Destroy();
		power++;
		break;
	case GameObjectType::Money:
		Engine::GetGSComponent<Score>()->AddScore(500);
		objectB->Destroy();
		break;
	case GameObjectType::Heart:
		Engine::GetGSComponent<Life>()->IncreseLife();
		objectB->Destroy();
		break;
	case GameObjectType::BallRobot:
		Engine::GetGSComponent<Life>()->DecreseLife();
		hurtTimer = 2;
		if (Engine::GetGSComponent<Life>()->GetLife() <= 0)
		{
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
			RemoveGOComponent<CS230::Collision>();
			isDead = true;
		}
		break;
	}
}