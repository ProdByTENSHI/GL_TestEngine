#include "Logger.h"

#include <chrono>
#include <ctime>
#include <fstream>

namespace logger {
	static Logger* instance;

	Logger::Logger() {}

	Logger* Logger::getInstance() {
		if (instance == nullptr)
			instance = new Logger();

		return instance;
	}

	void Logger::write(const std::string& content) {
		std::ofstream stream(m_FILE, std::ofstream::app);
		const std::chrono::time_point tpTime = std::chrono::system_clock::now();
		const std::time_t time = std::chrono::system_clock::to_time_t(tpTime);

		// Remove newline character from ctime output
		// Fuck ctime for that
		std::string currentTimeString = std::ctime(&time);
		for (int i = 0; i < currentTimeString.length(); i++) {
			if (currentTimeString[i] == '\n') {
				currentTimeString[i] = '\0';
				break;
			}
		}

		// Write Content to File
		if (m_firstWrite) {
			stream << "<========== NEW SESSION ==========>]" << std::endl;
			m_firstWrite = false;
		}

		stream << "[" << currentTimeString << "]: " << content << std::endl;
	}
}