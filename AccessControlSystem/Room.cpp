//Room.cpp : This file contains functions and attributes specifeid in the Room.h file.

#include "Room.h"

// Constructor for the Room class, initializes Room properties, such as floor number roomType, and roomNumber
Room::Room(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber)
    : Building(buildingCode, buildingName), floorNumber(floorNumber), roomType(roomType), roomNumber(roomNumber), roomState(RoomState::ROOM_NORMAL) {}

// Destructor: ~Room
// Objective: Performs cleanup when the Room object is destroyed, if needed.
Room::~Room() {
    // Cleanup, if needed
}

// Function: roomStateToString
// Parameters: state - RoomState enum representing the state of the room
// Objective: Converts the RoomState enum value to its corresponding string representation.
std::string Room::roomStateToString(RoomState state) {
    switch (state) {
    case RoomState::ROOM_NORMAL:
        return "NORMAL";
    case RoomState::ROOM_EMERGENCY:
        return "EMERGENCY";
    default:
        return "UNKNOWN_ROOM_STATE";
    }
} // end of roomStateToString

// Function: verifyEntryRequirements
// Objective: Placeholder function to verify entry requirements for the room.
//            Actual logic for entry requirement verification should replace the placeholder return value.
bool Room::verifyEntryRequirements() {
    // Placeholder logic for verifying entry requirements.
    // Replace the 'true' return value with the actual verification logic.
    return true; // Placeholder return value, replace with actual logic
} // end of verifyEntryRequirements


// Function: setFloorNumber
// Parameters: int floorNumber
// Objective: Set the floor number of the room based on the input provided.
void Room::setFloorNumber(int floorNumber) {
    this->floorNumber = floorNumber;
} // end of setFloorNumber

// Function: getFloorNumber
// Objective: Retrieve the floor number of the room.
int Room::getFloorNumber() const {
    return floorNumber;
} // end of getFloorNumber

// Function: setRoomType
// Parameters: const std::string& roomType
// Objective: Set the room type using the input provided.
void Room::setRoomType(const std::string& roomType) {
    this->roomType = roomType;
} // end of setRoomType

// Function: getRoomType
// Objective: Retrieve the room type.
std::string Room::getRoomType() const {
    return roomType;
} // end of getRoomType

// Function: setRoomNumber
// Parameters: int roomNumber
// Objective: Set the room number based on the input provided.
void Room::setRoomNumber(int roomNumber) {
    this->roomNumber = roomNumber;
} // end of setRoomNumber

// Function: getRoomNumber
// Objective: Retrieve the room number.
int Room::getRoomNumber() const {
    return roomNumber;
} // end of getRoomNumber

// Function: setRoomState
// Parameters: RoomState roomState
// Objective: Set the room state based on the input provided.
void Room::setRoomState(RoomState roomState) {
    this->roomState = roomState;
} // end of setRoomState

// Function: getRoomState
// Objective: Retrieve the room state.
RoomState Room::getRoomState() const {
    return roomState;
} // end of getRoomState

