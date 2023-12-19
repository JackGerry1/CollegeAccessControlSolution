#pragma once

#include "IDCardLog.h"
#include "SwipeCard.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// class for user
class User {
// private attributes and composition with SwipeCard
private:
    std::string forename;
    std::string surname;
    std::vector<std::string> roles; 
    SwipeCard swipeCard;

// public functions and constructor for User
public:
    User(std::string forename, std::string surname, std::vector<std::string> roles);

    void addUser();
    void removeUser();
    void updateUser();
    std::vector<std::string> addRoles(); // Modified to return a vector of roles
    void removeRole(std::string removedRole);
    static void displayUsersAlphabetically();
    std::string getFullName() const;
    std::vector<std::string> getRoles() const; // Getter for roles
    void addRoleToUser();
    void displayRoleMenu();
    std::string getRoleFromChoice(int choice);
    std::string updateUserRoles(const std::string& userData, const std::vector<std::string>& rolesToAdd);
};
