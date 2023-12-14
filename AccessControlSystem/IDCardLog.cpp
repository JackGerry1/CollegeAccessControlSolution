#include "IDCardLog.h"

void IDCardLog::logUserData(const std::string& userInfo) {
    std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::app); // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile << userInfo; // Write the user info to the file
        outputFile.close();
    }
    else {
        std::cerr << "Unable to open file\n";
    }
}

std::vector<std::string> IDCardLog::readUserDataFromFile() {
    std::ifstream inputFile("LogFiles/ID_Card_List.txt");
    std::vector<std::string> userData;

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            userData.push_back(line);
        }
        inputFile.close();
    }
    else {
        std::cerr << "Unable to open file\n";
    }
    return userData;
}

void IDCardLog::displayUsersFromLogFile() {
    std::vector<std::string> userData = readUserDataFromFile();

    if (!userData.empty()) {
        std::cout << "Current Users:\n";
        for (const std::string& user : userData) {
            std::cout << user << std::endl;
        }
        std::cout << "\n";
    }
    else {
        std::cout << "No users found in the log file.\n";
    }
}

void IDCardLog::removeUserFromLogFile(int index) {
    std::vector<std::string> userData = readUserDataFromFile();

    if (index >= 0 && index < userData.size()) {
        std::cout << "Removing user: " << userData[index] << std::endl;
        userData.erase(userData.begin() + index);

        std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::trunc); // Clear the file
        if (outputFile.is_open()) {
            for (const std::string& user : userData) {
                outputFile << user << "\n"; // Write the updated user data back to the file
            }
            outputFile.close();
            std::cout << "User removed from the log file.\n";
        }
        else {
            std::cerr << "Unable to open file\n";
        }
    }
    else {
        std::cout << "Invalid index.\n";
    }
}
