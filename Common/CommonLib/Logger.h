#pragma once

#include <cstdint>

namespace Utils {
	enum class LoggingLevel : std::uint8_t {
		Trace = 0,
		Debug = 1,
		Info = 2,
		Highlight = 3,
		Warning = 4,
		Error = 5
	};

	class ILoggingManager;

	class Logger final {
		ILoggingManager* m_LoggingManager;
		const char* m_ClassName;

	public:
		/*	Constructor creates a logger with parameter className of current class and
		a pointer to the current LoggingManager */
		Logger(const char* className, ILoggingManager* logManager);

		// Log functions send a message along with level of importance to the LoggingManager
		
		void LogInfo(const unsigned int bufferSize, const char* format, ...);
		void LogInfo(const char* format, ...);
		
		void LogHighlight(const unsigned int bufferSize, const char* format, ...);
		void LogHighlight(const char* format, ...);
		
		void LogWarning(const unsigned int bufferSize, const char* format, ...);
		void LogWarning(const char* format, ...);

		void LogError(const unsigned int bufferSize, const char* format, ...);
		void LogError(const char* format, ...);

		void LogLevel(const unsigned int bufferSize, const char* format, LoggingLevel loggingLevel, ...);
		void LogLevel(const char* format, LoggingLevel level, ...);

		void Log(const char* format, va_list args, LoggingLevel loggingLevel, const unsigned int bufferSize);
	};
}