#include "Logger.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

namespace engine {
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
		// TODO Fix: Cuts of first letter when concat with num values -> Look into Pointer Arithmetics for this issue
		std::string currentTimeString = std::ctime(&time);
		currentTimeString.erase(std::remove(currentTimeString.begin(), currentTimeString.end(), '\n'), currentTimeString.end());

		// Write Content to File
		if (m_firstWrite) {
			stream << "-- New Session " << currentTimeString << " --" << std::endl;
			m_firstWrite = false;
		}

		stream << content << std::endl;
		std::cout << content << std::endl;
	}
}