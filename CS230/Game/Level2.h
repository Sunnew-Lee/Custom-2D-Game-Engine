/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.h
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"				// InputKey
#include "..\Engine\GameObjectManager.h"	// GameObjectManager

class Ship;

class Level2 : public CS230::GameState {
public:
	Level2();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() override { return "Level 2"; }

	void Draw() override;
private:
	Ship* shipPtr;

	CS230::InputKey mainMenu;
	CS230::InputKey levelReload;
	CS230::InputKey slowMotion;
	CS230::Texture GameOverTexture;
	CS230::Texture RestartTexture;
};