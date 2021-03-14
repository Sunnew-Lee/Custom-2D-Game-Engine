/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Splash.h"

//Splash::Splash() : levelNext(CS230::InputKey::Keyboard::Enter) {}
Splash::Splash(){}

void Splash::Load() {
	texture.Load("assets/DigiPen_BLACK_1024px.png");
}
void Splash::Update([[maybe_unused]] double dt) {
	static std::chrono::system_clock::time_point start =std::chrono::system_clock::now();
	std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;

	if (sec.count()>=3) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level1));
	}
}
void Splash::Unload() {
}

void Splash::Draw()
{
	Engine::GetWindow().Clear(0xffffffff);
	texture.Draw(static_cast<math::vec2>(math::ivec2(Engine::GetWindow().GetSize() / 2 - texture.GetSize() / 2)));
}
