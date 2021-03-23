/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "Input.h"
#include "Engine.h"	// GetInput()

CS230::InputKey::InputKey(Keyboard button)
{
	InputKey::button = button;
}
bool CS230::InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(button);
}
bool CS230::InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(button);
}
CS230::Input::Input()
{
	Input::keyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
	Input::wasKeyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
}
void CS230::Input::Update()
{
	Input::wasKeyDown = Input::keyDown;
}
bool CS230::Input::IsKeyDown(InputKey::Keyboard key) const
{
	return Input::keyDown[static_cast<int>(key)];
}
bool CS230::Input::IsKeyReleased(InputKey::Keyboard key) const
{
	if ((Input::wasKeyDown[static_cast<int>(key)]==true) && (Input::keyDown[static_cast<int>(key)]==false))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void CS230::Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	Input::keyDown[static_cast<int>(key)] = value;
}