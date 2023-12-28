#include "DailyLogFile.h"
#include <iomanip>

std::string DailyLogFile::getFormattedDate()
{
	// Get current unformatted time
	time_t now = time(0);

	// Create a 'tm' structure to store the broken-down time
	tm ltm;

	// Convert 'time_t' to a local time and store it in 'ltm'
	localtime_s(&ltm, &now);

	// Create a string stream to format the time
	std::ostringstream oss;
	oss << std::put_time(&ltm, "%Y-%m-%d"); // Format: YYYY-MM-DD

	// Convert the formatted time from the string stream to a string and return it
	return oss.str();
}

void DailyLogFile::logRoomAccessAttempts(const std::string& accessInfo) {
    std::ofstream logFile("DailyAccessLogs/room_access_log_" + getFormattedDate() + ".txt", std::ios::app);

    if (logFile.is_open()) {
        // Write access attempt information to the file
        logFile << accessInfo << "\n";

        // Close the file after writing
        logFile.close();
    }
    else {
        std::cout << "Unable to open access log file." << std::endl;
    }
}

void DailyLogFile::viewRoomAccessAttempts() {
    std::string fileName = "DailyAccessLogs/room_access_log_" + getFormattedDate() + ".txt";
    std::ifstream logFile(fileName);
    if (logFile.is_open()) {
        std::string line;
        while (std::getline(logFile, line)) {
            std::cout << line << std::endl;
        }
        logFile.close();
    }
    else {
        std::cout << "Unable to open access log file." << std::endl;
    }
}