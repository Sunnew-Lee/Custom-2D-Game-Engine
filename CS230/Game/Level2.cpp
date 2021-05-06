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
	: mainMenu(CS230::InputKey::Keyboard::Escape), levelReload(CS230::InputKey::Keyboard::R), slowMotion(CS230::InputKey::Keyboard::Space)
{}

void Level2::Load() {
	AddGSComponent(new CS230::GameObjectManager()); 
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	CS230::GameObjectManager* GOM = GetGSComponent<CS230::GameObjectManager>();

	GOM->Add(new Ship({ Engine::GetWindow().GetSize() / 2.0 }));
	GOM->Add(new Meteor());
	GOM->Add(new Meteor());
	GOM->Add(new Meteor());
	GOM->Add(new Meteor());
	GOM->Add(new Meteor());

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
#endif
}
void Level2::Unload() {
	ClearGSComponent();
}

void Level2::Draw()
{
	Engine::GetWindow().Clear(0x000000ff);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y });
	math::TransformMatrix I_Matrix{};
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(I_Matrix);
}
