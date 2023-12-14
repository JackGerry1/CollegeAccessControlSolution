// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include "User.h"

int main() {
    int choice;
    bool exitProgram = false;
    User newUser("", "", "", 0);
    std::vector<User> users;

    while (!exitProgram) {
        std::cout << "Menu:\n";
        std::cout << "1. Add User\n";
        std::cout << "2. Display Users Alphabetically\n";
        std::cout << "3. Remove User\n"; // Adding the option to remove user
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        system("cls");

        switch (choice) {
        case 1: {
            newUser.addUser();
            users.push_back(newUser);
            break;
        }
        case 2:
            User::displayUsersAlphabetically(users);
            break;
        case 3:
            newUser.removeUser();
            break;
        case 4:
            std::cout << "Exiting Program...\n";
            exitProgram = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}

