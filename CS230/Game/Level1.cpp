/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"				// GetWindow(), GetGameStateManager()
#include "Screens.h"						// Screens::MainMenu
#include "Level1.h"
#include "..\Engine\TransformMatrix.h"		// math::TransformMatrix
#include "Hero.h"							// Hero
#include "Ball.h"							// Ball
#include "Bunny.h"							// Bunny
#include "TreeStump.h"						// TreeStump
#include "Fonts.h"							// Fonts::Font1
#include "..\Engine\GameObjectManager.h"	// GameObjectManager
#include "Gravity.h"						// Gravity
#include "Score.h"							// Score
#include "Timer.h"							// Timer
#include "..\Engine\ShowCollision.h"		// ShowCollision

Level1::Level1() : levelReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape), slowMotion(CS230::InputKey::Keyboard::Space), 
					heroPtr(nullptr), lives(3)
{}

void Level1::Load() {
	AddGSComponent(new CS230::GameObjectManager());
	AddGSComponent(new Background());
	AddGSComponent(new Gravity(2000.));
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	CS230::GameObjectManager* GOM = GetGSComponent<CS230::GameObjectManager>();
	Background* BG = GetGSComponent<Background>();

	heroPtr = new Hero({ 150, Level1::floor });
	GOM->Add(heroPtr);

	GOM->Add(new Ball({ 600, Level1::floor }));
	GOM->Add(new Ball({ 2700, Level1::floor }));
	GOM->Add(new Ball({ 4800, Level1::floor }));
	GOM->Add(new Bunny({ 1000, Level1::floor }));
	GOM->Add(new Bunny({ 2000, Level1::floor }));
	GOM->Add(new Bunny({ 3200, Level1::floor }));
	GOM->Add(new Bunny({ 3800, Level1::floor }));
	GOM->Add(new TreeStump({ 300, Level1::floor }, 3));
	GOM->Add(new TreeStump({ 1200, Level1::floor }, 2));
	GOM->Add(new TreeStump({ 2200, Level1::floor }, 1));
	GOM->Add(new TreeStump({ 2800, Level1::floor }, 5));
	GOM->Add(new TreeStump({ 5100, Level1::floor }, 5));

	BG->Add("assets/clouds.png", 4);
	BG->Add("assets/Moutains.png", 2);
	BG->Add("assets/foreground.png", 1);
	
	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0,0 }, { BG->Size() - Engine::GetWindow().GetSize() } });

	AddGSComponent(new Score(0, Fonts::Font1));
	
	std::string lifeString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(lifeString, 0xFFFFFFFF, true);

	AddGSComponent(new Timer(60));
}
void Level1::Update(double dt) {
#ifdef _DEBUG
	(slowMotion.IsKeyDown() == true) ? (dt /= 8) : (dt);
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
	GetGSComponent<Timer>()->Update(dt);
	if (GetGSComponent<Timer>()->hasEnded() == true)
	{
		lives--;
		if (lives == 0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
		else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}

	GetGSComponent<CS230::GameObjectManager>()->Update(dt);

	GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());

	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level1::Unload() {
	ClearGSComponent();
	heroPtr = nullptr;
}

void Level1::Draw()
{
	Engine::GetWindow().Clear(0x3399daff);
	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	GetGSComponent<Background>()->Draw(*cameraPtr);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y });
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - livesTexture.GetSize().x / 2, winSize.y - livesTexture.GetSize().y - 5 }));
	
	GetGSComponent<Timer>()->Draw(math::ivec2{ winSize.x, winSize.y });
	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(cameraMatrix);
}
