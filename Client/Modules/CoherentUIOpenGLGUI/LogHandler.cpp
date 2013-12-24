#include "LogHandler.h"

#include <CommonLib/ILoggingManager.h>

#include <string>

namespace CoherentUIOpenGLUI {
	LogHandler::LogHandler(Utils::ILoggingManager &logManager) :
		m_Logger(logManager.CreateLogger("Coherent"))
	{}

	LogHandler::~LogHandler() {}

	void LogHandler::WriteLog(Coherent::Logging::Severity severity, const char* message, size_t length) {
		const char *format;
		Utils::LoggingLevel level;

		// Get the correct pattern
		switch (severity) {
		case Coherent::Logging::Trace:
			format = "Trace: %s";
			level = Utils::LoggingLevel::Trace;
			break;
		case Coherent::Logging::Debug:
			format = "Debug: %s";
			level = Utils::LoggingLevel::Debug;
			break;
		case Coherent::Logging::Info:
			format = "Info: %s";
			level = Utils::LoggingLevel::Info;
			break;
		case Coherent::Logging::Warning:
			format = "Warning: %s";
			level = Utils::LoggingLevel::Warning;
			break;
		case Coherent::Logging::AssertFailure:
			format = "Assert Fail: %s";
			level = Utils::LoggingLevel::Error;
			break;
		case Coherent::Logging::Error:
			format = "Error: %s";
			level = Utils::LoggingLevel::Error;
			break;
		default:
			format = "Failed to log message, update WriteLog in LogHandler!";
			level = Utils::LoggingLevel::Error;
		}

		// Calculate length
		unsigned int ln = strlen(format) + length;

		// Log message in format
		m_Logger.LogLevel(ln, format, level, message);
	}

	void LogHandler::Assert(const char* message) {
	}
}