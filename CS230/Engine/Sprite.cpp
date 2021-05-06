/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/15/2021
-----------------------------------------------------------------*/
#include "Sprite.h"		// Sprite
#include "Engine.h"		// GetLogger(), GetTextureManager()
#include "Animation.h"	// Animation
#include "Texture.h"	// texturePtr
#include "GameObject.h"	// AddGOComponent()
#include "Collision.h"	// RectCollision, CircleCollision

CS230::Sprite::Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object)
{
	Load(spriteInfoFile, object);
}

CS230::Sprite::~Sprite() {
	for (Animation* anim : animations) {
		delete anim;
	}
	animations.clear();
}

void CS230::Sprite::Load(const std::filesystem::path& spriteInfoFile, GameObject* object)
{
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() != ".spt") {
		throw std::runtime_error("Bad Filetype.  " + spriteInfoFile.generic_string() + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
	}

	std::string text;
	inFile >> text;
	texturePtr = Engine::GetTextureManager().Load(text);
	frameSize = texturePtr->GetSize();

	inFile >> text;
	while (inFile.eof() == false) {
		if (text == "Anim")
		{
			inFile >> text;
			animations.push_back(new Animation{ text });
		}
		else if (text == "FrameSize") {
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		else if (text == "NumFrames") {
			int numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++) {
				frameTexel.push_back({ frameSize.x * i, 0 });
			}
		}
		else if (text == "Frame") {
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		}
		else if (text == "HotSpot") {
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpotList.push_back({ hotSpotX, hotSpotY });
		}
		else if (text == "CollisionRect") {
			math::irect2 rect;
			inFile >> rect.point1.x >> rect.point1.y >> rect.point2.x >> rect.point2.y;
			if (object == nullptr) {
				Engine::GetLogger().LogError("Trying to add collision to a nullobject");
			}
			else {
				object->AddGOComponent(new RectCollision(rect, object));
			}
		}
		else if (text == "CollisionCircle") {
			double radius;
			inFile >> radius;
			if (object == nullptr) {
				Engine::GetLogger().LogError("Trying to add collision to a nullobject");
			}
			else {
				object->AddGOComponent(new CircleCollision(radius, object));
			}
		}
		else {
			Engine::GetLogger().LogError("Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
	if (animations.empty() == true)
	{
		animations.push_back(new Animation());
	}
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix) {
	texturePtr->Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)), GetFrameTexel(animations[currAnim]->GetDisplayFrame()), GetFrameSize());
}

void CS230::Sprite::PlayAnimation(int anim)
{
	animations[anim]->ResetAnimation();

	if (anim > -1 && anim < animations.size())
	{
		currAnim = anim;
		return;
	}

	Engine::GetLogger().LogError("Not an Valid animation num!");
}

void CS230::Sprite::Update(double dt)
{
	animations[currAnim]->Update(dt);
}

bool CS230::Sprite::IsAnimationDone()
{
	return animations[currAnim]->IsAnimationDone();
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

math::ivec2 CS230::Sprite::GetFrameSize() const
{
	return frameSize;
}

math::ivec2 CS230::Sprite::GetFrameTexel(int frameNum) const
{
	if (frameNum > -1 && frameNum < frameTexel.size())
	{
		return frameTexel[frameNum];
	}

	Engine::GetLogger().LogError("Not an valid index for frameNum!");
	return math::ivec2(0);
}

