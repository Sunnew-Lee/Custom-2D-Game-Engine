/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Logger.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include <iostream>    // cout.rdbuf
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool useConsole, std::chrono::system_clock::time_point startTime) :
	minLevel(severity), outStream("Trace.log"), startTime(startTime) {
	if (useConsole == true) {
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

CS230::Logger::~Logger() {
	outStream.flush();
	outStream.close();
}

void CS230::Logger::Log(CS230::Logger::Severity severity, std::string message) {
	if (severity >= minLevel) {
		outStream.precision(4);
		outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";

		switch (severity) {
		case Severity::Verbose:
			outStream << "Verb \t";
			break;
		case Severity::Debug:
			outStream << "Debug\t";
			break;
		case Severity::Error:
			outStream << "Error\t";
			break;
		case Severity::Event:
			outStream << "Event\t";
			break;
		}
		outStream << message;

#ifdef _DEBUG
		outStream << std::endl;
#else
		outStream << '\n';
#endif
	}
}

double CS230::Logger::GetSecondsSinceStart() {
	return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
}