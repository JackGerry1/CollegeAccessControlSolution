// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "User.h"
#include "Building.h"
#include "IDCardLog.h"
#include "DailyLogFile.h"
#include "Simulation.h"

int main() {
	// choice is the the users choice from the menu and controls whether the program should exit
	int choice;
	bool exitProgram = false;
	// Creating a blank User Object
	User newUser("", "", std::vector<std::string>{""});
	Simulation sim;
	// Creating a Building object
	Building newBuilding("", "");
	// loop for menu system
	while (!exitProgram) {
		// Displaying the menu options
		std::cout << "Menu:\n";
		std::cout << "1. Add User\n";
		std::cout << "2. Display Users Alphabetically\n";
		std::cout << "3. Remove User\n";
		std::cout << "4. Update User\n";
		std::cout << "5. Add Roles To Existing Users\n";
		std::cout << "6. Remove Roles From Existing Users\n";
		std::cout << "7. Display ID_Card_List.txt File\n";
		std::cout << "8. Add Building\n";
		std::cout << "9: Add Room\n";
		std::cout << "10. Remove Room\n";
		std::cout << "11. Change Room State\n";
		std::cout << "12. Update Room\n";
		std::cout << "13. Display Room And Building Info\n";
		std::cout << "14. Start Simulation\n";
		std::cout << "15. View Today's Access Attempts\n";
		std::cout << "16. Exit\n";
		std::cout << "Enter your choice: ";
		// Taking user input for menu choice
		std::cin >> choice; 

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
		// add roles to existing users
		case 5:
			newUser.addRoleToUser();
			break;
		// remove roles from existing users
		case 6:
			newUser.removeRole();
			break;
		// display user file
		case 7:
			IDCardLog::displayUsersFromLogFile();
			break;
		// add new building case
		case 8:
			// Call addBuilding method from Building class 
			newBuilding.addBuilding(); 
			break;
		// add new room case
		case 9: 
			newBuilding.addRoom();
			break;
		// remove room case 
		case 10: 
			newBuilding.removeRoom();
			break;
		// change state case
		case 11:
			newBuilding.changeRoomAndBuildingState();
			break;
		// update room case
		case 12:
			newBuilding.updateRoom();
			break;
		// display room and building information
		case 13:
			BuildingStructureLog::displayFileInfo("LogFiles/Building_Structure.txt");
			break;
		// start simulation
		case 14: 
			sim.startSimulation();
			break;
		// view today's access attempts
		case 15:
			DailyLogFile::viewRoomAccessAttempts();
			break;
		// exit program case
		case 16:
			// Setting the flag to exit the loop and program after outputting a message 
			std::cout << "Exiting Program...\n";
			exitProgram = true;
			break;
		// Handling invalid user input
		default:
			std::cout << "Invalid choice. Please try again.\n"; 
			break;
		}
	}

	return 0; 
}