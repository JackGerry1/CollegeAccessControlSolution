// StaffRoom.h: This file defines functions and attributes for the StaffRoom class.

#pragma once
#include "Room.h"
#include <chrono>

// StaffRoom class, inheriting from the Room base class
class StaffRoom : public Room
{
public:
    // Constructor for StaffRoom
    StaffRoom(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber)
        : Room(buildingCode, buildingName, floorNumber, roomType, roomNumber) {}

    // Override function to verify entry requirements
    // Takes formattedRoles and roomState as parameters
    bool verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState) override;
};
