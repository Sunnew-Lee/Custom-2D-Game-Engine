/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 4/27/2021
-----------------------------------------------------------------*/
#include "MainMenu.h"
#include "..\Engine\Engine.h"
#include "Fonts.h"
#include "Screens.h"//?

MainMenu::MainMenu():selectedIndex(0), upKey(CS230::InputKey::Keyboard::Up), downKey(CS230::InputKey::Keyboard::Down), selectKey(CS230::InputKey::Keyboard::Enter)
{}

MainMenu::OptionData MainMenu::optionsData[static_cast<int>(MainMenu::Options::Count)] = {
	{"Side Scroller", {0.5, 0.45}, {} },
	{"Space Shooter", {0.5, 0.35}, {} },
	{"Quit", {0.5, 0.25}, {} },
};

void MainMenu::Load() {
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("CS230 Project", 0xFFFFFFFF, true);
	for (OptionData& data : optionsData) {
		RenderOption(data, false);
	}
	selectedIndex = static_cast<int>(Options::Level1);
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Update(double )
{
	if (upKey.IsKeyReleased() == true)
	{
		if (selectedIndex > 0)
		{
			RenderOption(optionsData[selectedIndex], false);
			selectedIndex--;
			RenderOption(optionsData[selectedIndex], true);
		}
	}
	if (downKey.IsKeyReleased() == true)
	{
		if (selectedIndex < 2)
		{
			RenderOption(optionsData[selectedIndex], false);
			selectedIndex++;
			RenderOption(optionsData[selectedIndex], true);
		}
	}
	if (selectKey.IsKeyReleased() == true)
	{
		switch (selectedIndex)
		{
		case 0:
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level1)); break;
		case 1:
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2)); break;
		case 2:
			Engine::GetGameStateManager().Shutdown(); break;
		}
	}
}

void MainMenu::Unload()
{}

void MainMenu::Draw()
{
	math::ivec2 a = Engine::GetWindow().GetSize();

	Engine::GetWindow().Clear(0x3399daff);
	title.Draw(math::TranslateMatrix(math::vec2{ a.x / 2. - title.GetSize().x,a.y * 0.7 }) * math::ScaleMatrix(math::vec2{ 2,2 }));
	for (MainMenu::OptionData t : optionsData)
	{
		t.texture.Draw(math::TranslateMatrix(math::vec2{ a.x * t.positionPercent.x - t.texture.GetSize().x / 2,a.y * t.positionPercent.y }));
	}
}

void MainMenu::RenderOption(OptionData& data, bool isHighlighted) {
	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(
		data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}
