/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"           // Sprite
#include "..\Engine\Input.h"            // InputKey
#include "..\Engine\Vec2.h"             // math::vec2
#include "..\Engine\TransformMatrix.h"  // math::TransformMatrix

namespace CS230 {
    class Camera;
}

class Hero {
public:
    Hero(math::vec2 startPos, const CS230::Camera& camera);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix cameraMatrix);
    math::vec2 Get_Hero_Position();

private:
    class State {
    public:
        virtual void Enter(Hero* hero) = 0;
        virtual void Update(Hero* hero, double dt) = 0;
        virtual void TestForExit(Hero* hero) = 0;
        virtual std::string GetName() = 0;
    };
    class State_Idle : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Skidding : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Skidding"; }
    };
    class State_Jumping : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Falling : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Falling"; }
    };

    CS230::Sprite sprite;
    math::vec2 startPos;
    math::vec2 position;

    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey moveJumpKey;
    math::vec2 velocity;
    math::TransformMatrix objectMatrix;
    bool isRunningLeft;

    const CS230::Camera& camera;
    static constexpr double Acceleration_x{ 500 };
    static constexpr double Drag_x{ 1000 };
    static constexpr double Max_Velocity_x{ 1000 };
    static constexpr double Jump_Velocity{ 1000 };

    State_Idle stateIdle;
    State_Running stateRunning;
    State_Skidding stateSkidding;
    State_Jumping stateJumping;
    State_Falling stateFalling;

    void UpdateXVelocity(double dt);     //Change X velocity stuff
    void ChangeState(State* newState);

    State* currState;

};