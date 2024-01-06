//BuildingStructureLog.cpp : This file contains functions and attributes specifeid in the Room.h file.

#include "BuildingStructureLog.h"

/*
References:
Cplusplus.com (2023) 'std::vector::erase', Cplusplus.com.
Available at: https://cplusplus.com/reference/vector/vector/erase/ [Accessed 18th December 2023].

Programiz (2023a) 'C++ File Handling', Programiz.
Available at: https://www.programiz.com/cpp-programming/file-handling [Accessed 14th December 2023].

Sinha, A. (2022). string::npos in C++. [Online] CodeSpeedy.
Available at: https://www.codespeedy.com/stringnpos-in-cpp/ [Accessed 18th December 2023].
*/

// Function: logInfo
// Parameters: const std::string& buildingInfo, const std::string& fileLocation
// Objective: Logs building information to a specified file location.
void BuildingStructureLog::logInfo(const std::string& buildingInfo, const std::string& fileLocation) {
    // Open the file in append mode to add building information
    std::ofstream outFile(fileLocation, std::ios::app);

    // Check if the file opened successfully
    if (outFile.is_open()) {
        // Write the building information to the file
        outFile << buildingInfo << std::endl;

        // Close the file after writing
        outFile.close();

        // Notify successful logging
        std::cout << "Building information logged to file.\n";
    }
    else {
        // Notify if the file couldn't be opened
        std::cout << "Unable to open file.\n";
    }
} // end of logInfo


// Function: displayFileInfo
// Parameters: const std::string& fileLocation
// Objective: Display the content of a file located at 'fileLocation'.
void BuildingStructureLog::displayFileInfo(const std::string& fileLocation) {
    // Open the file for reading
    std::ifstream inFile(fileLocation);
    std::string line;
    
    // Check if the file is opened successfully
    if (inFile.is_open()) {
        int lineNum = 0;

        // Read file line by line and display its content appending the index to the front
        while (std::getline(inFile, line)) {
            std::cout << lineNum++ << ". " << line << '\n';
        }
        inFile.close(); // Close the file after reading
    }
    else {
        std::cout << "Unable to open file.\n"; // Display if file opening fails
    }
} // end of displayFileInfo


// Function: isDuplicate
// Parameters: const std::string& name, const std::string& code
// Objective: Check if a building name or code already exists in the log file.
bool BuildingStructureLog::isDuplicate(const std::string& name, const std::string& code) {
    // Open the log file for reading
    std::ifstream inFile("LogFiles/BuildingInfo.txt");
    std::string line;

    // Check if the file is opened successfully
    if (inFile.is_open()) {
        // Read the file line by line
        while (std::getline(inFile, line)) {
            // Check if the current line contains the provided name or code
            if (line.find("Building Name: " + name) != std::string::npos ||
                line.find("Building Code: " + code) != std::string::npos) {
                inFile.close(); // Close the file
                return true;    // Found a duplicate
            }
        }
        inFile.close(); // Close the file after reading
    }
    else {
        std::cout << "Unable to open file.\n"; // Display if file opening fails
    }

    return false; // No duplicate found
} // end of isDuplicate

// Function: readRoomDataFromFile
// Objective: Read room data from a file and store it in a vector of strings.
std::vector<std::string> BuildingStructureLog::readRoomDataFromFile() {
    // Open the file "LogFiles/Building_Structure.txt" for reading
    std::ifstream inputFile("LogFiles/Building_Structure.txt");
    std::vector<std::string> roomData; // Initialize a vector to store room data

    // Check if the file is opened successfully
    if (inputFile.is_open()) {
        std::string line;

        // Read each line from the file and store it in the roomData vector
        while (std::getline(inputFile, line)) {
            roomData.push_back(line);
        }

        inputFile.close(); // Close the file after reading
    }
    else {
        std::cerr << "Unable to open file\n"; // Display an error message if file opening fails
    }

    return roomData; // Return the vector containing room data read from the file
} // end of readRoomDataFromFile


// Function: removeRoomFromLogFile
// Paramater: int index of room that is getting removed
// Objective: Remove a room entry from the log file based on the provided index.
void BuildingStructureLog::removeRoomFromLogFile(int index) {
    std::vector<std::string> roomData = readRoomDataFromFile(); // Read room data from the file

    // Check if the index is within the range of the roomData vector
    if (index >= 0 && index < roomData.size()) {
        std::cout << "Removing room: " << roomData[index] << std::endl;

        roomData.erase(roomData.begin() + index); // Remove the room entry at the specified index

        // Open the file in truncation mode to clear its content
        std::ofstream outputFile("LogFiles/Building_Structure.txt", std::ios::trunc);

        // Check if the file is opened successfully
        if (outputFile.is_open()) {
            // Rewrite the updated room data back to the file
            for (const std::string& room : roomData) {
                outputFile << room << "\n";
            }
            outputFile.close(); // Close the file after writing

            std::cout << "Room removed from the log file.\n"; // Display success message
        }
        else {
            std::cerr << "Unable to open file\n"; // Display error message if file opening fails
        }
    }
    else {
        std::cout << "Invalid index.\n"; // Display message for an invalid index
    }
} // end of removeRoomFromLogFile


// Function: getBuildingInfo
// Paramater: int index of the building that is being used
// Objective: Retrieve building information from the log file at the specified index.
std::string BuildingStructureLog::getBuildingInfo(int index) {
    std::ifstream inFile("LogFiles/BuildingInfo.txt"); // Open the log file for reading
    std::string line;
    int currentIndex = 0;

    // Check if the file is open and readable
    if (inFile.is_open()) {
        // Read each line of the file
        while (std::getline(inFile, line)) {
            // Check if the current line index matches the specified index
            if (currentIndex == index) {
                inFile.close(); // Close the file
                return line; // Return the building info at the specified index
            }
            currentIndex++; // Move to the next line index
        }
        inFile.close(); // Close the file after reading
    }
    else {
        std::cout << "Unable to open file.\n"; // Display an error message if the file cannot be opened
    }

    return ""; // Return an empty string if the index is out of range or the file couldn't be opened
} // end of getBuildingInfo


// Function: updateRoomDataFile
// Paramater: vector of strings for the newly updated room data
// Objective: Update the room data in the "LogFiles/Building_Structure.txt" file with the provided updated room data.
void BuildingStructureLog::updateRoomDataFile(const std::vector<std::string>& updatedRoomData) {
    // Open the file in truncation mode to clear its contents before adding the new data
    std::ofstream outputFile("LogFiles/Building_Structure.txt", std::ios::trunc);

    // Check if the file is open and writable
    if (outputFile.is_open()) {
        // Iterate through each updated room data in the provided vector
        for (const std::string& room : updatedRoomData) {
            outputFile << room << "\n"; // Write each updated room data to the file
        }
        outputFile.close(); // Close the file after writing
        std::cout << "Room data updated in the log file.\n"; // Display a success message
    }
    else {
        std::cerr << "Unable to open file\n"; // Display an error message if the file couldn't be opened
    }
}
