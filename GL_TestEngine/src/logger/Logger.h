#pragma once

#include <string>

namespace engine {
	class Logger {
	public:
		static Logger* getInstance();

		void write(const std::string& content);
		
	private:
		Logger();
		Logger(const Logger& other);

		const char* const m_FILE = "log/DebugLog.txt";
		bool m_firstWrite = true;
	};
}