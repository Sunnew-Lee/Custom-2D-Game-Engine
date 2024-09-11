/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "Input.h"
#include "Engine.h"		//GetInput

CS230::Input::Input() {
	keyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
	wasKeyDown.resize(static_cast<int>(InputKey::Keyboard::Count));
}

bool CS230::Input::IsKeyDown(InputKey::Keyboard key) const {
	return keyDown[static_cast<int>(key)];
}

bool CS230::Input::IsKeyReleased(InputKey::Keyboard key) const {
	return keyDown[static_cast<int>(key)] == false && wasKeyDown[static_cast<int>(key)] == true;
}

void CS230::Input::SetKeyDown(InputKey::Keyboard key, bool value) {
	keyDown[static_cast<int>(key)] = value;
}

void CS230::Input::Update() {
	wasKeyDown = keyDown;
}

CS230::InputKey::InputKey(CS230::InputKey::Keyboard button) : button(button) {}

bool CS230::InputKey::IsKeyDown() const {
	return Engine::GetInput().IsKeyDown(button);
}

bool CS230::InputKey::IsKeyReleased() const {
	return Engine::GetInput().IsKeyReleased(button);
}
