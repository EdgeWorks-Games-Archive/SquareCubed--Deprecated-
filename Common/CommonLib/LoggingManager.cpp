#include "LoggingManager.h"
#include "Logger.h"

namespace Utils {
	LoggingManager::LoggingManager(const char* logPath) :
		m_Minimum(LoggingLevel::Info),
		m_Log(logPath)
	{ }

	LoggingManager::~LoggingManager() {
		try {
			m_Log.close();
		}
		catch (...) {
			// We don't want an exception to go uncatched in the deconstructor
		}
	}

	Logger LoggingManager::CreateLogger(const char* className) {
		return Logger(className, this);
	}

	void LoggingManager::SetMinimumLevel(LoggingLevel level) {
		m_Minimum = level;
	}

	void LoggingManager::Log(const char* className, const char* message, LoggingLevel loggingLevel, const unsigned int bufferSize) {
		// Temporary, will be changed with something better once log format is read from a config file
		// Didn't bother to count it out precisely, just a rough approximation
		const int sBuffSize = strlen("[%c] %-8s | %s") + strlen(className) + 8 + bufferSize;

		// Create a Message
		char *buff = new char[sBuffSize];
		sprintf_s(buff, sBuffSize, "[%c] %-8s | %s", LevelToString(loggingLevel)[0], className, message);

		// Output it to the File and the Console
		if (loggingLevel >= m_Minimum)
			m_Log << buff << std::endl;
		std::cout << buff << std::endl;
	}

	const char* LoggingManager::LevelToString(LoggingLevel loggingLevel) {
		switch (loggingLevel) {
		case LoggingLevel::Info:
			return "Info";
		case LoggingLevel::Highlight:
			return "Highlight";
		case LoggingLevel::Warning:
			return "Warning";
		case LoggingLevel::Error:
			return "Error";
		}

		// Should never happen unless someone adds a new level
		return "#INVALID";
	}
}