#include "BuildingStructureLog.h"

void BuildingStructureLog::logInfo(const std::string& buildingInfo, const std::string& fileLocation) {
    std::ofstream outFile(fileLocation, std::ios::app);
    if (outFile.is_open()) {
        outFile << buildingInfo << std::endl;
        outFile.close();
        std::cout << "Building information logged to file.\n";
    }
    else {
        std::cout << "Unable to open file.\n";
    }
}

void BuildingStructureLog::displayFileInfo(const std::string& fileLocation) {
    std::ifstream inFile(fileLocation);
    std::string line;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    }
    else {
        std::cout << "Unable to open file.\n";
    }
}


bool BuildingStructureLog::isDuplicate(const std::string& name, const std::string& code) {
    std::ifstream inFile("LogFiles/BuildingInfo.txt");
    std::string line;

    while (std::getline(inFile, line)) {
        // Check for duplicate name or code in the log
        if (line.find("Building Name: " + name) != std::string::npos ||
            line.find("Building Code: " + code) != std::string::npos) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

std::vector<std::string> BuildingStructureLog::readRoomDataFromFile() {
    std::ifstream inputFile("LogFiles/Building_Structure.txt");
    std::vector<std::string> roomData;

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            roomData.push_back(line);
        }
        inputFile.close();
    }
    else {
        std::cerr << "Unable to open file\n";
    }
    return roomData;
}

void BuildingStructureLog::removeRoomFromLogFile(int index) {
    std::vector<std::string> roomData = readRoomDataFromFile();

    if (index >= 0 && index < roomData.size()) {
        std::cout << "Removing room: " << roomData[index] << std::endl;

        roomData.erase(roomData.begin() + index);

        std::ofstream outputFile("LogFiles/Building_Structure.txt", std::ios::trunc);
        if (outputFile.is_open()) {
            for (const std::string& room : roomData) {
                outputFile << room << "\n";
            }
            outputFile.close();

            std::cout << "Room removed from the log file.\n";
        }
        else {
            std::cerr << "Unable to open file\n";
        }
    }
    else {
        std::cout << "Invalid index.\n";
    }
}

std::string BuildingStructureLog::getBuildingInfo(int index) {
    std::ifstream inFile("LogFiles/BuildingInfo.txt");
    std::string line;
    int currentIndex = 0;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            if (currentIndex == index) {
                inFile.close();
                return line; // Return the building info at the specified index
            }
            currentIndex++;
        }
        inFile.close();
    }
    else {
        std::cout << "Unable to open file.\n";
    }

    return ""; // Return an empty string if the index is out of range or file couldn't be opened
}

void BuildingStructureLog::updateRoomDataFile(const std::vector<std::string>& updatedRoomData) {
    std::ofstream outputFile("LogFiles/Building_Structure.txt", std::ios::trunc); // Open file in truncation mode to clear its contents

    if (outputFile.is_open()) {
        for (const std::string& room : updatedRoomData) {
            outputFile << room << "\n"; // Write each updated room data to the file
        }
        outputFile.close(); // Close the file after writing
        std::cout << "Room data updated in the log file.\n";
    }
    else {
        std::cerr << "Unable to open file\n"; // Display an error message if the file couldn't be opened
    }
}