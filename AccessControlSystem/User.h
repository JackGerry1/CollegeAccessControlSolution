//User.h: This file contains functions and attributes for the user class. 

#pragma once

// include all libaries and other header files so i don't have to include in the User.cpp file
#include "IDCardLog.h"
#include "SwipeCard.h"
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>

// create user class with private attributes
class User {
private:
    std::string forename;
    std::string surname;
    std::string role;
    int userID;
    // Composite relationship with SwipeCard
    SwipeCard swipeCard; 


public:
    // constructor for User class
    User(std::string forename, std::string surname, std::string role, int userID);

    // public function declarations for the User class
    void addUser();
    void removeUser();
    void updateUser();
    std::string addRole();
    void removeRole(std::string removedRole);
    static void displayUsersAlphabetically();
    int getUserID();
    std::string getFullName() const;
    std::string getRole() const;
};
