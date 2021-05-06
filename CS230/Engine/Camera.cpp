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

CS230::Camera::Camera(math::rect2 movableRange) : extent(math::irect2{ math::ivec2(0) }), position(math::vec2(0)), movableRange(movableRange)
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
	if (followObjPos.x-position.x < movableRange.Left())
	{
		position.x = followObjPos.x - movableRange.Left();
	}
	else if (followObjPos.x - position.x > movableRange.Right())
	{
		position.x = followObjPos.x - movableRange.Right();
	}

	if (followObjPos.y - position.y < movableRange.Bottom())
	{
		position.y = followObjPos.y - movableRange.Bottom();
	}
	else if (followObjPos.y - position.y > movableRange.Top())
	{
		position.y = followObjPos.y - movableRange.Top();
	}


	if (position.x < extent.Left())
	{
		position.x = extent.Left();
	}
	else if (position.x > extent.Right())
	{
		position.x = extent.Right();
	}

	if (position.y < extent.Bottom())
	{
		position.y = extent.Bottom();
	}
	else if (position.y > extent.Top())
	{
		position.y = extent.Top();
	}
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix::TranslateMatrix(-position);
}
