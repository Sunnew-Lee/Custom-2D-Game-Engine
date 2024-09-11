/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include <stdexcept>	//std::exception
#include <iostream>		//std::cerr

#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/Level1.h"
#include "Game/Level2.h"
#include "Game/My_Game.h"
#include "Game/Screens.h"
#include "Game/MainMenu.h"


int main(void) {
	try {
		Engine& engine = Engine::Instance();
		engine.Init("Final");
		Splash splash;
		MainMenu mainmenu;
		Level1 level1;
		Level2 level2;
		My_Game my_game;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mainmenu);
		engine.GetGameStateManager().AddGameState(level1);
		engine.GetGameStateManager().AddGameState(level2);
		engine.GetGameStateManager().AddGameState(my_game);
		engine.AddSpriteFont("assets/font.png");
		engine.AddSpriteFont("assets/font2.png");

		while (engine.HasGameEnded() == false) {
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	} catch (std::exception& e) {
		std::cerr << e.what() << "\n";
		return -1;
	}
}