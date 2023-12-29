// Simulation.cpp : This file contains functions and attributes specifeid in the Simulation.h file. 

#include "Simulation.h"


void Simulation::startSimulation() {
	std::vector<std::string> simUserData = IDCardLog::readUserDataFromFile();

	if (!simUserData.empty()) {
		IDCardLog::displayUsersFromLogFile();

		// Ask the user for the line number/index to simulate
		int lineNumber;
		std::cout << "Enter the index/line number of the user you want to simulate: ";
		std::cin >> lineNumber;

		// Check if the entered line number is within the valid range
		if (lineNumber >= 0 && lineNumber < simUserData.size()) {
			std::string userToSimulate = simUserData[lineNumber]; // Retrieve the user data based on the input index
			// Perform simulation logic using the user data and clear screen to make ui look nicer
			system("cls");
			std::cout << "Simulating user: " << userToSimulate << std::endl;

			// Menu for simulation options
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
		else {
			std::cout << "Invalid index/line number entered." << std::endl;
		}
	}
	else {
		std::cout << "No Users to Simulate" << std::endl;
	}
}

void Simulation::extractRoles(const std::string& userToJoin, std::vector<std::string>& roles) {
	// Find the position of "Roles:"
	size_t pos = userToJoin.find("Roles:");
	if (pos != std::string::npos) {
		// Extract roles substring after "Roles:"
		std::string rolesString = userToJoin.substr(pos + 7); // Skip "Roles:" and space
		size_t swipeCardPos = rolesString.find("Swipe Card ID:");
		if (swipeCardPos != std::string::npos) {
			rolesString = rolesString.substr(0, swipeCardPos); // Exclude swipe card information
		}

		std::stringstream ss(rolesString);
		std::string role;
		// Tokenize roles separated by ','
		while (std::getline(ss, role, ',')) {
			roles.push_back(role);
		}
	}
}
void Simulation::extractRoomInfo(const std::string& roomToJoin, std::string& roomType, std::string& roomState) {
	// Find the positions of "Room Type:" and "Room State:"
	size_t typePos = roomToJoin.find("Room Type:");
	size_t statePos = roomToJoin.find("Room State:");
	if (typePos != std::string::npos && statePos != std::string::npos) {
		// Extract room type substring after "Room Type:"
		size_t typeStart = typePos + 11; // Skip "Room Type:" and space
		size_t typeEnd = roomToJoin.find(',', typeStart); // Find end of room type string
		roomType = roomToJoin.substr(typeStart, typeEnd - typeStart);

		// Extract room state substring after "Room State:" and stop at the comma before "Building State:"
		size_t stateStart = statePos + 12; // Skip "Room State:" and space
		size_t buildingStatePos = roomToJoin.find("Building State:");
		size_t stateEnd = (buildingStatePos != std::string::npos) ? buildingStatePos - 2 : roomToJoin.size();
		roomState = roomToJoin.substr(stateStart, stateEnd - stateStart);
	}
}
bool Simulation::verifyRoomAccess(const std::string& roomType, const std::string& formattedRoles, const std::string& roomState, const std::string& log) {
	bool accessGranted = false;
	std::string message;
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
		std::cout << "Unknown room type encountered." << std::endl;
	}

	if (accessGranted) {
		message = "ACCESS GRANTED: " + log;
	}
	else {
		message = "ACCESS DENIED: " + log;
	}
	std::string dateTime = getDateAndTime();

	message += ", Date And Time: " + dateTime;
	std::cout << "Adding To Daily Access Log: " << message << std::endl;
	DailyLogFile::logRoomAccessAttempts(message);
	

	return accessGranted;
}

void Simulation::joinRoom(const std::string& userToJoin) {
	std::vector<std::string> roomData = BuildingStructureLog::readRoomDataFromFile();
	std::cout << userToJoin << std::endl;
	if (!roomData.empty()) {
		BuildingStructureLog::displayFileInfo("LogFiles/Building_Structure.txt");

		// Ask the user for the index/line number of the room to join
		int roomIndex;
		std::cout << "Enter the index/line number of the room you want to join: ";
		std::cin >> roomIndex;

		// Check if the entered room index is valid
		if (roomIndex >= 0 && roomIndex < roomData.size()) {

			// Check if the entered room index is valid

			std::string roomToJoin = roomData[roomIndex]; // Retrieve room data based on the input index
			// Extract roles from the user to join
			std::vector<std::string> roles;
			extractRoles(userToJoin, roles);

			// Extract room type and state from the room to join
			std::string roomType, roomState;
			extractRoomInfo(roomToJoin, roomType, roomState);

			std::string formattedRoles;
			if (!roles.empty()) {
				std::stringstream rolesOutput;

				auto rolesIter = roles.begin();
				rolesOutput << *rolesIter; // Output the first role

				// Output subsequent roles preceded by "," if they exist
				for (++rolesIter; rolesIter != roles.end(); ++rolesIter) {
					rolesOutput << "," << *rolesIter;
				}

				// Get the resulting string
				formattedRoles = rolesOutput.str();

				// Remove trailing spaces and commas
				formattedRoles.erase(
					std::find_if(
						formattedRoles.rbegin(),
						formattedRoles.rend(),
						[](char ch) { return ch != ' ' && ch != ','; }
					).base(),
					formattedRoles.end()
				);
			}
			
			std::string log = generateLog(userToJoin, roomToJoin, roomState, formattedRoles);
			bool accessGranted = verifyRoomAccess(roomType, formattedRoles, roomState, log);

			// leave room additional functionality
			if (accessGranted) {
				leaveRoom(log);
			}
		}
		else {
			std::cout << "Invalid room index/line number entered." << std::endl;
		}
	}
}

void Simulation::leaveRoom(const std::string& log) {
	bool leavingRoom = false;

	// Display menu to allow the user to leave the room
	while (!leavingRoom) {
		std::cout << "\nOptions:\n"
			"1. Leave Room\n"
			"2. Go Back To Simulation Menu\n"
			"Choose an option: ";
		int choice;
		std::cin >> choice;

		switch (choice) {
		case 1: {
			std::string leaveDateTime = getDateAndTime();
			std::string leaveMessage = "LEFT ROOM: " + log + ", Date and Time: " + leaveDateTime;
			DailyLogFile::logRoomAccessAttempts(leaveMessage);
			std::cout << "You have left the room.\n";
			leavingRoom = true;
			break;
		}
		case 2:
			// Set leavingRoom to true to exit the loop
			system("cls");
			std::cout << "Returned To Simulation Menu" << std::endl;
			leavingRoom = true; 
			break;
		default:
			std::cout << "Invalid choice. Please choose again.\n";
			break;
		
		}
	}
}


std::string Simulation::generateLog(const std::string& userToJoin, const std::string& roomToJoin, const std::string& roomState, const std::string& formattedRoles) {
	size_t nameStart = userToJoin.find("Name:") + 6;
	size_t nameEnd = userToJoin.find(", Roles:");
	std::string userName = userToJoin.substr(nameStart, nameEnd - nameStart);

	size_t swipeCardStart = userToJoin.find("Swipe Card ID:") + 15;
	std::string swipeCardID = userToJoin.substr(swipeCardStart);

	// Replace quad spaces with an empty string
	size_t foundQuadSpaces = swipeCardID.find("    ");
	while (foundQuadSpaces != std::string::npos) {
		swipeCardID.replace(foundQuadSpaces, 4, "");
		foundQuadSpaces = swipeCardID.find("    ", foundQuadSpaces + 1);
	}

	size_t roomTypeStart = roomToJoin.find("Room Type:") + 11;
	size_t roomTypeEnd = roomToJoin.find(", Room State:");
	std::string roomType = roomToJoin.substr(roomTypeStart, roomTypeEnd - roomTypeStart);

	size_t buildingNameStart = roomToJoin.find("Building Name:") + 15;
	size_t buildingNameEnd = roomToJoin.find(", Room:");
	std::string buildingName = roomToJoin.substr(buildingNameStart, buildingNameEnd - buildingNameStart);

	size_t roomNumberStart = roomToJoin.find("Room:") + 6;
	size_t roomNumberEnd = roomToJoin.find(", Room Type:");
	std::string roomNumber = roomToJoin.substr(roomNumberStart, roomNumberEnd - roomNumberStart);

	std::string logMessage =
		"User: " + userName + ", Roles: " + formattedRoles + ", Swipe Card ID: " + swipeCardID +
		", Building Name: " + buildingName + ", Room: " + roomNumber +
		", Room Type: " + roomType + ", Room State: " + roomState;

	return logMessage;
}


void Simulation::stopSimulation() {
	system("cls");
	std::cout << "Simulation Stopped\n\n";
}

std::string Simulation::getDateAndTime() {
	// Get current unformatted time
	time_t now = time(0);

	// Create a 'tm' structure to store the broken-down time
	tm ltm;

	// Convert 'time_t' to a local time and store it in 'ltm'
	localtime_s(&ltm, &now);

	// Create a string stream to Format the time as: YYYY-MM-DD HH:MM:SS
	std::ostringstream oss;
	oss << std::put_time(&ltm, "%Y-%m-%d %H:%M:%S");

	std::string dateTime = oss.str();

	return dateTime;
}