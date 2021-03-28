/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TransformMatrix.cpp
Project: CS230
Author: sunwoo.lee
Creation date: 03/26/2021
-----------------------------------------------------------------*/
#include "TransformMatrix.h"

math::TransformMatrix::TransformMatrix()
{
	Reset();
}

math::TransformMatrix math::TransformMatrix::operator * (TransformMatrix rhs) const {
    TransformMatrix result;

    result.matrix[0][0] = matrix[0][0] * rhs[0][0] + matrix[0][1] * rhs[1][0] + matrix[0][2] * rhs[2][0];
    result.matrix[0][1] = matrix[0][0] * rhs[0][1] + matrix[0][1] * rhs[1][1] + matrix[0][2] * rhs[2][1];
    result.matrix[0][2] = matrix[0][0] * rhs[0][2] + matrix[0][1] * rhs[1][2] + matrix[0][2] * rhs[2][2];
    result.matrix[1][0] = matrix[1][0] * rhs[0][0] + matrix[1][1] * rhs[1][0] + matrix[1][2] * rhs[2][0];
    result.matrix[1][1] = matrix[1][0] * rhs[0][1] + matrix[1][1] * rhs[1][1] + matrix[1][2] * rhs[2][1];
    result.matrix[1][2] = matrix[1][0] * rhs[0][2] + matrix[1][1] * rhs[1][2] + matrix[1][2] * rhs[2][2];
    result.matrix[2][0] = matrix[2][0] * rhs[0][0] + matrix[2][1] * rhs[1][0] + matrix[2][2] * rhs[2][0];
    result.matrix[2][1] = matrix[2][0] * rhs[0][1] + matrix[2][1] * rhs[1][1] + matrix[2][2] * rhs[2][1];
    result.matrix[2][2] = matrix[2][0] * rhs[0][2] + matrix[2][1] * rhs[1][2] + matrix[2][2] * rhs[2][2];

    return result;
}

math::TransformMatrix& math::TransformMatrix::operator *= (math::TransformMatrix rhs) {
    (*this) = (*this) * rhs;
    return (*this);
}

void math::TransformMatrix::Reset()
{
    constexpr int MATRIX_SIZE{ 3 };

    for (int row{ 0 }; row < MATRIX_SIZE; row++)
    {
        for (int column{ 0 }; column < MATRIX_SIZE; column++)
        {
            matrix[row][column] = 0;
        }
    }

    for (int i{ 0 }; i < MATRIX_SIZE; i++)
    {
        matrix[i][i] = 1;
    }
}

math::TranslateMatrix::TranslateMatrix(ivec2 translate)
{
    matrix[0][2] = translate.x;
    matrix[1][2] = translate.y;
}

math::TranslateMatrix::TranslateMatrix(vec2 translate)
{
    matrix[0][2] = translate.x;
    matrix[1][2] = translate.y;
}
