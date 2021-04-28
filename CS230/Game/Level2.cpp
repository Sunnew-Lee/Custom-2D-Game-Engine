/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	// GetWindow(), GetGameStateManager()
#include "Level2.h"
#include "Ship.h"				// Ship
#include "Meteor.h"				// Meteor
#include "Fonts.h"
#include "Screens.h"

Level2::Level2() 
	: Score(0), mainMenu(CS230::InputKey::Keyboard::Escape), levelReload(CS230::InputKey::Keyboard::R), slowMotion(CS230::InputKey::Keyboard::Space)
{}

void Level2::Load() {
	gameObjectManager.Add(new Ship({ Engine::GetWindow().GetSize() / 2.0 }));
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());

	Score = 0;
	std::string scoreString = "Score: " + std::to_string(Score / 100) + std::to_string((Score % 100) / 10) + std::to_string(Score % 10);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture(scoreString, 0xFFFFFFFF, false);
}
void Level2::Update(double dt) {
#ifdef _DEBUG
	(slowMotion.IsKeyDown() == true) ? (dt /= 8) : (dt);
#endif
	gameObjectManager.UpdateAll(dt);
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level2::Unload() {
	gameObjectManager.Unload();
}

void Level2::Draw()
{
	Engine::GetWindow().Clear(0x000000ff);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	scoreTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, winSize.y - scoreTexture.GetSize().y - 5 }));
	math::TransformMatrix I_Matrix{};
	gameObjectManager.DrawAll(I_Matrix);
}
