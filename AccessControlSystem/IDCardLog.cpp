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

void IDCardLog::updateUserInLogFile(int index, const std::string& newForename, const std::string& newSurname, const std::string& newRole, bool generateCard) {
    std::vector<std::string> userData = readUserDataFromFile();

    if (index >= 0 && index < userData.size()) {
        std::string& userToUpdate = userData[index];

        // Extract existing role and swipe card ID from the user data
        std::string existingRole, swipeCardID;
        size_t roleStart = userToUpdate.find("Role: ");
        if (roleStart != std::string::npos) {
            size_t roleEnd = userToUpdate.find(",", roleStart);
            existingRole = userToUpdate.substr(roleStart + 6, roleEnd - roleStart - 6);
        }

        size_t swipeCardStart = userToUpdate.find("Swipe Card ID: ");
        if (swipeCardStart != std::string::npos) {
            swipeCardID = userToUpdate.substr(swipeCardStart + 15);
        }

        // Update user information based on user input
        size_t nameStart = userToUpdate.find("Name: ") + 6;
        size_t commaPosition = userToUpdate.find(",", nameStart); // Find the comma after the name
        size_t surnameStart = userToUpdate.find(" ", nameStart); // Find the space between forename and surname

        if (!newForename.empty()) {
            if (commaPosition != std::string::npos) {
                userToUpdate.replace(nameStart, surnameStart - nameStart, newForename);
            }
            else {
                userToUpdate.replace(nameStart, userToUpdate.find(" ", nameStart) - nameStart, newForename);
            }
        }
        if (!newSurname.empty()) {
            size_t commaAfterSurname = userToUpdate.find(",", surnameStart); // Find the comma after the surname
            if (commaAfterSurname != std::string::npos) {
                userToUpdate.replace(surnameStart + 1, commaAfterSurname - (surnameStart + 1), newSurname);
            }
            else {
                userToUpdate.replace(surnameStart + 1, userToUpdate.find("\n", surnameStart) - (surnameStart + 1), newSurname);
            }
        }

        if (generateCard) {
            SwipeCard card("");
            swipeCardID = card.addSwipeCard();
            userToUpdate.replace(userToUpdate.find("Swipe Card ID: ") + 15, userToUpdate.find("\n") - (userToUpdate.find("Swipe Card ID: ") + 15), swipeCardID);
        }

        if (!newRole.empty()) {
            existingRole = newRole;
            userToUpdate.replace(userToUpdate.find("Role: ") + 6, userToUpdate.find(",", userToUpdate.find("Role: ")) - (userToUpdate.find("Role: ") + 6), existingRole);
        }

        std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::trunc);
        if (outputFile.is_open()) {
            for (const std::string& user : userData) {
                outputFile << user << "\n";
            }
            outputFile.close();
            std::cout << "User information updated.\n";
        }
        else {
            std::cerr << "Unable to open file\n";
        }
    }
    else {
        std::cout << "Invalid index.\n";
    }
}
