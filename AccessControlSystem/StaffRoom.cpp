#include "StaffRoom.h"

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
// Parameters: const std::string& formattedRoles - formatted user roles const std::string& roomState - state of the room
// Objective: Determines if access is granted based on user roles and room state.
bool StaffRoom::verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState)
{
	// Deny access by default
	bool accessGranted = false;

	// Security: Access at any time, regardless of mode
	if (formattedRoles.find("Security") != std::string::npos) {
		accessGranted = true;
	}

	// Check the room state first
	if (roomState == "NORMAL") {

		// Check if any of the roles match the allowed entry requirements
		// this is the check for Staff Members
		if (formattedRoles.find("Staff Member") != std::string::npos) {
			// Get the current system time and convert to time_t for localtime_s
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
		// check for Contract Cleaner
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
		// check for manager
		else if (formattedRoles.find("Manager") != std::string::npos) {
			accessGranted = true;
		}
	}
	// Emergency mode access
	else {
		// Emergency Responder: Access only in emergency mode
		if (formattedRoles.find("Emergency Responder") != std::string::npos) {
			accessGranted = true;
		}
	}
	return accessGranted;
} // end of verifyEntryRequirements
