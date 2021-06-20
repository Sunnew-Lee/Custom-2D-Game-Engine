/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: My_Game.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 06/19/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"   //GetWindow, GetGameStateManager
#include "../Engine/ShowCollision.h"
#include "Screens.h"
#include "My_Game.h"
#include "My_Player.h"
#include "BadRobot.h"
#include "Meteor.h"
#include "Fonts.h"
#include "Score.h"
#include "GameParticles.h"
#include "Floor.h"
#include "Life.h"
#include "Block.h"

My_Game::My_Game() : levelReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape), 
playerPtr(nullptr), block_timer(0), badrobot_timer(0), speed(1), screenwrap(0) {}

void My_Game::Load() {
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	CS230::GameObjectManager* gom = new CS230::GameObjectManager();
	AddGSComponent(gom);
	playerPtr = new My_Player({ Engine::GetWindow().GetSize().x / 2.0, Engine::GetWindow().GetSize().y * 0.1 });
	gom->Add(new Floor({ {0, 0}, {90, Engine::GetWindow().GetSize().y} }));
	gom->Add(new Floor({ {1350, 0}, {Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y} }));
	gom->Add(new Floor({ {0, 0}, {Engine::GetWindow().GetSize().x, 1} }));
	gom->Add(new Block(playerPtr));
	BadRobot* enemy = new BadRobot(playerPtr);
	gom->Add(enemy);
	gom->Add(playerPtr);
	AddGSComponent(new Score(0, Fonts::Font2));
	AddGSComponent(new Life(10, Fonts::Font2));
	AddGSComponent(new HitEmitter());
	AddGSComponent(new BlockBitEmitter());
	BackGroundTexture_1 = Engine::GetTextureManager().Load("assets/Background.png");
	BackGroundTexture_2 = Engine::GetTextureManager().Load("assets/Background.png");
	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, false);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, false);
}

void My_Game::Update(double dt) {
	if (speed <= 4)
	{
		speed += 0.0001;
	}
	dt = dt * speed;
	block_timer += dt;
	badrobot_timer += dt;
	if (playerPtr->IsDead() == false) 
	{ 
		screenwrap += 100 * dt; 
		if (block_timer >= block_respawn)
		{
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Block(playerPtr));
			block_timer = 0;
		}
		if (badrobot_timer >= badrobot_respawn)
		{
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new BadRobot(playerPtr));
			badrobot_timer = 0;
		}
	}

	UpdateGSComponents(dt);

	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#else
	if (playerPtr != nullptr && playerPtr->IsDead() == true && levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}

void My_Game::Unload() {
	ClearGSComponent();
	screenwrap = 0;
	block_timer = 0;
	badrobot_timer = 0;
	speed = 1;
	playerPtr = nullptr;
}

void My_Game::Draw() {
	Engine::GetWindow().Clear(0x000000ff);
	if (screenwrap >= Engine::GetWindow().GetSize().y) { screenwrap = 0; }
	BackGroundTexture_1->Draw(math::TranslateMatrix(math::vec2{ 0, -screenwrap }));
	BackGroundTexture_2->Draw(math::TranslateMatrix(math::vec2{ 0, Engine::GetWindow().GetSize().y - screenwrap }));

	math::TransformMatrix camera;
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw({ 10, winSize.y - 5 });
	GetGSComponent<Life>()->Draw({ 10, static_cast<int>(winSize.y * 0.8) - 5 });

	if (playerPtr->IsDead() == true) {
		GameOverTexture.Draw(math::TranslateMatrix(winSize / 2 + math::ivec2{ 0, 30 } - GameOverTexture.GetSize() / 2));
		RestartTexture.Draw(math::TranslateMatrix(winSize / 2 + math::ivec2{ 0, -30 } - RestartTexture.GetSize() / 2));
	}
}