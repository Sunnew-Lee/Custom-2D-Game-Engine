/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/26/2021
-----------------------------------------------------------------*/
#include "Camera.h"
#include "TransformMatrix.h"	// math::TransformMatrix, math::TranslateMatrix

CS230::Camera::Camera(math::rect2 movableRange):movableRange(movableRange)
{}

void CS230::Camera::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
}

const math::vec2& CS230::Camera::GetPosition() const
{
	return position;
}

void CS230::Camera::SetExtent(math::irect2 newExtent)
{
	extent = newExtent;
}

void CS230::Camera::Update(const math::vec2& followObjPos)
{
	if (followObjPos.x-position.x < movableRange.bottomLeft.x)
	{
		position.x = followObjPos.x - movableRange.bottomLeft.x;
	}
	else if (followObjPos.x - position.x > movableRange.topRight.x)
	{
		position.x = followObjPos.x - movableRange.topRight.x;
	}

	if (position.x < extent.bottomLeft.x)
	{
		position.x = extent.bottomLeft.x;
	}
	else if (position.x > extent.topRight.x)
	{
		position.x = extent.topRight.x;
	}
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix::TranslateMatrix(-position);
}
