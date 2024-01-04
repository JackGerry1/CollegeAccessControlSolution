// Simulation.cpp : This file contains functions and attributes specifeid in the Simulation.h file. 

#include "Simulation.h"

/*
References:
Tutorialspoint (2020) 'C++ Date and Time - Tutorialspoint', Tutorialspoint.
Available at: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm [Accessed 27th December 2023].

Haleem, A. (2020) 'Exploring Date and Time with Chrono', Medium.
Available at: https://ambreen2006.medium.com/exploring-date-and-time-with-chrono-3a8e9af60f62 [Accessed 27th December 2023].

Clark, M. (2023) 'Creating a Formatted Date String from Date Time in C', CopyProgramming. 
Available at: https://copyprogramming.com/howto/c-get-formated-date-string-from-date-time#c11-get-current-date-and-time-as-string [Accessed 27th December 2023].

Kaushik, A. (2022) 'C++ String Replace Function', Scaler Topics.
Available at: https://www.scaler.com/topics/cpp-string-replace/ [Accessed 18th December 2023].

Ram, V. (2022) 'How to use the string find() in C++', DigitalOcean.
Available at: https://www.digitalocean.com/community/tutorials/string-find-c-plus-plus [Accessed 18th December 2023].

GeeksForGeeks (2023b) 'Substring in C++', GeeksforGeeks.
Available at: https://www.geeksforgeeks.org/substring-in-cpp/ [Accessed 18th December 2023].

Cplusplus.com (2023) 'std::vector::erase', Cplusplus.com.
Available at: https://cplusplus.com/reference/vector/vector/erase/ [Accessed 18th December 2023].

Cppreference (2023) 'std::size_t - cppreference.com', en.cppreference.com.
Available at: https://en.cppreference.com/w/cpp/types/size_t [Accessed 18th December 2023].
*/

// Function: startSimulation
// Objective: allow user to choose which user they want to simulate
void Simulation::startSimulation() {
	// Retrieve user data from the file
	std::vector<std::string> simUserData = IDCardLog::readUserDataFromFile();

	if (!simUserData.empty()) {
		// Display available user data for simulation
		IDCardLog::displayUsersFromLogFile();

		// Ask for the line number/index to simulate
		int lineNumber;
		std::cout << "Enter the index/line number of the user you want to simulate: ";
		std::cin >> lineNumber;

		// Check if the entered line number is within the valid range
		if (lineNumber >= 0 && lineNumber < simUserData.size()) {
			std::string userToSimulate = simUserData[lineNumber]; // Get user data based on the input index

			// Clear the screen for a better UI
			system("cls");
			std::cout << "Simulating user: " << userToSimulate << std::endl;

			// Simulation menu for user actions
			bool continueSimulation = true;
			while (continueSimulation) {
				int simOption;
				std::cout << "\nSimulation Menu:\n";
				std::cout << "1. Join Room\n";
				std::cout << "2. Stop Simulation\n";
				std::cout << "Enter your choice: ";
				std::cin >> simOption;

				switch (simOption) {
				case 1:
					// Perform room joining simulation
					joinRoom(userToSimulate); 
					break;
				case 2:
					// Stop the simulation
					stopSimulation();
					continueSimulation = false;
					break;
				default:
					std::cout << "Invalid choice. Please try again." << std::endl;
					break;
				}
			}
		}
		// erorr if invalid line number
		else {
			std::cout << "Invalid index/line number entered." << std::endl;
		}
	}
	// error if no users to simulate
	else {
		std::cout << "No Users to Simulate" << std::endl;
	}
}
// Function: extractRoles
// Paramaters: string of the user that is attempting to join a room, and an empty vector for the user roles
void Simulation::extractRoles(const std::string& userToJoin, std::vector<std::string>& roles) {
	// Find the position of "Roles:"
	size_t pos = userToJoin.find("Roles:");

	if (pos != std::string::npos) {
		// Extract roles substring after "Roles:"
		std::string rolesString = userToJoin.substr(pos + 7); // Skip "Roles:" and space

		// Find the position of "Swipe Card ID:"
		size_t swipeCardPos = rolesString.find("Swipe Card ID:");

		// If the position of "Swipe Card ID:" is found in the roles string,
		// exclude the substring starting from "Swipe Card ID:" till the end
		if (swipeCardPos != std::string::npos) {
			rolesString = rolesString.substr(0, swipeCardPos);
		}

		// Use stringstream to split roles separated by ','
		std::stringstream ss(rolesString);
		std::string role;

		// Tokenize roles separated by ',' and Store each role in the roles vector
		while (std::getline(ss, role, ',')) {
			roles.push_back(role); 
		}
	}
} // end of extractRoles

// Function: extractRoomInfo
// Paramaters: The room that has been chosen the empty strings for roomType and roomState
// Objective: extract the room type and room state for the room that the user is attempting to access. 
void Simulation::extractRoomInfo(const std::string& roomToJoin, std::string& roomType, std::string& roomState) {
	// Find the positions of "Room Type:" and "Room State:"
	size_t typePos = roomToJoin.find("Room Type:");
	size_t statePos = roomToJoin.find("Room State:");

	// Check if both "Room Type:" and "Room State:" are found in the input string
	if (typePos != std::string::npos && statePos != std::string::npos) {
		// Extract room type substring after "Room Type:"
		size_t typeStart = typePos + 11; // Skip "Room Type:" and space
		size_t typeEnd = roomToJoin.find(',', typeStart); // Find the end of the room type string
		roomType = roomToJoin.substr(typeStart, typeEnd - typeStart);

		// Extract room state substring after "Room State:" and stop before "Building State:"
		size_t stateStart = statePos + 12; // Skip "Room State:" and space
		size_t buildingStatePos = roomToJoin.find("Building State:");

		// Determine the endpoint for the room state substring:
		// If "Building State:" exists in the string, the endpoint for the room state substring
		// is set just before "Building State:". Otherwise, it takes the end of the roomToJoin string.
		size_t stateEnd = (buildingStatePos != std::string::npos) ? buildingStatePos - 2 : roomToJoin.size();

		// Extract the room state substring starting from stateStart and ending at stateEnd
		roomState = roomToJoin.substr(stateStart, stateEnd - stateStart);
	}
} // end of extractRoomInfo


// Function: verifyRoomAccess
// Paramaters: roomType string, formattedRoles string, roomState string and the current generated log message. 
// Objective: choose one of the overriden functions based on the room type, return true or false then write that log message to the daily log file
bool Simulation::verifyRoomAccess(const std::string& roomType, const std::string& formattedRoles, const std::string& roomState, const std::string& log) {
	bool accessGranted = false; // Flag to track access permission
	std::string message; // String to store the access status message

	// Check the type of room and verify access based on room type
	// will call a different overloaded function based on the room type
	if (roomType == "Lecture Hall") {
		LectureHall lectureHall("", "", -1, "", -1);
		accessGranted = lectureHall.verifyEntryRequirements(formattedRoles, roomState);
	}
	else if (roomType == "Teaching Room") {
		TeachingRoom teachingRoom("", "", -1, "", -1);
		accessGranted = teachingRoom.verifyEntryRequirements(formattedRoles, roomState);
	}
	else if (roomType == "Staff Room") {
		StaffRoom staffRoom("", "", -1, "", -1);
		accessGranted = staffRoom.verifyEntryRequirements(formattedRoles, roomState);
	}
	else if (roomType == "Secure Room") {
		SecureRoom secureRoom("", "", -1, "", -1);
		accessGranted = secureRoom.verifyEntryRequirements(formattedRoles, roomState);
	}
	else {
		std::cout << "Unknown room type encountered." << std::endl; // Handle an unknown room type
	}

	// Formulate the access status message based on accessGranted flag
	if (accessGranted) {
		message = "ACCESS GRANTED: " + log;
	}
	else {
		message = "ACCESS DENIED: " + log;
	}
	// Get the current date and time
	std::string dateTime = getDateAndTime(); 

	message += ", Date And Time: " + dateTime; // Include date and time in the access status message
	std::cout << "Adding To Daily Access Log: " << message << std::endl;

	DailyLogFile::logRoomAccessAttempts(message); // Log the access attempt in the daily log file

	return accessGranted; // Return the access permission status
} // end of verifyRoomAccess

// Function: joinRoom
// Paramaters: string of userToJoin
// Objective: get all of the user and room information required to pass into the verifyRoomAccess function
void Simulation::joinRoom(const std::string& userToJoin) {
	// Retrieve room data from the file
	std::vector<std::string> roomData = BuildingStructureLog::readRoomDataFromFile();

	// Display user information
	std::cout << userToJoin << std::endl;

	// Check if room data exists
	if (!roomData.empty()) {
		// Display building structure information
		BuildingStructureLog::displayFileInfo("LogFiles/Building_Structure.txt");

		// Ask the user for the index/line number of the room to join
		int roomIndex;
		std::cout << "Enter the index/line number of the room you want to join: ";
		std::cin >> roomIndex;

		// Check if the entered room index is valid
		if (roomIndex >= 0 && roomIndex < roomData.size()) {
			// Retrieve room data based on the input index
			std::string roomToJoin = roomData[roomIndex];

			// Extract roles from the user to join
			std::vector<std::string> roles;
			extractRoles(userToJoin, roles);

			// Extract room type and state from the room to join
			std::string roomType, roomState;
			extractRoomInfo(roomToJoin, roomType, roomState);

			// Generate log information with roles as a single string
			std::string rolesString;
			if (!roles.empty()) {
				rolesString = roles[0]; // Initialize with the first role
				for (int i = 1; i < roles.size(); ++i) {
					rolesString += "," + roles[i]; // Append subsequent roles with a comma separator
				}
			}
			// Generate log information
			std::string log = generateLog(userToJoin, roomToJoin, roomState, rolesString);

			// Verify room access based on room type, roles, and state, and log access attempt
			bool accessGranted = verifyRoomAccess(roomType, rolesString, roomState, log);

			// Perform additional functionality if access is granted
			if (accessGranted) {
				leaveRoom(log); 
			}
		}
		else {
			std::cout << "Invalid room index/line number entered." << std::endl;
		}
	}
} // end of joinRoom


// Function: leaveRoom
// Paramater: the log string 
// Objective: to allow the user to leave the room if they desire
void Simulation::leaveRoom(const std::string& log) {
	bool leavingRoom = false; // Initialize leavingRoom flag

	// Display menu to allow the user to leave the room
	while (!leavingRoom) {
		std::cout << "\nOptions:\n"
			"1. Leave Room\n"
			"2. Go Back To Simulation Menu\n"
			"Choose an option: ";
		int choice;
		std::cin >> choice; // User input for choice

		switch (choice) {
		case 1: {
			std::string leaveDateTime = getDateAndTime(); // Get current date and time
			// Construct a message indicating leaving the room with log information and the leave time
			std::string leaveMessage = "LEFT ROOM: " + log + ", Date and Time: " + leaveDateTime;
			// Log the leaving attempt with the assembled message
			DailyLogFile::logRoomAccessAttempts(leaveMessage);
			std::cout << "You have left the room.\n"; // Inform the user about leaving
			leavingRoom = true; // Set leavingRoom to true to exit the loop
			break;
		}
		case 2:
			// Set leavingRoom to true to exit the loop and return to the simulation menu
			system("cls"); // Clear the console screen
			std::cout << "Returned To Simulation Menu" << std::endl;
			leavingRoom = true;
			break;
		default:
			std::cout << "Invalid choice. Please choose again.\n"; // Prompt for a valid choice
			break;
		}
	}
} // end of leaveRoom


// Function: generateLog
// Paramaters: userToJoin, roomToJoin, roomstate, formattedRoles
// Objective: to generate a message log for every access attempt
std::string Simulation::generateLog(const std::string& userToJoin, const std::string& roomToJoin, const std::string& roomState, const std::string& formattedRoles) {
	// Extract user's name from userToJoin string
	size_t nameStart = userToJoin.find("Name:") + 6; // Find the start of the name substring
	size_t nameEnd = userToJoin.find(", Roles:"); // Find the end of the name substring
	std::string userName = userToJoin.substr(nameStart, nameEnd - nameStart); // Extract the user's name

	// Extract swipe card ID from userToJoin string
	size_t swipeCardStart = userToJoin.find("Swipe Card ID:") + 15; // Find the start of the swipe card ID substring
	std::string swipeCardID = userToJoin.substr(swipeCardStart); // Extract the swipe card ID

	// Remove quad spaces from swipe card ID
	size_t foundQuadSpaces = swipeCardID.find("    "); // Find quad spaces
	while (foundQuadSpaces != std::string::npos) {
		swipeCardID.replace(foundQuadSpaces, 4, ""); // Replace quad spaces with an empty string
		foundQuadSpaces = swipeCardID.find("    ", foundQuadSpaces + 1); // Find the next occurrence
	}

	// Extract room information from roomToJoin string
	size_t roomTypeStart = roomToJoin.find("Room Type:") + 11; // Find the start of the room type substring
	size_t roomTypeEnd = roomToJoin.find(", Room State:"); // Find the end of the room type substring
	std::string roomType = roomToJoin.substr(roomTypeStart, roomTypeEnd - roomTypeStart); // Extract the room type

	size_t buildingNameStart = roomToJoin.find("Building Name:") + 15; // Find the start of the building name substring
	size_t buildingNameEnd = roomToJoin.find(", Room:"); // Find the end of the building name substring
	std::string buildingName = roomToJoin.substr(buildingNameStart, buildingNameEnd - buildingNameStart); // Extract the building name

	size_t roomNumberStart = roomToJoin.find("Room:") + 6; // Find the start of the room number substring
	size_t roomNumberEnd = roomToJoin.find(", Room Type:"); // Find the end of the room number substring
	std::string roomNumber = roomToJoin.substr(roomNumberStart, roomNumberEnd - roomNumberStart); // Extract the room number

	// Construct the log message using extracted information
	std::string logMessage =
		"User: " + userName + ", Roles: " + formattedRoles + "Swipe Card ID: " + swipeCardID +
		", Building Name: " + buildingName + ", Room: " + roomNumber +
		", Room Type: " + roomType + ", Room State: " + roomState;

	return logMessage; // Return the constructed log message
} // end of generateLog


// Function: stopSimulation
// Objective: allow the user to stop the simulation
void Simulation::stopSimulation() {
	// Inform the user that the simulation has stopped
	system("cls"); 
	std::cout << "Simulation Stopped\n\n"; 
} // end of stopSimulation

// Function: getDateAndTime
// Objective: format the date and time into YYYY-MM-DD HH-MM-SS
std::string Simulation::getDateAndTime() {
	// Get current unformatted time as 'time_t'
	time_t now = time(0);

	// Create a 'tm' structure to store the broken-down time
	tm ltm;

	// Convert 'time_t' to a local time and store it in 'ltm'
	localtime_s(&ltm, &now);

	// Create a string stream to format the time as: YYYY-MM-DD HH:MM:SS
	std::ostringstream oss;
	oss << std::put_time(&ltm, "%Y-%m-%d %H:%M:%S");

	std::string dateTime = oss.str();

	return dateTime; // Return the formatted date and time
} // end of getDateAndTime
