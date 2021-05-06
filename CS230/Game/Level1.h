/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.h
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"				// InputKey
#include "Background.h"						// Background
#include "..\Engine\Camera.h"				// Camera
#include "..\Engine\GameObjectManager.h"	// GameObjectManager
#include "..\Engine\Texture.h"				// Texture

class Hero;

class Level1 : public CS230::GameState {
public:
	Level1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() override { return "Level 1"; }

	static constexpr double floor = 126.0f;
	void Draw() override;
private:
	int lives;
	CS230::Texture livesTexture;

	CS230::InputKey mainMenu;
	CS230::InputKey levelReload;
	CS230::InputKey slowMotion;
	Hero* heroPtr;
};