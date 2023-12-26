#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include "Building.h"

class BuildingStructureLog {
public:
    static bool isDuplicate(const std::string& name, const std::string& code);
    static void logInfo(const std::string& buildingInfo, const std::string& fileLocation);
    static void displayFileInfo(const std::string& fileLocation);
    static std::string getBuildingInfo(int index);
    static std::vector<std::string> readRoomDataFromFile();
    static void removeRoomFromLogFile(int index);
    static void updateRoomDataFile(const std::vector<std::string>& updatedRoomData);
};
