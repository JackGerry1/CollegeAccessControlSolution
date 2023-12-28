#pragma once
#include "Room.h"
#include <chrono>

class LectureHall : public Room {
public:
    LectureHall(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber)
        : Room(buildingCode, buildingName, floorNumber, roomType, roomNumber) {}

    bool verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState) override;
};