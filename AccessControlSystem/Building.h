// Building.h: This file defines functions and attributes for the Building class.

#pragma once

// Header files necessary for this class
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>
#include "BuildingStructureLog.h" // Assuming this file contains additional functionality related to building structures

// Enum to represent the state of a building (Normal or Emergency)
enum class BuildingState {
    BUILDING_NORMAL,
    BUILDING_EMERGENCY
};

// Forward declaration of the Room class to avoid circular dependencies
class Room;

// Declaration of the Building class
class Building {
private:
    std::string buildingCode; // Unique code for the building
    std::string buildingName; // Name of the building
    BuildingState buildingState; // Current state of the building (Normal or Emergency)
    std::vector<Room*> rooms; // Collection of rooms in the building

public:
    // Constructor accepting building code and name
    Building(std::string buildingCode, std::string buildingName);

    // Destructor to clean up memory (if required)
    ~Building();

    // Functions to perform various operations on rooms in the building
    void addRoom(); // Adds a new room to the building
    void removeRoom(); // Removes a room from the building
    void updateRoom(); // Updates details of a room in the building
    void changeRoomAndBuildingState(); // Changes state of rooms or the entire building
    void addBuilding(); // Adds a new building to the system

    // Static method to convert BuildingState enum to string representation
    static std::string buildingStateToString(BuildingState state);

    // Getters and setters for buildingCode and buildingName
    void setBuildingCode(const std::string& buildingCode);
    std::string getBuildingCode() const;

    void setBuildingName(const std::string& buildingName);
    std::string getBuildingName() const;

};


