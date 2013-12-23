#pragma once

#include "Logger.h"

namespace Utils {
	class Logger;

	class ILoggingManager {
	public:
		virtual ~ILoggingManager(){}

		// Set function for minimum logtofile priority level
		virtual void SetMinimumLevel(LoggingLevel level) = 0;

		/*	Log function called by logger which then writes to either just
		console or both console and file depending on priority level */
		virtual void Log(const char* className, const char* message, LoggingLevel loggingLevel, const unsigned int bufferSize) = 0;

		/*	Factory method for creating a logger, parameter className being
		the name of the class the logger is created in */
		virtual Logger CreateLogger(const char* className) = 0;
	};
}