#include "Building.h"
#include "Room.h"

Building::Building(std::string buildingCode, std::string buildingName)
	: buildingCode(buildingCode), buildingName(buildingName), buildingState(BuildingState::BUILDING_NORMAL) {}


Building::~Building() {
	for (auto room : rooms) {
		delete room;
	}
	rooms.clear();
}

void Building::addRoom() {
	std::cout << "CURRENT BUILDINGS: " << std::endl;
	BuildingStructureLog::displayFileInfo("LogFiles/BuildingInfo.txt"); // Display current log before adding a room

	int selectedBuildingIndex;
	std::cout << "Enter the index of the building to add the room to: ";
	std::cin >> selectedBuildingIndex;

	std::string roomType;
	int floorNumber, roomNumber;

	std::cout << "Enter the floor number: ";
	std::cin >> floorNumber;

	std::cout << "Enter the room number: ";
	std::cin >> roomNumber;
	std::string roomNumberStr = (roomNumber < 10) ? "0" + std::to_string(roomNumber) : std::to_string(roomNumber);

	std::cout << "Room Types:\n";
	std::cout << "1. Lecture Hall\n";
	std::cout << "2. Teaching Room\n";
	std::cout << "3. Staff Room\n";
	std::cout << "4. Secure Room\n";
	std::cout << "Select room type (enter number): ";
	int roomTypeChoice;
	std::cin >> roomTypeChoice;

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
		std::cout << "Invalid room type selection.\n";
		return;
	}

	// Get building code
	std::string buildingInfo = BuildingStructureLog::getBuildingInfo(selectedBuildingIndex);
	size_t buildingCodeStart = buildingInfo.find("Building Code: ");
	std::string buildingCode = buildingInfo.substr(buildingCodeStart + 15, buildingInfo.find("\n", buildingCodeStart) - buildingCodeStart - 15);

	Room newRoom(buildingCode, "", floorNumber, roomType, roomNumber);
	std::string roomLabel = buildingCode + std::to_string(floorNumber) + roomNumberStr;

	// Construct room information
	std::string buildingName = buildingInfo.substr(buildingInfo.find("Building Name: ") + 15, buildingInfo.find(", Building Code:") - buildingInfo.find("Building Name: ") - 15);

	newRoom.setBuildingName(buildingName);
	newRoom.setRoomNumber(roomNumber);
	newRoom.setFloorNumber(floorNumber);
	newRoom.setRoomType(roomType);
	newRoom.setRoomState(RoomState::ROOM_NORMAL);

	std::string roomInfo = "Building Name: " + newRoom.getBuildingName() + ", Room: " + roomLabel +
		", Room Type: " + newRoom.getRoomType() + ", Room State: " + Room::roomStateToString(newRoom.getRoomState()) +
		", Building State: " + buildingStateToString(BuildingState::BUILDING_NORMAL);

	std::cout << roomInfo << std::endl;

	// Log room information
	BuildingStructureLog::logInfo(roomInfo, "LogFiles/Building_Structure.txt");
}


void Building::removeRoom() {
	// Reading user data from a file and storing it in a vector
	std::vector<std::string> userData = BuildingStructureLog::readRoomDataFromFile();

	// Checking if the user data vector is not empty
	if (!userData.empty()) {
		BuildingStructureLog::displayFileInfo("LogFiles/Building_Structure.txt");

		// Taking user input for the index of the user to remove
		int index;
		std::cout << "Enter the index of the user you want to remove: ";
		std::cin >> index;

		// Removing the user based on the provided index from the log file
		BuildingStructureLog::removeRoomFromLogFile(index);
	}
	else {
		std::cout << "No users found in the log file. Nothing to remove.\n\n";
	}
}


std::string Building::buildingStateToString(BuildingState state) {
	switch (state) {
	case BuildingState::BUILDING_NORMAL:
		return "NORMAL";
	case BuildingState::BUILDING_EMERGENCY:
		return "EMERGENCY";
	default:
		return "UNKNOWN_BUILDING_STATE";
	}
}

void Building::changeRoomAndBuildingState() {
	// Fetch room data from the file
	std::vector<std::string> roomData = BuildingStructureLog::readRoomDataFromFile();

	// Display available rooms for user selection
	std::cout << "Available rooms:\n";
	for (size_t i = 0; i < roomData.size(); ++i) {
		std::cout << i << ". " << roomData[i] << '\n';
	}

	int selectedRoomIndex;
	std::cout << "Select the index of the room to update: ";
	std::cin >> selectedRoomIndex;

	// Check if the selected index is valid
	if (selectedRoomIndex >= 0 && selectedRoomIndex < roomData.size()) {
		std::string roomInfo = roomData[selectedRoomIndex];
		size_t buildingNameStart = roomInfo.find("Building Name: ");
		size_t buildingNameEnd = roomInfo.find(", Room: ");
		std::string buildingName = roomInfo.substr(buildingNameStart + 15, buildingNameEnd - buildingNameStart - 15);

		size_t roomStateStart = roomInfo.find("Room State: ");
		size_t roomStateEnd = roomInfo.find(", Building State:");
		std::string roomStateStr = roomInfo.substr(roomStateStart + 12, roomStateEnd - roomStateStart - 12);

		// Toggle room state
		RoomState newState = (roomStateStr == "NORMAL") ? RoomState::ROOM_EMERGENCY : RoomState::ROOM_NORMAL;

		// Update room state in the room information string
		std::string updatedRoomInfo = roomInfo.substr(0, roomStateStart + 12) + Room::roomStateToString(newState) +
			roomInfo.substr(roomStateEnd);

		// Update the selected room's state
		roomData[selectedRoomIndex] = updatedRoomInfo;

		// Update the building state based on room states within the same building
		std::string buildingState = Room::roomStateToString(newState);

		// Track whether any room within the building has changed its state
		bool buildingStateChanged = false;
		bool anyRoomInBuildingChanged = false; // Track if any room in the building changed

		for (size_t i = 0; i < roomData.size(); ++i) {
			size_t currentBuildingNameStart = roomData[i].find("Building Name: ");
			if (currentBuildingNameStart != std::string::npos) {
				size_t currentBuildingNameEnd = roomData[i].find(", Room: ");
				std::string currentBuildingName = roomData[i].substr(currentBuildingNameStart + 15, currentBuildingNameEnd - currentBuildingNameStart - 15);

				if (currentBuildingName == buildingName) {
					size_t currentRoomStateStart = roomData[i].find("Room State: ");
					size_t currentRoomStateEnd = roomData[i].find(", Building State:");
					std::string currentRoomStateStr = roomData[i].substr(currentRoomStateStart + 12, currentRoomStateEnd - currentRoomStateStart - 12);

					if (currentRoomStateStr != buildingState) {
						roomData[i] = roomData[i].substr(0, currentRoomStateStart + 12) + buildingState +
							roomData[i].substr(currentRoomStateEnd);
						buildingStateChanged = true; // Update flag since a room in this building changed
					}

					if (i == static_cast<size_t>(selectedRoomIndex)) {
						anyRoomInBuildingChanged = true; // Mark if the selected room changed
					}
				}
			}
		}

		// Update the building state if it has changed or if the selected room changed
		if (buildingStateChanged || anyRoomInBuildingChanged) {
			for (size_t i = 0; i < roomData.size(); ++i) {
				size_t currentBuildingNameStart = roomData[i].find("Building Name: ");
				if (currentBuildingNameStart != std::string::npos) {
					size_t currentBuildingNameEnd = roomData[i].find(", Room: ");
					std::string currentBuildingName = roomData[i].substr(currentBuildingNameStart + 15, currentBuildingNameEnd - currentBuildingNameStart - 15);

					if (currentBuildingName == buildingName) {
						size_t buildingStateStart = roomData[i].find("Building State: ");
						roomData[i] = roomData[i].substr(0, buildingStateStart + 16) + buildingState;
					}
				}
			}
		}
		BuildingStructureLog::updateStates(roomData);
	}
	else {
		std::cout << "Invalid room index selected.\n";
	}
}

void Building::updateRoom() {
	std::vector<std::string> roomData = BuildingStructureLog::readRoomDataFromFile();

	if (!roomData.empty()) {
		BuildingStructureLog::displayFileInfo("LogFiles/Building_Structure.txt");

		int selectedRoomIndex;
		std::cout << "Select the index of the room to update: ";
		std::cin >> selectedRoomIndex;

		if (selectedRoomIndex >= 0 && selectedRoomIndex < roomData.size()) {
			std::string roomInfo = roomData[selectedRoomIndex];

			std::string buildingName;
			std::string roomNumber;
			std::string roomType;
			std::string roomState;
			std::string buildingState;

			size_t buildingNamePos = roomInfo.find("Building Name: ");
			if (buildingNamePos != std::string::npos) {
				size_t roomPos = roomInfo.find(", Room: ");
				if (roomPos != std::string::npos) {
					buildingName = roomInfo.substr(buildingNamePos + 15, roomPos - (buildingNamePos + 15));
					roomNumber = roomInfo.substr(roomPos + 8, roomInfo.find(", Room Type: ") - (roomPos + 8)); // Adjust based on the expected structure

					size_t roomTypePos = roomInfo.find("Room Type: ");
					if (roomTypePos != std::string::npos) {
						size_t roomStatePos = roomInfo.find(", Room State: ");
						if (roomStatePos != std::string::npos) {
							size_t buildingStatePos = roomInfo.find(", Building State: ");
							if (buildingStatePos != std::string::npos) {
								roomType = roomInfo.substr(roomTypePos + 11, roomStatePos - (roomTypePos + 11));
								roomState = roomInfo.substr(roomStatePos + 14, buildingStatePos - (roomStatePos + 14));
								buildingState = roomInfo.substr(buildingStatePos + 18);
							}
						}
					}
				}
			}
			
			std::string floorUpdate;
			std::cout << "Do you want to update the floor number? (Leave blank to keep unchanged): ";
			std::cin.ignore(); // Clear newline character from buffer
			std::getline(std::cin, floorUpdate);

			if (!floorUpdate.empty() && floorUpdate.length() == 1 && isdigit(floorUpdate[0])) {
				// Validate if the entered floor number is a digit and within the range 0-9
				int newFloor = floorUpdate[0] - '0'; // Convert char to integer

				if (newFloor >= 0 && newFloor <= 9) {
					// Update the floor number in the room info
					roomNumber[2] = floorUpdate[0];
					std::cout << "Floor number updated to: " << floorUpdate << std::endl;
				}
				else {
					std::cout << "Invalid floor number. Floor number remains unchanged.\n";
				}
			}

			std::string updateRoomNumber;
			std::cout << "Do you want to update the room number? (yes/no): ";
			std::cin >> updateRoomNumber;

			if (updateRoomNumber == "yes") {
				std::string roomUpdate;
				std::cout << "Enter the new room number: ";
				std::cin.ignore(); // Clear newline character from buffer
				std::getline(std::cin, roomUpdate);

				if (!roomUpdate.empty()) {
					int newRoomNumber = std::stoi(roomUpdate);
					if (newRoomNumber >= 0 && newRoomNumber < 100) { // Considering valid room numbers are between 0 and 99
						std::string buildingCode = roomNumber.substr(0, 3); // Extract building code
						std::string newRoomStr = (newRoomNumber < 10) ? "0" + std::to_string(newRoomNumber) : std::to_string(newRoomNumber);

						if (newRoomNumber < 10) {
							// Pad single-digit room numbers with leading zero
							roomNumber = buildingCode + "0" + std::to_string(newRoomNumber);
						}
						else {
							roomNumber = buildingCode + std::to_string(newRoomNumber);
						}

						std::cout << "Room number updated to: " << roomNumber << std::endl;
					}
					else {
						std::cout << "Invalid room number. Room number remains unchanged.\n";
					}
				}
			}

			std::string typeUpdate;
			std::cout << "Do you want to update the room type? (yes/no): ";
			std::cin >> typeUpdate;

			if (typeUpdate == "yes") {
				std::cout << "Available room types:\n";
				std::cout << "1. Lecture Hall\n";
				std::cout << "2. Teaching Room\n";
				std::cout << "3. Staff Room\n";
				std::cout << "4. Secure Room\n";

				int selectedType;
				std::cout << "Enter the number corresponding to the new room type: ";
				std::cin >> selectedType;

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
					std::cout << "Invalid room type selection. Room type remains unchanged.\n";
					break;
				}

				if (selectedType >= 1 && selectedType <= 4) {
					std::cout << "Room type updated to: " << roomType << std::endl;
				}
			}
			else {
				std::cout << "Room type remains unchanged.\n";
			}

			// Assign the updated room information to roomInfoOutput variable
			std::string roomInfoOutput = "Building Name: " + buildingName + ", Room: " + roomNumber + ", Room Type: " + roomType
				+ ", Room State: " + roomState + ", Building State: " + buildingState;

			// update the index with the updated info
			roomData[selectedRoomIndex] = roomInfoOutput;

			std::cout << "Updated Room Info: " << roomInfoOutput + '\n';
			BuildingStructureLog::updateRoomDataFile(roomData);
		}
	}
	else {
		std::cout << "No rooms found in the log file.\n\n";
	}
}

void Building::addBuilding() {
	std::cout << "CURRENT BUILDINGS: " << std::endl;
	BuildingStructureLog::displayFileInfo("LogFiles/BuildingInfo.txt"); // Display current log before adding new building

	std::string code, name;

	std::cout << "Enter building name: ";
	std::cin >> name;
	setBuildingName(name);

	std::cout << "Enter building code: ";
	std::cin >> code;
	setBuildingCode(code);

	if (!BuildingStructureLog::isDuplicate(getBuildingName(), getBuildingCode())) {
		std::string buildingInfo = "Building Name: " + getBuildingName() + ", Building Code: " + getBuildingCode();

		BuildingStructureLog::logInfo(buildingInfo, "LogFiles/BuildingInfo.txt");

		std::cout << "Added Building: " << buildingInfo + "\n"; // Output the building info to the console
	}
	else {
		std::cout << "Building with the same name or code already exists. Not added to log.\n";
	}
}

void Building::setBuildingCode(const std::string& buildingCode) {
	this->buildingCode = buildingCode;
}

std::string Building::getBuildingCode() const {
	return buildingCode;
}

void Building::setBuildingName(const std::string& buildingName) {
	this->buildingName = buildingName;
}

std::string Building::getBuildingName() const {
	return buildingName;
}
