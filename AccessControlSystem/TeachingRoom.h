// TeachingRoom.h: This file contains functions and attributes for the TeachingRoom class. 

#pragma once
#include "Room.h"
#include <chrono>

// TeachingRoom class, inheriting from the Room base class
class TeachingRoom : public Room {
public:
    // Constructor for TeachingRoom, initializes using Room's constructor
    TeachingRoom(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber)
        : Room(buildingCode, buildingName, floorNumber, roomType, roomNumber) {}

    // Override function to verify entry requirements based on formatted roles and room state
    bool verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState) override;
};