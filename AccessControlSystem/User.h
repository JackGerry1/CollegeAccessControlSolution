// User.h: Contains declarations for functions and attributes in User.cpp file.

#pragma once

#include "IDCardLog.h"
#include "SwipeCard.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Represents a user with associated functionalities
class User {
private:
    std::string forename; // User's forename
    std::string surname; // User's surname
    std::vector<std::string> roles; // User's roles stored as strings
    SwipeCard swipeCard; // Composition with a SwipeCard object

public:
    // Constructor for User
    User(std::string forename, std::string surname, std::vector<std::string> roles);

    // Functions to manipulate user data
    void addUser(); // Add a new user to the system
    void removeUser(); // Remove an existing user from the system
    void updateUser(); // Update user information
    std::vector<std::string> addRoles(); // Add roles to the user, returns a vector of roles
    void removeRole(); // Remove a specific role from the user
    static void displayUsersAlphabetically(); // Display users in alphabetical order
    std::string getFullName() const; // Retrieve the user's full name
    std::vector<std::string> getRoles() const; // Getter function to retrieve user's roles
    void addRoleToUser(); // Add a role to an existing user
    int displayRoleMenuAndGetChoice(); // Display a menu of roles and get user's choice
    std::string getRoleFromChoice(int choice); // Get a specific role based on user's choice
};
