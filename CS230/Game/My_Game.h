/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: My_Game.h
Project: CS230
Author: sunwoo.lee
Creation date: 06/19/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"

class My_Player;

class My_Game : public CS230::GameState {
public:
	My_Game();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "My Game"; }
private:
	My_Player* playerPtr;
	double screenwrap;
	double block_timer;
	double badrobot_timer;
	double speed;

	static const int block_respawn = 10;
	static const int badrobot_respawn = 5;
	CS230::InputKey levelReload;
	CS230::InputKey mainMenu;

	CS230::Texture* BackGroundTexture_1;
	CS230::Texture* BackGroundTexture_2;
	CS230::Texture GameOverTexture;
	CS230::Texture RestartTexture;
};
