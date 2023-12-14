#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "User.h"

class IDCardLog {
public:
    static void logUserData(const std::string& userInfo);
    static std::vector<std::string> readUserDataFromFile();
    static void displayUsersFromLogFile();
    static void removeUserFromLogFile(int index);
};
