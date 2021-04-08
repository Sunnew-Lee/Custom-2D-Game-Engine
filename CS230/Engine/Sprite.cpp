/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/15/2021
-----------------------------------------------------------------*/
#include "Sprite.h"
#include "Engine.h"		// GetLogger()

void CS230::Sprite::Load(const std::filesystem::path& texturePath)
{
	texture.Load(texturePath);
	hotSpotList.push_back(texture.GetSize() / 2);
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, math::ivec2 hotSpotPosition)
{
	texture.Load(texturePath);
	hotSpotList.push_back(hotSpotPosition);
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, std::initializer_list<math::ivec2> hotspots)
{
	texture.Load(texturePath);
	for (math::ivec2 hotspot : hotspots)
	{
		hotSpotList.push_back(hotspot);
	}
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix) {
	texture.Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)));
}

math::ivec2 CS230::Sprite::GetTextureSize()
{
	return texture.GetSize();
}

math::ivec2 CS230::Sprite::GetHotSpot(int index)
{
	if (index > -1 && index < hotSpotList.size())
	{
		return hotSpotList[index];
	}

	Engine::GetLogger().LogError("Not an valid index for hotspot!");
	return math::ivec2(0);
}

