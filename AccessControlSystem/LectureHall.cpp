// LectureHall.cpp : This file contains functions and attributes specifeid in the LectureHall.h file. 

#include "LectureHall.h"

/*
References:

Tutorialspoint (2020) 'C++ Date and Time - Tutorialspoint', Tutorialspoint.
Available at: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm [Accessed 27th December 2023].

Haleem, A. (2020) 'Exploring Date and Time with Chrono', Medium.
Available at: https://ambreen2006.medium.com/exploring-date-and-time-with-chrono-3a8e9af60f62 [Accessed 27th December 2023].

Sinha, A. (2022). string::npos in C++. [Online] CodeSpeedy.
Available at: https://www.codespeedy.com/stringnpos-in-cpp/ [Accessed 18th December 2023].
*/

// Function: verifyEntryRequirements
// Paramaters: current roomState and formattedRoles of the user attempting to enter
// Objective: Return true or false whether or not the simulated user can enter the room
bool LectureHall::verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState) {
	// Deny access by default
	bool accessGranted = false;
	// Security: Access at any time, regardless of mode
	if (formattedRoles.find("Security") != std::string::npos) {
		accessGranted = true;
	}

	// Check the room state first
	if (roomState == "NORMAL") {

		// Check if any of the roles match the allowed entry requirements
		// below is a check for staff member
		if (formattedRoles.find("Staff Member") != std::string::npos) {
			// Get the current system time
			auto now = std::chrono::system_clock::now();
			std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

			// Extract the hour and minute from the current time using localtime_s
			std::tm timeInfo;
			localtime_s(&timeInfo, &currentTime);
			int currentHour = timeInfo.tm_hour;
			int currentMinute = timeInfo.tm_min;

			// Check if the current time is within the allowed time window for Staff Member
			if ((currentHour > 5 && currentHour < 23) || (currentHour == 5 && currentMinute >= 30) || (currentHour == 23 && currentMinute <= 59)) {
				accessGranted = true;
			}
		}
		// Check for if a student or visitor/guest can enter the room
		else if (formattedRoles.find("Student") != std::string::npos || formattedRoles.find("Visitor / Guest") != std::string::npos) {
			// Get the current system time
			auto now = std::chrono::system_clock::now();
			std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

			// Extract the hour and minute from the current time using localtime_s
			std::tm timeInfo;
			localtime_s(&timeInfo, &currentTime);
			int currentHour = timeInfo.tm_hour;
			int currentMinute = timeInfo.tm_min;

			// Check if the current time is within the allowed time window for Student or Visitor/Guest (08:30 to 22:00)
			if ((currentHour > 8 && currentHour < 22) || (currentHour == 8 && currentMinute >= 30) || (currentHour == 22 && currentMinute == 0)) {
				accessGranted = true;
			}
		}

		// Check if a contract cleaner can enter the room
		else if (formattedRoles.find("Contract Cleaner") != std::string::npos) {
			// Get the current system time
			auto now = std::chrono::system_clock::now();
			std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

			// Extract the hour and minute from the current time using localtime_s
			std::tm timeInfo;
			localtime_s(&timeInfo, &currentTime);
			int currentHour = timeInfo.tm_hour;
			int currentMinute = timeInfo.tm_min;

			// Check if the current time is within the allowed time window for Contract Cleaner
			// Access is allowed only during specific time windows (05:30 to 10:30 and 17:30 to 22:30)
			if ((currentHour > 5 && currentHour < 10) || (currentHour == 5 && currentMinute >= 30) ||
				(currentHour > 17 && currentHour < 22) || (currentHour == 17 && currentMinute >= 30) ||
				(currentHour == 10 && currentMinute == 30) || (currentHour == 22 && currentMinute == 30)) {
				accessGranted = true;
			}

		}
		// any time a manager can enter the room
		else if (formattedRoles.find("Manager") != std::string::npos) {
			accessGranted = true;
		}	
	}
	// check for emergeny state
	else {
		// Emergency Responder: Access only in emergency mode
		if (formattedRoles.find("Emergency Responder") != std::string::npos) {
			
			accessGranted = true;
		}

	}
	return accessGranted;
} // end of verifyEntryRequirements