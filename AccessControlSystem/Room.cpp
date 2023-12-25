#include "Room.h"

Room::Room(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber)
    : Building(buildingCode, buildingName), floorNumber(floorNumber), roomType(roomType), roomNumber(roomNumber), roomState(RoomState::ROOM_NORMAL) {}

Room::~Room() {
    // Cleanup, if needed
}
std::string Room::roomStateToString(RoomState state) {
    switch (state) {
    case RoomState::ROOM_NORMAL:
        return "NORMAL";
    case RoomState::ROOM_EMERGENCY:
        return "EMERGENCY";
    default:
        return "UNKNOWN_ROOM_STATE";
    }
}
bool Room::verifyEntryRequirements() {
    // Verify entry requirements logic
    return true; // Placeholder return value, replace with actual logic
}

void Room::setFloorNumber(int floorNumber) {
    this->floorNumber = floorNumber;
}

int Room::getFloorNumber() const {
    return floorNumber;
}

void Room::setRoomType(const std::string& roomType) {
    this->roomType = roomType;
}

std::string Room::getRoomType() const {
    return roomType;
}

void Room::setRoomNumber(int roomNumber) {
    this->roomNumber = roomNumber;
}

int Room::getRoomNumber() const {
    return roomNumber;
}

void Room::setRoomState(RoomState roomState) {
    this->roomState = roomState;
}

RoomState Room::getRoomState() const {
    return roomState;
}
