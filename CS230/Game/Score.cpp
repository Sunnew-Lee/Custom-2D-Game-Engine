/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 5/03/2021
-----------------------------------------------------------------*/
#include "Score.h"
#include "..\Engine\Engine.h"	// GetSpriteFont()

Score::Score(int startingScore, Fonts fontToUse): score(startingScore),fontToUse(fontToUse)
{}

void Score::AddScore(int newPoints)
{
	score += newPoints;
}

void Score::Draw(math::ivec2 location)
{
	RenderText();
	location.y -= scoreTexture.GetSize().y + 5;
	scoreTexture.Draw(math::TranslateMatrix(location));
}

void Score::RenderText()
{
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}
