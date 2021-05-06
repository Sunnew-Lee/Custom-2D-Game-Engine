/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 04/18/2021
-----------------------------------------------------------------*/
#include "GameObjectManager.h"
#include "..\Engine\TransformMatrix.h"  // math::TransformMatrix
#include "GameObject.h"					// GameObject

CS230::GameObjectManager::~GameObjectManager()
{
	for (GameObject* gameobject : gameObjects)
	{
		delete gameobject;
	}

	gameObjects.clear();
}

void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void CS230::GameObjectManager::Update(double dt)
{
	for (GameObject* gameobject : gameObjects)
	{
		gameobject->Update(dt);
	}
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (GameObject* gameobject : gameObjects)
	{
		gameobject->Draw(cameraMatrix);
	}
}
