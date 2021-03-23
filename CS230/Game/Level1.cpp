/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	// GetWindow(), GetGameStateManager()
#include "Screens.h"			// Screens::Level2
#include "Level1.h"


Level1::Level1() 
	: levelNext(CS230::InputKey::Keyboard::Enter), levelReload(CS230::InputKey::Keyboard::R),
	hero(math::vec2(static_cast<double>(Engine::GetWindow().GetSize().x/2),floor)),
	ball(math::vec2(600, floor))
{}

void Level1::Load() {
	hero.Load();
	ball.Load();
	background.Load("assets/Background.png");
}
void Level1::Update(double dt) {
	hero.Update(dt);
	ball.Update(dt);
	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level1::Unload() {
}

void Level1::Draw()
{
	background.Draw(0);
	hero.Draw();
	ball.Draw();
}
