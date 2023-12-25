#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "BuildingStructureLog.h"

enum class BuildingState {
    BUILDING_NORMAL,
    BUILDING_EMERGENCY
};

class Room; // Forward declaration

class Building {
private:
    std::string buildingCode;
    std::string buildingName;
    BuildingState buildingState;
    std::vector<Room*> rooms;

public:
    Building(std::string buildingCode, std::string buildingName);
    ~Building();

    void addRoom();
    void removeRoom();
    void updateRoom();
    void changeRoomAndBuildingState();
    void addBuilding();

    
    static std::string buildingStateToString(BuildingState state);
    // Getters and setters
    void setBuildingCode(const std::string& buildingCode);
    std::string getBuildingCode() const;

    void setBuildingName(const std::string& buildingName);
    std::string getBuildingName() const;

    // Other getters/setters
};

