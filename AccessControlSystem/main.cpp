// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "User.h"

int main() {
	// choice is the the users choice from the menu and controls whether the program should exit
	int choice;
	bool exitProgram = false;
	// Creating a blank User Objectg
	User newUser("", "", ""); 

	// loop for menu system
	while (!exitProgram) {
		// Displaying the menu options
		std::cout << "Menu:\n";
		std::cout << "1. Add User\n";
		std::cout << "2. Display Users Alphabetically\n";
		std::cout << "3. Remove User\n";
		std::cout << "4. Update User\n";
		std::cout << "5. Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice; // Taking user input for menu choice

		// Clearing the console screen to make the other display info for adding users etc more clear
		system("cls"); 

		switch (choice) {
		// case for adding a user
		case 1: {
			newUser.addUser(); 
			break;
		}
		// dispaly alphabetical list of users case
		case 2:
			User::displayUsersAlphabetically(); 
			break;
		// remove user case 
		case 3:
			newUser.removeUser(); 
			break;
		// update user case
		case 4: 
			newUser.updateUser();
			break;
		// exit program case
		case 5:
			// Setting the flag to exit the loop and program after outputting a message 
			std::cout << "Exiting Program...\n"; 
			exitProgram = true; 
			break;
		default:
			// Handling invalid user input
			std::cout << "Invalid choice. Please try again.\n"; 
			break;
		}
	}

	return 0; 
}