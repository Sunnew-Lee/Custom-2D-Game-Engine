/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Floor.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 05/20/2021
-----------------------------------------------------------------*/
#include "Floor.h"
#include "..\Engine\Rect.h"			// math::irect2
#include "..\Engine\Collision.h"	// RectCollision

Floor::Floor(math::irect2 rect) : GameObject(rect.point1)
{
	math::irect2 rect_new{ math::ivec2{ 0 }, rect.Size() };
	this->AddGOComponent(new CS230::RectCollision(rect_new, this));
}  
