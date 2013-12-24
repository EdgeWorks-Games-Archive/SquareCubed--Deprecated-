#pragma once

#include <Coherent/Libraries/Logging/ILogHandler.h>

#include <CommonLib/Logger.h>

namespace Utils { class ILoggingManager; }

namespace CoherentUIOpenGLUI {
	class LogHandler final : public Coherent::Logging::ILogHandler {
		Utils::Logger m_Logger;

	public:
		LogHandler(Utils::ILoggingManager &logManager);
		~LogHandler();

		void WriteLog(Coherent::Logging::Severity severity, const char* message, size_t length);
		void Assert(const char* message);
	};
}