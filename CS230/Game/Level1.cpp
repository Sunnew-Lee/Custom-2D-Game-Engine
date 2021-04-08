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


Level1::Level1()
	: levelNext(CS230::InputKey::Keyboard::Enter), levelReload(CS230::InputKey::Keyboard::R),
	camera(math::rect2(math::vec2(Engine::GetWindow().GetSize().x * 0.15, 0), math::vec2(Engine::GetWindow().GetSize().x * 0.35, 0))),
	hero(math::vec2(Engine::GetWindow().GetSize().x / 2., floor), camera),
	ball1(math::vec2(600, floor)), ball2(math::vec2(2700, floor)), ball3(math::vec2(4800, floor))
{}

void Level1::Load() {
	hero.Load();
	ball1.Load();
	ball2.Load();
	ball3.Load();
	background.Add("assets/clouds.png",4);
	background.Add("assets/Moutains.png", 2);
	background.Add("assets/foreground.png", 1);
	camera.SetPosition(math::vec2(0,0));
	camera.SetExtent(math::irect2{ math::ivec2(0,0),math::ivec2(background.Size() - Engine::GetWindow().GetSize()) });
}
void Level1::Update(double dt) {
	hero.Update(dt);
	ball1.Update(dt);
	ball2.Update(dt);
	ball3.Update(dt);
	camera.Update(hero.Get_Hero_Position());

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
	background.Unload();
}

void Level1::Draw()
{
	Engine::GetWindow().Clear(0x3399daff);
	background.Draw(camera);

	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	hero.Draw(cameraMatrix);
	ball1.Draw(cameraMatrix);
	ball2.Draw(cameraMatrix);
	ball3.Draw(cameraMatrix);
}
