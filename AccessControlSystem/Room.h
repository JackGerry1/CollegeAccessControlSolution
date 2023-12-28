// Room.h: This file defines functions and attributes for the Room class.

#pragma once
#include <string>
#include "Building.h"

// Enum representing the state of a room
enum class RoomState {
    ROOM_NORMAL,    // Represents a room in a normal state
    ROOM_EMERGENCY  // Represents a room in an emergency state
};

// Room class inheriting from Building
class Room : public Building {
private:
    int floorNumber;      // Floor number of the room
    std::string roomType; // Type of the room (e.g., Lecture Hall, Teaching Room)
    int roomNumber;       // Room number within the building
    RoomState roomState;  // State of the room (normal or emergency)

public:
    // Constructor initializing Room object with building details, floor number, room type, and room number
    Room(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber);

    // Destructor to handle cleanup if needed
    ~Room();

    // Method to verify the entry requirements for the room
    virtual bool verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState);

    // Method to convert RoomState enum value to its corresponding string representation
    static std::string roomStateToString(RoomState state);

    // Getters and setters for room attributes
    void setFloorNumber(int floorNumber);
    int getFloorNumber() const;

    void setRoomType(const std::string& roomType);
    std::string getRoomType() const;

    void setRoomNumber(int roomNumber);
    int getRoomNumber() const;

    void setRoomState(RoomState roomState);
    RoomState getRoomState() const;
};


