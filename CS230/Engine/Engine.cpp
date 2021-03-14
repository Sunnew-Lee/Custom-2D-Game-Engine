/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Purpose: This is the service provider for our games engine services
Project: CS230
Author: sunwoo.lee
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "Engine.h"

Engine::Engine() :
#ifdef _DEBUG				
	logger(CS230::Logger::Severity::Debug, true, lastTick)
#else 						
	logger(CS230::Logger::Severity::Event, false, lastTick)
#endif
	,frameCount(0),lastTick(std::chrono::system_clock::now())
{}
Engine::~Engine() 
{}
void Engine::Init(std::string windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(windowName);
	fpsCalcTime = lastTick;
}
void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
}
void Engine::Update()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();
	if (dt > (1 / Engine::Target_FPS))
	{
		logger.LogVerbose("Engine Update");
		gameStateManager.Update(dt);
		input.Update();
		window.Update();
		if (++frameCount > Engine::FPS_IntervalFrameCount)
		{
			//Calculate the averageFrameRate for the given time interval
			double averageFrameRate = frameCount / std::chrono::duration<double>(now - fpsCalcTime).count();

			logger.LogEvent("FPS:  " + std::to_string(averageFrameRate));
			frameCount = 0;
			fpsCalcTime = now;
		}
		lastTick = now;
	}
}
bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();
}