// DailyLogFile.cpp : This file contains functions and attributes specifeid in the DailyLogFile.h file. 

#include "DailyLogFile.h"
#include <iomanip>

/*
References:
    URL: https://www.programiz.com/cpp-programming/file-handling Date Accessed: 14/12/23
    URL: https://copyprogramming.com/howto/c-get-formated-date-string-from-date-time#c11-get-current-date-and-time-as-string Date Accessed: 27/12/23
*/

// Function: getFormattedDate
// Objective: Format the date into YYYY-MM-DD
std::string DailyLogFile::getFormattedDate()
{
	// Get current unformatted time
	time_t now = time(0);

	// Create a 'tm' structure to store the broken-down date
	tm ltm;

	// Convert 'time_t' to a local date and store it in 'ltm'
	localtime_s(&ltm, &now);

	// Create a string stream to format the date
	std::ostringstream oss;
	oss << std::put_time(&ltm, "%Y-%m-%d"); // Format: YYYY-MM-DD

	// Convert the formatted date from the string stream to a string and return it
	return oss.str();
} // end of getFormattedDate

// Function: logRoomAccessAttempts
// Paramaters: String of log result
// Objective: log each attempt to the current days access log
void DailyLogFile::logRoomAccessAttempts(const std::string& accessInfo) {
    // Creates a new file for the current day if one does not exist, else just appends to the currently created file
    std::ofstream logFile("DailyAccessLogs/room_access_log_" + getFormattedDate() + ".txt", std::ios::app);

    // checks if log file is open
    if (logFile.is_open()) {
        // Write access attempt information to the file
        logFile << accessInfo << "\n";

        // Close the file after writing
        logFile.close();
    }
    // error if unable to open file
    else {
        std::cout << "Unable to open access log file." << std::endl;
    }
} // end of logRoomAccessAttempts

// Function: viewRoomAccessAttempts
// Objective: View access attempts logged in the daily room access log file.
void DailyLogFile::viewRoomAccessAttempts() {
    // Generate the file name using the formatted date
    std::string fileName = "DailyAccessLogs/room_access_log_" + getFormattedDate() + ".txt";

    // Open the file stream for reading
    std::ifstream logFile(fileName);

    // Check if the log file is successfully opened
    if (logFile.is_open()) {
        std::string line;

        // Read each line from the file and display it on the console
        while (std::getline(logFile, line)) {
            std::cout << line << std::endl;
        }

        // Close the log file stream
        logFile.close();
    }
    else {
        // Display an error message if the log file couldn't be opened
        std::cout << "Unable to open access log file." << std::endl;
    }
} // end of viewRoomAccessAttempts
