//IDCardLog.cpp : This file contains functions and attributes specifeid in the IDCardLog.h file.

#include "IDCardLog.h"

// function to log users data addition
void IDCardLog::logUserData(const std::string& userInfo) {
    // Open the file in append mode
    std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::app); 

    // if the file can be opened write to that file
    if (outputFile.is_open()) {
        outputFile << userInfo; 
        outputFile.close(); 
    }
    // Display an error message if the file couldn't be opened
    else {
        std::cerr << "Unable to open file\n"; 
    }
}

// function to read text file
std::vector<std::string> IDCardLog::readUserDataFromFile() {
    // Open the file for reading
    std::ifstream inputFile("LogFiles/ID_Card_List.txt"); 
    
    // Vector to hold user data read from the file
    std::vector<std::string> userData; 
    
    // Check if the file was opened successfully
    if (inputFile.is_open()) {
        // store the line in this variable
        std::string line;
        // for every line in the file add it to the end of vector
        while (std::getline(inputFile, line)) {
            userData.push_back(line); 
        }
        inputFile.close(); 
    }
    // Display an error message if the file couldn't be opened
    else {
        std::cerr << "Unable to open file\n"; 
    }
    // Return the vector containing user data read from the file
    return userData; 
}

// function to displayUsersfrom the Log File
void IDCardLog::displayUsersFromLogFile() {
    // Read user data from the log file and store in vector of strings
    std::vector<std::string> userData = readUserDataFromFile(); 

    // Check if user data exists
    if (!userData.empty()) { 
        std::cout << "Current Users:\n"; 
        // loop for vector and output each user's data from the vector
        for (const std::string& user : userData) {
            std::cout << user << std::endl; 
        }
        // newline for readablity
        std::cout << "\n"; 
    }
    // If no user data is available, display a message
    else {
        std::cout << "No users found in the log file.\n"; 
    }
}


// function to remove a user from the log file
void IDCardLog::removeUserFromLogFile(int index) {
    // Read user data from the log file and store in vector
    std::vector<std::string> userData = readUserDataFromFile(); 

    // Check if the index is within the bounds of user data, which is how many lines are in the file
    if (index >= 0 && index < userData.size()) {
        // Display the user being removed
        std::cout << "Removing user: " << userData[index] << std::endl;

        // Erase the user data at the specified index
        userData.erase(userData.begin() + index);

        // Open the file in truncation mode to clear it
        std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::trunc);
        if (outputFile.is_open()) {
            // Write the updated user data back to the file
            for (const std::string& user : userData) {
                outputFile << user << "\n";
            }
            outputFile.close(); // Close the file after writing

            // Indicate successful removal
            std::cout << "User removed from the log file.\n";
        }
        // Error message if unable to open the file
        else {
            std::cerr << "Unable to open file\n"; 
        }
    }
    // Display an error if the index is out of bounds
    else {
        std::cout << "Invalid index.\n"; 
    }
}

