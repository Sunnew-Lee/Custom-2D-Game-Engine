/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/23/2021
-----------------------------------------------------------------*/
#include "Background.h"
#include "..\Engine\Camera.h"		// GetPosition()

void Background::Add(const std::filesystem::path& texturePath, int level)
{
	backgrounds.push_back(ParallaxInfo{ texturePath,level });
}

void Background::Unload()
{
	backgrounds.clear();
}

void Background::Draw(const CS230::Camera& camera)
{
	for (Background::ParallaxInfo& p : backgrounds)
	{
		p.texture.Draw(math::TranslateMatrix::TranslateMatrix(math::vec2{ -camera.GetPosition().x / p.level, -camera.GetPosition().y }));
	}
}
	
math::ivec2 Background::Size()
{
	for (Background::ParallaxInfo& p : backgrounds)
	{
		if (p.level == 1)
		{
			return p.texture.GetSize();
		}
	}

	return math::ivec2(0);
}
