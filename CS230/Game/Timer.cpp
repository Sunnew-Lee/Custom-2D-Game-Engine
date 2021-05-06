/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 5/03/2021
-----------------------------------------------------------------*/
#include "Timer.h"
#include "..\Engine\Engine.h"	// GetSpriteFont()
#include "Fonts.h"	// Fonts::Font1

Timer::Timer(int time) :timer(time)
{}

void Timer::Update(double dt)
{
	int passed_time = static_cast<int>(timer);
	timer -= dt;
	if (passed_time != static_cast<int>(timer))
	{
		std::string timerString = "Time: " + std::to_string(passed_time);
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);
	}

}

void Timer::Draw(math::ivec2 location)
{
	location -= math::ivec2{ timeTexture.GetSize().x + 10,timeTexture.GetSize().y + 5 };
	timeTexture.Draw(math::TranslateMatrix(location));
}

bool Timer::hasEnded()
{
	if (timer < 0)
	{
		return true;
	}
	return false;
}
