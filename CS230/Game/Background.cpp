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
#include "..\Engine\Texture.h"      // texturePtr
#include "..\Engine\Engine.h"      // GetTextureManager(), GetGSComponent()

Background::~Background()
{
	backgrounds.clear();
}

void Background::Add(const std::filesystem::path& texturePath, int level)
{
	backgrounds.push_back(ParallaxInfo{ Engine::GetTextureManager().Load(texturePath),level });
}

void Background::Draw(const CS230::Camera& )
{
	CS230::Camera* cameraPtr = Engine::GetGSComponent<CS230::Camera>();
	for (Background::ParallaxInfo& p : backgrounds)
	{
		p.texturePtr->Draw(math::TranslateMatrix::TranslateMatrix(math::vec2{ -cameraPtr->GetPosition().x / p.level, cameraPtr->GetPosition().y }));
	}
}
	
math::ivec2 Background::Size()
{
	for (Background::ParallaxInfo& p : backgrounds)
	{
		if (p.level == 1)
		{
			return p.texturePtr->GetSize();
		}
	}

	return math::ivec2(0);
}
