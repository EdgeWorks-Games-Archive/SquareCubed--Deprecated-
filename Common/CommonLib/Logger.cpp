#include "LoggingManager.h"
#include "Logger.h"
#include <stdio.h>
#include <stdarg.h>

namespace Utils {
	Logger::Logger(const char* className, ILoggingManager* logManager) {
		m_LoggingManager = logManager;
		m_ClassName = className;
	}

	void Logger::LogInfo(const unsigned int bufferSize, const char* format, ...) {		
		va_list args;
		va_start(args, format);
		Log(format, args, LoggingLevel::Info, bufferSize);
		va_end(args);
	}
	void Logger::LogInfo(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Log(format, args, LoggingLevel::Info, 500);
		va_end(args);
	}
	
	
	void Logger::LogHighlight(const unsigned int bufferSize, const char* format, ...) {
		va_list args;
		va_start(args, format);
		Log(format, args, LoggingLevel::Highlight, bufferSize);
		va_end(args);
	}
	void Logger::LogHighlight(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Log(format, args, LoggingLevel::Highlight, 500);
		va_end(args);
	}


	void Logger::LogWarning(const unsigned int bufferSize, const char* format, ...) {
		va_list args;
		va_start(args, format);
		Log(format, args, LoggingLevel::Warning, bufferSize);
		va_end(args);
	}
	void Logger::LogWarning(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Log(format, args, LoggingLevel::Warning, 500);
		va_end(args);
	}

	
	void Logger::LogError(const unsigned int bufferSize, const char* format, ...) {
		va_list args;
		va_start(args, format);
		Log(format, args, LoggingLevel::Error, bufferSize);
		va_end(args);
	}
	void Logger::LogError(const char* format, ...) {
		va_list args;
		va_start(args, format);
		Log(format, args, LoggingLevel::Error, 500);
		va_end(args);
	}

	
	void Logger::LogLevel(const unsigned int bufferSize, const char* format, LoggingLevel loggingLevel, ...) {
		va_list args;
		va_start(args, loggingLevel);
		Log(format, args, loggingLevel, bufferSize);
		va_end(args);
	}
	void Logger::LogLevel(const char* format, LoggingLevel loggingLevel, ...) {
		va_list args;
		va_start(args, loggingLevel);
		Log(format, args, loggingLevel, 500);
		va_end(args);
	}


	void Logger::Log(const char* format, va_list args, LoggingLevel loggingLevel, const unsigned int bufferSize) {
		char* buff = new char[bufferSize];
		vsprintf_s(buff, bufferSize, format, args);
		m_LoggingManager->Log(m_ClassName, buff, loggingLevel, bufferSize);
	}
}