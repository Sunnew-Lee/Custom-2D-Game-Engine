/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.h
Project: CS230
Author: Kevin Wright
Creation date: 2/17/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h" 

enum class Fonts;

class Life : public CS230::Component {
public:
    Life(int startingLife, Fonts fontToUse);
    void IncreseLife();
    void DecreseLife();
    int GetLife();
    void Draw(math::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int life;
    CS230::Texture lifeTexture;
};