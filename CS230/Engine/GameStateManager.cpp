/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/07/2021
-----------------------------------------------------------------*/
#include "GameStateManager.h"
#include "GameState.h"			// GetName(), Load(), Update(), Unload()
#include "Engine.h"				// GetLogger(), GetTextureManager()

CS230::GameStateManager::GameStateManager()
{
	GameStateManager::currGameState = nullptr;
	GameStateManager::nextGameState = nullptr;
	GameStateManager::state = State::START;
}
void CS230::GameStateManager::AddGameState(GameState& gameState)
{
	GameStateManager::gameStates.push_back(&gameState);
}
void CS230::GameStateManager::SetNextState(int initState)
{
	GameStateManager::nextGameState = GameStateManager::gameStates[initState];
}
void CS230::GameStateManager::Shutdown()
{
	GameStateManager::nextGameState = nullptr;
}
void CS230::GameStateManager::ReloadState()
{
	GameStateManager::state = State::UNLOAD;
}
void CS230::GameStateManager::Update(double dt)
{
	switch (GameStateManager::state)
	{
	case State::START:
		if (GameStateManager::gameStates.empty() == true)
		{
			Engine::GetLogger().LogError("No States!");
			GameStateManager::state = State::SHUTDOWN;
		}
		else
		{
			GameStateManager::nextGameState = GameStateManager::gameStates[0];
			GameStateManager::state = State::LOAD;
		}
		break;

	case State::LOAD:
		GameStateManager::currGameState = GameStateManager::nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		GameStateManager::currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		GameStateManager::state = State::UPDATE;
		break;

	case State::UPDATE:
		if (GameStateManager::currGameState != GameStateManager::nextGameState)
		{
			GameStateManager::state = State::UNLOAD;
		}
		else
		{
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());
			GameStateManager::currGameState->Update(dt);
			GameStateManager::currGameState->Draw();
		}
		break;

	case State::UNLOAD:
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		GameStateManager::currGameState->Unload();

		if (GameStateManager::currGameState != GameStateManager::nextGameState)
		{
			Engine::GetTextureManager().Unload();
		}

		if (GameStateManager::nextGameState == nullptr)
		{
			GameStateManager::state = State::SHUTDOWN;
		}
		else
		{
			GameStateManager::state = State::LOAD;
		}
		break;

	case State::SHUTDOWN:
		GameStateManager::state = State::EXIT; break;

	case State::EXIT:break;

	default:break;
	}
}