/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 5/5/2021
-----------------------------------------------------------------*/
#include "Collision.h"
#include "TransformMatrix.h"        // math::TransformMatrix
#include "doodle/drawing.hpp"       // draw_rectangle()
#include "GameObject.h"             // GetGOComponent<>()

void CS230::RectCollision::Draw(math::TransformMatrix cameraMatrix)
{
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    math::rect2 displayRect = GetWorldCoorRect();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_rectangle(displayRect.Left(), displayRect.Bottom(), displayRect.Size().x, displayRect.Size().y);
    doodle::pop_settings();
}

math::rect2 CS230::RectCollision::GetWorldCoorRect()
{
    return math::rect2{ objectPtr->GetMatrix() * rect.point1 ,objectPtr->GetMatrix() * rect.point2 };
}

bool CS230::RectCollision::DoesCollideWith(GameObject* testAgainstObject)
{
    if (testAgainstObject->GetGOComponent<Collision>() != nullptr && testAgainstObject->GetGOComponent<Collision>()->GetCollideType() == Collision::CollideType::Rect_Collide)
    {
        math::rect2 test = testAgainstObject->GetGOComponent<RectCollision>()->GetWorldCoorRect();
        if (GetWorldCoorRect().Left() < test.Right() && GetWorldCoorRect().Right() > test.Left() && GetWorldCoorRect().Bottom() < test.Top() && GetWorldCoorRect().Top() > test.Bottom())
        {
            return true;
        }
    }

    return false;
}

bool CS230::RectCollision::DoesCollideWith(math::vec2 point)
{
    if (GetWorldCoorRect().Left() <= point.x && GetWorldCoorRect().Right() >= point.x && GetWorldCoorRect().Bottom() <= point.y && GetWorldCoorRect().Top() >= point.y)
    {
        return true;
    }

    return false;
}

void CS230::CircleCollision::Draw(math::TransformMatrix cameraMatrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_ellipse(objectPtr->GetPosition().x, objectPtr->GetPosition().y, GetRadius() * 2);
    doodle::pop_settings();
}

double CS230::CircleCollision::GetRadius()
{
    return radius * objectPtr->GetScale().x;
}

bool CS230::CircleCollision::DoesCollideWith(GameObject* testAgainstObject)
{
    if (testAgainstObject->GetGOComponent<Collision>() != nullptr && testAgainstObject->GetGOComponent<Collision>()->GetCollideType() == Collision::CollideType::Circle_Collide)
    {
        math::vec2 objPos = objectPtr->GetPosition();
        math::vec2 textPos = testAgainstObject->GetPosition();
        double textRad = testAgainstObject->GetGOComponent<CircleCollision>()->GetRadius();
        if ((objPos.x - textPos.x) * (objPos.x - textPos.x) + (objPos.y - textPos.y) * (objPos.y - textPos.y) < (GetRadius() + textRad) * (GetRadius() + textRad))
        {
            return true;
        }
    }
    return false;
}

bool CS230::CircleCollision::DoesCollideWith(math::vec2 point)
{
    math::vec2 objPos = objectPtr->GetPosition();
    if ((objPos.x - point.x) * (objPos.x - point.x) + (objPos.y - point.y) * (objPos.y - point.y) <= GetRadius() * GetRadius())
    {
        return true;
    }
    return false;
}
