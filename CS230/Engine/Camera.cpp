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

CS230::Camera::Camera(math::rect2 movableRange) : extent(math::ivec2(0)), position(math::vec2(0)), movableRange(movableRange)
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

	if (followObjPos.y - position.y < movableRange.bottomLeft.y)
	{
		position.y = followObjPos.y - movableRange.bottomLeft.y;
	}
	else if (followObjPos.y - position.y > movableRange.topRight.y)
	{
		position.y = followObjPos.y - movableRange.topRight.y;
	}


	if (position.x < extent.bottomLeft.x)
	{
		position.x = extent.bottomLeft.x;
	}
	else if (position.x > extent.topRight.x)
	{
		position.x = extent.topRight.x;
	}

	if (position.y < extent.bottomLeft.y)
	{
		position.y = extent.bottomLeft.y;
	}
	else if (position.y > extent.topRight.y)
	{
		position.y = extent.topRight.y;
	}
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix::TranslateMatrix(-position);
}
