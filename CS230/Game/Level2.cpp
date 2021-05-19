/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"			// GetWindow(), GetGameStateManager()
#include "Level2.h"
#include "Ship.h"						// Ship
#include "Meteor.h"						// Meteor
#include "Fonts.h"						// Fonts::Font2
#include "Screens.h"					// Screens::MainMenu
#include "Score.h"						// Score
#include "..\Engine\ShowCollision.h"	// ShowCollision

Level2::Level2() 
	: shipPtr(nullptr), mainMenu(CS230::InputKey::Keyboard::Escape), levelReload(CS230::InputKey::Keyboard::R), slowMotion(CS230::InputKey::Keyboard::Space)
{}

void Level2::Load() {
	AddGSComponent(new CS230::GameObjectManager()); 
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	CS230::GameObjectManager* GOM = GetGSComponent<CS230::GameObjectManager>();

	GOM->Add(new Meteor());
	GOM->Add(new Meteor());
	GOM->Add(new Meteor());
	GOM->Add(new Meteor());
	GOM->Add(new Meteor());
	shipPtr = new Ship({ Engine::GetWindow().GetSize() / 2.0 });
	GOM->Add(shipPtr);
	
	GameOverTexture=Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, false);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, false);
	AddGSComponent(new Score(0,Fonts::Font2));
}
void Level2::Update(double dt) {
#ifdef _DEBUG
	(slowMotion.IsKeyDown() == true) ? (dt /= 8) : (dt);
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
	GetGSComponent<CS230::GameObjectManager>()->Update(dt);
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#else
	if (shipPtr->IsDead() == true)
	{
		if (levelReload.IsKeyReleased() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}
#endif
}
void Level2::Unload() {
	ClearGSComponent();
	shipPtr = nullptr;
}

void Level2::Draw()
{
	Engine::GetWindow().Clear(0x000000ff);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	math::TransformMatrix I_Matrix{};
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(I_Matrix);
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y });
	if (shipPtr->IsDead() == true)
	{
		GameOverTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, static_cast<int>(winSize.y * 0.55) - GameOverTexture.GetSize().y - 5 }));
		RestartTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - RestartTexture.GetSize().x / 2, static_cast<int>(winSize.y * 0.45) - RestartTexture.GetSize().y - 5 }));
	}
}
