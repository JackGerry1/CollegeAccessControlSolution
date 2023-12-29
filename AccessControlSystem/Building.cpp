//Building.cpp : This file contains functions and attributes specifeid in the Building.h file.

#include "Building.h"
#include "Room.h"

/*
References:
URL: https://cplusplus.com/reference/vector/vector/erase/ Date Accessed: 18/12/23
URL: https://www.scaler.com/topics/cpp-string-replace/ Date Accessed: 18/12/23
URL: https://www.digitalocean.com/community/tutorials/string-find-c-plus-plus 18/12/23
URL: https://en.cppreference.com/w/cpp/types/size_t Date Accessed: 18/12/23
URL: https://www.geeksforgeeks.org/substring-in-cpp/ Date Accessed: 18/12/23
URL: https://www.programiz.com/cpp-programming/file-handling Date Accessed: 14/12/23
*/

// Constructor for the Building class, initializes building properties
Building::Building(std::string buildingCode, std::string buildingName)
	: buildingCode(buildingCode), buildingName(buildingName), buildingState(BuildingState::BUILDING_NORMAL) {
	// Initializes Building object with provided code, name, and sets the building state to normal
}

// Destructor for the Building class
Building::~Building() {
	// Loops through each room in the 'rooms' vector
	for (auto room : rooms) {
		delete room; // Deletes the room object to prevent memory leaks
	}
	rooms.clear(); // Clears the 'rooms' vector after deleting room objects
}

// Function: setBuildingCode
// Parameters: string buildingCode
// Objective: Sets the building code based on the input provided by the user.
void Building::setBuildingCode(const std::string& buildingCode) {
	this->buildingCode = buildingCode;
} // end of setBuildingCode

// Function: getBuildingCode
// Objective: Retrieves the building code.
std::string Building::getBuildingCode() const {
	return buildingCode;
} // end of getBuildingCode

// Function: setBuildingName
// Parameters: const std::string& buildingName
// Objective: Sets the building name using the input provided.
void Building::setBuildingName(const std::string& buildingName) {
	this->buildingName = buildingName;
} // end of setBuildingName

// Function: getBuildingName
// Objective: Retrieves the building name.
std::string Building::getBuildingName() const {
	return buildingName;
} // end of getBuildingName

// Function: addRoom
// Objective: add room to the system based on user input
void Building::addRoom() {
	// Display the current buildings and their information from the log file
	std::cout << "CURRENT BUILDINGS: " << std::endl;
	BuildingStructureLog::displayFileInfo("LogFiles/BuildingInfo.txt");

	// Select a building index to add a room to
	int selectedBuildingIndex;
	std::cout << "Enter the index of the building to add the room to: ";
	std::cin >> selectedBuildingIndex;

	// Gather room details: floor number, room number, and room type
	std::string roomType;
	int floorNumber, roomNumber;

	std::cout << "Enter the floor number: ";
	std::cin >> floorNumber;

	std::cout << "Enter the room number: ";
	std::cin >> roomNumber;

	// if room number less than < 10 append a 0 to the front so 1 becomes 01
	std::string roomNumberStr = (roomNumber < 10) ? "0" + std::to_string(roomNumber) : std::to_string(roomNumber);

	// Display available room types and prompt the user to select one
	std::cout << "Room Types:\n";
	std::cout << "1. Lecture Hall\n";
	std::cout << "2. Teaching Room\n";
	std::cout << "3. Staff Room\n";
	std::cout << "4. Secure Room\n";
	std::cout << "Select room type (enter number): ";
	int roomTypeChoice;
	std::cin >> roomTypeChoice;

	// Based on the user's choice, assign the corresponding room type
	switch (roomTypeChoice) {
	case 1:
		roomType = "Lecture Hall";
		break;
	case 2:
		roomType = "Teaching Room";
		break;
	case 3:
		roomType = "Staff Room";
		break;
	case 4:
		roomType = "Secure Room";
		break;
	default:
		// Display an error message for an invalid room type selection
		std::cout << "Invalid room type selection.\n";
		return; // Abort the function as an invalid choice was made
	}

	// Retrieve building information based on the selected building index
	std::string buildingInfo = BuildingStructureLog::getBuildingInfo(selectedBuildingIndex);

	// Extract the building code from the retrieved building information
	size_t buildingCodeStart = buildingInfo.find("Building Code: ");
	std::string buildingCode = buildingInfo.substr(buildingCodeStart + 15, buildingInfo.find("\n", buildingCodeStart) - buildingCodeStart - 15);

	// Create a new Room object with the obtained building code, floor number, room type, and room number
	Room newRoom(buildingCode, "", floorNumber, roomType, roomNumber);

	// Create a unique label for the room by combining building code, floor number, and room number
	std::string roomLabel = buildingCode + std::to_string(floorNumber) + roomNumberStr;

	// Extract the building name from the retrieved building information
	std::string buildingName = buildingInfo.substr(buildingInfo.find("Building Name: ") + 15, buildingInfo.find(", Building Code:") - buildingInfo.find("Building Name: ") - 15);

	// Set various attributes of the newRoom object
	newRoom.setBuildingName(buildingName);
	newRoom.setRoomNumber(roomNumber);
	newRoom.setFloorNumber(floorNumber);
	newRoom.setRoomType(roomType);
	newRoom.setRoomState(RoomState::ROOM_NORMAL);

	// Construct a string containing detailed room information
	std::string roomInfo = "Building Name: " + newRoom.getBuildingName() + ", Room: " + roomLabel +
		", Room Type: " + newRoom.getRoomType() + ", Room State: " + Room::roomStateToString(newRoom.getRoomState()) +
		", Building State: " + buildingStateToString(BuildingState::BUILDING_NORMAL);

	// Display the room information to the console
	std::cout << roomInfo << std::endl;

	// Log room information to the Building_Structure.txt file
	BuildingStructureLog::logInfo(roomInfo, "LogFiles/Building_Structure.txt");
} // end of addRoom

// Function: removeRoom
// Objective: remove room from system based on room input
void Building::removeRoom() {
	// Reading room data from a file and storing it in a vector
	std::vector<std::string> roomData = BuildingStructureLog::readRoomDataFromFile();

	// Checking if the room data vector is not empty
	if (!roomData.empty()) {
		BuildingStructureLog::displayFileInfo("LogFiles/Building_Structure.txt");

		// Taking room input for the index of the room to remove
		int index;
		std::cout << "Enter the index of the room you want to remove: ";
		std::cin >> index;

		// Removing the room based on the provided index from the log file
		BuildingStructureLog::removeRoomFromLogFile(index);
	}
	else {
		std::cout << "No rooms found in the log file. Nothing to remove.\n\n";
	}
} // end of removeRoom


// Function: buildingStateToString
// Objective: convert enum to string for the building state
std::string Building::buildingStateToString(BuildingState state) {
	// Switch statement to handle different BuildingState cases
	switch (state) {
		// If the state is BUILDING_NORMAL, return "NORMAL"
	case BuildingState::BUILDING_NORMAL:
		return "NORMAL";

		// If the state is BUILDING_EMERGENCY, return "EMERGENCY"
	case BuildingState::BUILDING_EMERGENCY:
		return "EMERGENCY";

		// Default case for unknown or unexpected BuildingState values
	default:
		return "UNKNOWN_BUILDING_STATE";
	}
} // end of buildingStateToString

// Function: changeRoomAndBuildingState
// Objective: to change the room and building states based on the user input and update the log file correctly
void Building::changeRoomAndBuildingState() {
	// Fetch room data from the file
	std::vector<std::string> roomData = BuildingStructureLog::readRoomDataFromFile();

	if (!roomData.empty()) {
		BuildingStructureLog::displayFileInfo("LogFiles/Building_Structure.txt");

		int selectedRoomIndex;
		std::cout << "Select the index of the room to update: ";
		std::cin >> selectedRoomIndex;

		// Check if the selected index is valid
		if (selectedRoomIndex >= 0 && selectedRoomIndex < roomData.size()) {
			// Extract necessary information from the selected room data
			std::string roomInfo = roomData[selectedRoomIndex];

			// Find the start and end positions of the building name within the room information
			size_t buildingNameStart = roomInfo.find("Building Name: ");
			size_t buildingNameEnd = roomInfo.find(", Room: ");

			// Extract the building name from the room information using the identified positions
			std::string buildingName = roomInfo.substr(buildingNameStart + 15, buildingNameEnd - buildingNameStart - 15);

			// Find the start and end positions of the room state within the room information
			size_t roomStateStart = roomInfo.find("Room State: ");
			size_t roomStateEnd = roomInfo.find(", Building State:");

			// Extract the room state as a string from the room information using the identified positions
			std::string roomStateStr = roomInfo.substr(roomStateStart + 12, roomStateEnd - roomStateStart - 12);

			// Toggle the room state between "NORMAL" and "EMERGENCY"
			RoomState newState = (roomStateStr == "NORMAL") ? RoomState::ROOM_EMERGENCY : RoomState::ROOM_NORMAL;

			// Update the room's state in the room information string
			std::string updatedRoomInfo = roomInfo.substr(0, roomStateStart + 12) + Room::roomStateToString(newState) +
				roomInfo.substr(roomStateEnd);

			// Update the selected room's state in the roomData vector
			roomData[selectedRoomIndex] = updatedRoomInfo;

			// Update the building state based on the room states within the same building
			std::string buildingState = Room::roomStateToString(newState);

			// Track changes in building state due to room state changes
			bool buildingStateChanged = false; // Track if any room in this building changed its state
			bool anyRoomInBuildingChanged = false; // Track if any room in the building changed

			// Loop through room data to update building state based on room state changes
			for (size_t i = 0; i < roomData.size(); ++i) {
				size_t currentBuildingNameStart = roomData[i].find("Building Name: ");

				// Check if the room data contains building-related information
				if (currentBuildingNameStart != std::string::npos) {
					size_t currentBuildingNameEnd = roomData[i].find(", Room: ");
					std::string currentBuildingName = roomData[i].substr(currentBuildingNameStart + 15, currentBuildingNameEnd - currentBuildingNameStart - 15);

					// Check if the room belongs to the same building as the selected room
					if (currentBuildingName == buildingName) {
						size_t currentRoomStateStart = roomData[i].find("Room State: ");
						size_t currentRoomStateEnd = roomData[i].find(", Building State:");
						std::string currentRoomStateStr = roomData[i].substr(currentRoomStateStart + 12, currentRoomStateEnd - currentRoomStateStart - 12);

						// Update the room state in the room data for the rooms within the same building
						if (currentRoomStateStr != buildingState) {
							roomData[i] = roomData[i].substr(0, currentRoomStateStart + 12) + buildingState +
								roomData[i].substr(currentRoomStateEnd);
							buildingStateChanged = true; // Flag that a building changed its state
						}

						// Mark if the selected room or any other room in the building changed state
						if (i == static_cast<size_t>(selectedRoomIndex)) {
							anyRoomInBuildingChanged = true; // Selected room changed
						}
					}
				}
			}

			// Update the building state if it has changed or if the selected room changed
			if (buildingStateChanged || anyRoomInBuildingChanged) {
				// Iterate through room data to update the building state for affected rooms
				for (size_t i = 0; i < roomData.size(); ++i) {
					size_t currentBuildingNameStart = roomData[i].find("Building Name: ");

					// Check if the room data contains building-related information
					if (currentBuildingNameStart != std::string::npos) {
						size_t currentBuildingNameEnd = roomData[i].find(", Room: ");
						std::string currentBuildingName = roomData[i].substr(currentBuildingNameStart + 15, currentBuildingNameEnd - currentBuildingNameStart - 15);

						// Check if the room belongs to the same building as the selected room
						if (currentBuildingName == buildingName) {
							size_t buildingStateStart = roomData[i].find("Building State: ");
							// Update the building state for the rooms within the same building
							roomData[i] = roomData[i].substr(0, buildingStateStart + 16) + buildingState;
						}
					}
				}
			}

			// Update the building state in the log file
			BuildingStructureLog::updateRoomDataFile(roomData);
		}
		else {
			std::cout << "Invalid room index selected.\n";
		}
	}
	else {
		std::cout << "No rooms found in the log file.\n\n";
	}

} // end of changeRoomAndBuildingState

void Building::updateRoom() {
	std::vector<std::string> roomData = BuildingStructureLog::readRoomDataFromFile();

	if (!roomData.empty()) {
		BuildingStructureLog::displayFileInfo("LogFiles/Building_Structure.txt"); // Display information from a file

		// Prompt user to select a room index for updating
		int selectedRoomIndex;
		std::cout << "Select the index of the room to update: ";
		std::cin >> selectedRoomIndex;

		// Check if the selected index is within range
		if (selectedRoomIndex >= 0 && selectedRoomIndex < roomData.size()) {

			// Extract room information based on the selected index
			std::string roomInfo = roomData[selectedRoomIndex];

			// Variables to hold various room details
			std::string buildingName;
			std::string roomNumber;
			std::string roomType;
			std::string roomState;
			std::string buildingState;

			// Find the position of "Building Name: " in the room information
			size_t buildingNamePos = roomInfo.find("Building Name: ");
			if (buildingNamePos != std::string::npos) {
				// Find the position of ", Room: " in the room information
				size_t roomPos = roomInfo.find(", Room: ");
				if (roomPos != std::string::npos) {
					// Extract building name and room number
					buildingName = roomInfo.substr(buildingNamePos + 15, roomPos - (buildingNamePos + 15));
					roomNumber = roomInfo.substr(roomPos + 8, roomInfo.find(", Room Type: ") - (roomPos + 8)); // Adjust based on the expected structure

					// Find the position of "Room Type: " in the room information
					size_t roomTypePos = roomInfo.find("Room Type: ");
					if (roomTypePos != std::string::npos) {
						// Find the position of ", Room State: " in the room information
						size_t roomStatePos = roomInfo.find(", Room State: ");
						if (roomStatePos != std::string::npos) {
							// Find the position of ", Building State: " in the room information
							size_t buildingStatePos = roomInfo.find(", Building State: ");
							if (buildingStatePos != std::string::npos) {
								// Extract room type, room state, and building state from roomInfo
								roomType = roomInfo.substr(roomTypePos + 11, roomStatePos - (roomTypePos + 11));
								roomState = roomInfo.substr(roomStatePos + 14, buildingStatePos - (roomStatePos + 14));
								buildingState = roomInfo.substr(buildingStatePos + 18);
							}
						}
					}
				}
			}

			// Variable to store user input for floor update
			std::string floorUpdate;

			// Prompt the user whether they want to update the floor number or leave it unchanged
			std::cout << "Do you want to update the floor number? (Leave blank to keep unchanged): ";

			// Clear the newline character from the input buffer to avoid unexpected behavior in getline
			std::cin.ignore();

			// Read the user's input, allowing for updating the floor number
			std::getline(std::cin, floorUpdate);

			// Check if the user input is not empty, is a single character, and is a digit
			if (!floorUpdate.empty() && floorUpdate.length() == 1 && isdigit(floorUpdate[0])) {
				// Convert the character digit to its integer equivalent
				int newFloor = floorUpdate[0] - '0';

				// Check if the new floor number is within the valid range (0-9)
				if (newFloor >= 0 && newFloor <= 9) {
					// Update the third character (representing the floor digit) in the room number
					roomNumber[2] = floorUpdate[0];
					std::cout << "Floor number updated to: " << floorUpdate << std::endl;
				}
				else {
					// Inform the user about an invalid floor number and keep the floor number unchanged
					std::cout << "Invalid floor number. Floor number remains unchanged.\n";
				}
			}

			// Variable to store user input to determine whether the user wants to update the room number
			std::string updateRoomNumber;

			// Prompt the user if they want to update the room number
			std::cout << "Do you want to update the room number? (yes/no): ";
			std::cin >> updateRoomNumber;

			// Check if the user wants to update the room number
			if (updateRoomNumber == "yes") {
				std::string roomUpdate;
				std::cout << "Enter the new room number: ";

				// Clear the newline character from the input buffer
				std::cin.ignore();

				// Read the user's input for the new room number
				std::getline(std::cin, roomUpdate);

				// Check if the user input is not empty
				if (!roomUpdate.empty()) {
					// Convert the user input string to an integer
					int newRoomNumber = std::stoi(roomUpdate);

					// Check if the entered room number is within the valid range (0-99)
					if (newRoomNumber >= 0 && newRoomNumber < 100) {
						std::string buildingCode = roomNumber.substr(0, 3); // Extract the building code from the room number
						std::string newRoomStr = (newRoomNumber < 10) ? "0" + std::to_string(newRoomNumber) : std::to_string(newRoomNumber);

						// Pad single-digit room numbers with a leading zero
						if (newRoomNumber < 10) {
							roomNumber = buildingCode + "0" + std::to_string(newRoomNumber);
						}
						else {
							roomNumber = buildingCode + std::to_string(newRoomNumber);
						}

						// Inform the user about the successful update of the room number
						std::cout << "Room number updated to: " << roomNumber << std::endl;
					}
					else {
						// Inform the user about an invalid room number and keep the room number unchanged
						std::cout << "Invalid room number. Room number remains unchanged.\n";
					}
				}
			}

			// Variable to store user input to determine whether the user wants to update the room type
			std::string typeUpdate;

			// Prompt the user if they want to update the room type
			std::cout << "Do you want to update the room type? (yes/no): ";
			std::cin >> typeUpdate;

			// Check if the user wants to update the room type
			if (typeUpdate == "yes") {
				// Display available room types for the user to choose from
				std::cout << "Available room types:\n";
				std::cout << "1. Lecture Hall\n";
				std::cout << "2. Teaching Room\n";
				std::cout << "3. Staff Room\n";
				std::cout << "4. Secure Room\n";

				int selectedType;
				std::cout << "Enter the number corresponding to the new room type: ";
				std::cin >> selectedType;

				// Update room type based on the user's selected type
				switch (selectedType) {
				case 1:
					roomType = "Lecture Hall";
					break;
				case 2:
					roomType = "Teaching Room";
					break;
				case 3:
					roomType = "Staff Room";
					break;
				case 4:
					roomType = "Secure Room";
					break;
				default:
					// Inform the user about an invalid room type selection
					std::cout << "Invalid room type selection. Room type remains unchanged.\n";
					break;
				}

				// Check if the selected type is within the valid range and inform the user about the updated room type
				if (selectedType >= 1 && selectedType <= 4) {
					std::cout << "Room type updated to: " << roomType << std::endl;
				}
			}
			else {
				// Inform the user that the room type remains unchanged
				std::cout << "Room type remains unchanged.\n";
			}


			// Assign the updated room information to roomInfoOutput variable
			std::string roomInfoOutput = "Building Name: " + buildingName + ", Room: " + roomNumber + ", Room Type: " + roomType
				+ ", Room State: " + roomState + ", Building State: " + buildingState;

			// update the index with the updated info
			roomData[selectedRoomIndex] = roomInfoOutput;

			// log updated info to a log file. 
			std::cout << "Updated Room Info: " << roomInfoOutput + '\n';
			BuildingStructureLog::updateRoomDataFile(roomData);
		}
	}
	else {
		std::cout << "No rooms found in the log file.\n\n";
	}
} // end of updateRoom

// Function: addBuilding
// Objective: add a building based on user input
void Building::addBuilding() {
	// Display existing buildings from the log file before adding a new one
	std::cout << "CURRENT BUILDINGS: " << std::endl;
	BuildingStructureLog::displayFileInfo("LogFiles/BuildingInfo.txt");

	std::string code, name;

	// Prompt user for building name and set it
	std::cout << "Enter building name: ";
	std::cin >> name;
	setBuildingName(name);

	// Prompt user for building code and set it
	std::cout << "Enter building code: ";
	std::cin >> code;
	setBuildingCode(code);

	// Check for duplicates based on building name and code
	if (!BuildingStructureLog::isDuplicate(getBuildingName(), getBuildingCode())) {
		// Create building information string with the name and code
		std::string buildingInfo = "Building Name: " + getBuildingName() + ", Building Code: " + getBuildingCode();

		// Log building information to the file
		BuildingStructureLog::logInfo(buildingInfo, "LogFiles/BuildingInfo.txt");

		// Output the added building information to the console
		std::cout << "Added Building: " << buildingInfo + "\n";
	}
	else {
		// Notify if a building with the same name or code already exists
		std::cout << "Building with the same name or code already exists. Not added to log.\n";
	}
} // end of addBuilding



