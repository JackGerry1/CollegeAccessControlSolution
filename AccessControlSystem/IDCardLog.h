// IDCardLog.h: This file defines functions and attributes for the IDCardLog class.

#pragma once
#include "User.h"
#include <fstream>
#include <iostream>
#include <vector>

/*
References:
    URL: https://www.instructables.com/How-to-Do-the-Singleton-Design-Pattern-in-C/ Date Accessed: 27/12/23
*/


// Define a class for handling ID card logging operations
class IDCardLog {
private:
    static IDCardLog* instance;
    IDCardLog(); // Private constructor declaration
public:
    // Function declaration
    static IDCardLog* getInstance();
    // Log user data to a file
    static void logUserData(const std::string& userInfo);

    // Read user data from a file and return as a vector of strings
    static std::vector<std::string> readUserDataFromFile();

    // Display all users' data stored in the log file
    static void displayUsersFromLogFile();

    // Remove a user's data from the log file based on the index
    static void removeUserFromLogFile(int index);

    // Update user information (forename, surname, card) in the log file at a specified index
    static void updateUserInLogFile(int index, const std::string& newForename, const std::string& newSurname, bool generateCard);

    // Update user roles in the provided user data string and return the updated user data
    static std::string updateUserRoles(const std::string& userData, const std::vector<std::string>& rolesToAdd);

    // Update the entire user data file with the provided vector of updated user data
    static void updateUserDataFile(const std::vector<std::string>& updatedUserData);
};