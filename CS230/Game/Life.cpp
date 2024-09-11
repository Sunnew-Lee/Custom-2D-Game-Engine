/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Life.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 06/19/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"		//DrawTextToTexture
#include "../Engine/TransformMatrix.h"
#include "../Engine/Vec2.h"
#include "Life.h"
#include "Fonts.h"

Life::Life(int startingLife, Fonts fontToUse) : fontToUse(fontToUse), life(startingLife) {
	RenderText();
}

void Life::IncreseLife() {
	life++;
	RenderText();
}

void Life::DecreseLife() {
	life--;
	RenderText();
}

int Life::GetLife()
{
	return life;
}
void Life::Draw(math::ivec2 location) {
	lifeTexture.Draw(math::TranslateMatrix(location - math::ivec2{ 0, lifeTexture.GetSize().y }));
}

void Life::RenderText() {
	std::string scoreString = "Life: " + std::to_string(life / 100) + std::to_string((life % 100) / 10) + std::to_string(life % 10);
	lifeTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}