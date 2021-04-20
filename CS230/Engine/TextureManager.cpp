/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 4/19/2021
-----------------------------------------------------------------*/
#include "TextureManager.h"
#include "Texture.h"		// Texture
#include "Engine.h"			// GetLogger()

CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& filePath)
{
	for (std::pair<const std::filesystem::path, CS230::Texture*> &p : pathToTexture)
	{
		if (p.first == filePath)
		{
			return p.second;
		}
	}

	pathToTexture.insert(std::pair<std::filesystem::path, Texture*>(filePath, new Texture(filePath)));
	return pathToTexture.find(filePath)->second;
}

void CS230::TextureManager::Unload()
{
	Engine::GetLogger().LogEvent("Clear Textures");

	for (std::pair<const std::filesystem::path, CS230::Texture*> &p : pathToTexture)
	{
		delete p.second;
	}
	pathToTexture.clear();
}
