#pragma once

#include "ILoggingManager.h"
#include "Logger.h"

#include <iostream>
#include <fstream>

namespace Utils {

	class LoggingManager final : public ILoggingManager {
		LoggingLevel m_Minimum;
		std::ofstream m_Log;

	public: // Constructor/Deconstructor
		/*	Constructor takes a LoggingLevel parameter that is then used
		to set the minimum priority level to log to file. */
		LoggingManager(const char* logPath);
		~LoggingManager();

		Logger CreateLogger(const char* className);

		void SetMinimumLevel(LoggingLevel level);
		void Log(const char* className, const char* message, LoggingLevel loggingLevel, const unsigned int bufferSize);

	public: // Helping Methods
		/*	Function for turning a LoggingLevel into an appropriate string
		for the sprintf function */
		static const char* LevelToString(LoggingLevel loggingLevel);
	};
}