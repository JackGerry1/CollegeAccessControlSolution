//IDCardLog.h: This file contains functions and attributes for the IDCardLog class. 

#pragma once
// include libraries and other header files for the IDCardLog.cpp file
#include "User.h"
#include <fstream>
#include <iostream>
#include <vector>

// create a class with the public methods for the IDCardLog.cpp file
class IDCardLog {
public:
    static void logUserData(const std::string& userInfo);
    static std::vector<std::string> readUserDataFromFile();
    static void displayUsersFromLogFile();
    static void removeUserFromLogFile(int index);
    static void updateUserInLogFile(int index, const std::string& newForename, const std::string& newSurname, bool generateCard);
    static void updateUserDataFile(const std::vector<std::string>& updatedUserData);
};
