// BuildingStructureLog.h: This header file declares the BuildingStructureLog class, which manages building-related log operations.

#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include "Building.h"

// Declaration of BuildingStructureLog class containing static methods
class BuildingStructureLog {
public:
    // Check if a building with the provided name and code already exists in the log
    static bool isDuplicate(const std::string& name, const std::string& code);

    // Log building information to a specified file location
    static void logInfo(const std::string& buildingInfo, const std::string& fileLocation);

    // Display information stored in a file at a given location
    static void displayFileInfo(const std::string& fileLocation);

    // Retrieve building information at a specified index
    static std::string getBuildingInfo(int index);

    // Read room data from a file and return as a vector of strings
    static std::vector<std::string> readRoomDataFromFile();

    // Remove room information at a given index from the log file
    static void removeRoomFromLogFile(int index);

    // Update the room data file with the provided updated room data
    static void updateRoomDataFile(const std::vector<std::string>& updatedRoomData);
};
