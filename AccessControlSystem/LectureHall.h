//LectureHall.h: This file contains functions and attributes for the LectureHall class. 


#pragma once

#include "Room.h"  
#include <chrono>  

// Class LectureHall: Inherits from the Room class
class LectureHall : public Room {
public:
    // Constructor: Initializes LectureHall object inheriting from Room
    LectureHall(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber)
        : Room(buildingCode, buildingName, floorNumber, roomType, roomNumber) {}

    // Function: verifyEntryRequirementsOverride method to verify access requirements for the LectureHall.
    // Evaluates if access is permitted based on user roles and room state.
    bool verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState) override;
};
