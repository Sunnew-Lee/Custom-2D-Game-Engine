/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"			// GetWindow(), GetGameStateManager()
#include "Screens.h"					// Screens::Level2
#include "Level1.h"
#include "..\Engine\TransformMatrix.h"	// math::TransformMatrix
#include "Hero.h"						// Hero
#include "Ball.h"						// Ball
#include "Bunny.h"						// Bunny
#include "TreeStump.h"					// TreeStump
#include "Fonts.h"


Level1::Level1()
	: score(0),timer(5),lives(3), mainMenu(CS230::InputKey::Keyboard::Escape), levelReload(CS230::InputKey::Keyboard::R), slowMotion(CS230::InputKey::Keyboard::Space), heroPtr(nullptr),
	camera(math::rect2{ math::vec2{Engine::GetWindow().GetSize().x * 0.15, 0},math::vec2{Engine::GetWindow().GetSize().x * 0.35, 0} })/*camera(math::rect2(math::vec2(Engine::GetWindow().GetSize().x * 0.15, 0), math::vec2(Engine::GetWindow().GetSize().x * 0.35, 0)))*/
{}

void Level1::Load() {
	heroPtr = new Hero({ 150, Level1::floor }, camera);
	gameObjectManager.Add(heroPtr);
	gameObjectManager.Add(new Ball({ 600, Level1::floor }));
	gameObjectManager.Add(new Ball({ 2700, Level1::floor }));
	gameObjectManager.Add(new Ball({ 4800, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 1000, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 2000, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 3200, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 3800, Level1::floor }));
	gameObjectManager.Add(new TreeStump({ 300, Level1::floor }, 3));
	gameObjectManager.Add(new TreeStump({ 1200, Level1::floor }, 2));
	gameObjectManager.Add(new TreeStump({ 2200, Level1::floor }, 1));
	gameObjectManager.Add(new TreeStump({ 2800, Level1::floor }, 5));
	gameObjectManager.Add(new TreeStump({ 5100, Level1::floor }, 5));

	background.Add("assets/clouds.png", 4);
	background.Add("assets/Moutains.png", 2);
	background.Add("assets/foreground.png", 1);
	camera.SetPosition(math::vec2(0, 0));
	camera.SetExtent(math::irect2{ math::ivec2(0,0),math::ivec2(background.Size() - Engine::GetWindow().GetSize()) });

	timer = 5;
	score = 0;

	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);

	std::string lifeString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(lifeString, 0xFFFFFFFF, true);

	std::string timerString = "Time: " + std::to_string(static_cast<int>(timer));
	timerTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);

}
void Level1::Update(double dt) {
#ifdef _DEBUG
	(slowMotion.IsKeyDown() == true) ? (dt /= 8) : (dt);
#endif
	int t = static_cast<int>(timer);
	timer -= dt;
	if (t != static_cast<int>(timer))
	{
		std::string timerString = "Time: " + std::to_string(t);
		timerTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);
	}

	if (timer < 0)
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
	gameObjectManager.UpdateAll(dt);

	camera.Update(heroPtr->Get_Hero_Position());

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
	gameObjectManager.Unload();
	background.Unload();
	heroPtr = nullptr;
}

void Level1::Draw()
{
	Engine::GetWindow().Clear(0x3399daff);
	background.Draw(camera);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	scoreTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, winSize.y - scoreTexture.GetSize().y - 5 }));
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - livesTexture.GetSize().x / 2, winSize.y - livesTexture.GetSize().y - 5 }));
	timerTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x - timerTexture.GetSize().x - 10, winSize.y - timerTexture.GetSize().y - 5 }));

	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	gameObjectManager.DrawAll(cameraMatrix);
}
