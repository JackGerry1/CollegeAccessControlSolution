// SecureRoom.h: This file contains functions and attributes for the SecureRoom class. 

#pragma once
#include "Room.h"
#include <chrono>

// Class SecureRoom: Inherits from the Room class
class SecureRoom : public Room
{
public:
    // Constructor: Initializes SecureRoom object inheriting from Room
    SecureRoom(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber)
        : Room(buildingCode, buildingName, floorNumber, roomType, roomNumber) {}

    // Function: verifyEntryRequirementsOverride method to verify access requirements for the SecureRoom.
    // Evaluates if access is permitted based on user roles and room state.
    bool verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState) override;
};

