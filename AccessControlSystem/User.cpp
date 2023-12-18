//User.cpp : This file contains functions and attributes specifeid in the User.h file. 

#include "User.h"

// Constructor initializing user details for forename surname role user id and swipecard
User::User(std::string forename, std::string surname, std::string role)
	: forename(forename), surname(surname), role(role), swipeCard("") {}

// function to the combine the forename and surname specifed by the user
std::string User::getFullName() const {
	return forename + " " + surname;
}

// function to get the role specifed by the user
std::string User::getRole() const {
	return role;
}

// function to allow the user to create a user, which will be logged into the ID_Card_List.txt file
void User::addUser() {
	// initiise variables for the forename, surname and role that can be specifed by the user
	std::string newForename, newSurname, newRole;

	// take user input for the forename and store in newForename
	std::cout << "Enter forename: ";
	std::cin >> newForename;

	// take user input for the surname and store in newSurname
	std::cout << "Enter surname: ";
	std::cin >> newSurname;

	// set the constructor attributes to the values specifed by the user
	forename = newForename;
	surname = newSurname;

	// Set the role by invoking the addRole() method
	role = addRole();

	// Creating a new blank SwipeCard object
	SwipeCard swipeCard("");

	// Clearing the console screen so the user input options aren't shown after selecting the desired role
	system("cls");

	// Creating user information string using the info gathered previusly
	std::string userInfo = "Name: " + getFullName() + ", Role: " + getRole() + ", Swipe Card ID: " + swipeCard.addSwipeCard() + "\n";

	// Outputting user information to a log file
	IDCardLog::logUserData(userInfo);

	// Displaying the added user information on the console
	std::cout << "Added User Info: " << userInfo << "\n";
}

// function to remove a user from the log file
void User::removeUser() {
	// Reading user data from a file and storing it in a vector
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	// Checking if the user data vector is not empty
	if (!userData.empty()) {
		IDCardLog::displayUsersFromLogFile();

		// Taking user input for the index of the user to remove
		int index;
		std::cout << "Enter the index of the user you want to remove: ";
		std::cin >> index;

		// Removing the user based on the provided index from the log file
		IDCardLog::removeUserFromLogFile(index);
	}
	else {
		std::cout << "No users found in the log file. Nothing to remove.\n\n";
	}
}

// function to update user from the log file
void User::updateUser() {
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	if (!userData.empty()) {
		IDCardLog::displayUsersFromLogFile();

		int index;
		std::cout << "Enter the index of the user you want to update: ";
		std::cin >> index;

		if (index >= 0 && index < userData.size()) {
			std::string newForename, newSurname;
			std::string newRole;
			bool generateCard = false;

			std::cout << "Enter new forename (Leave blank to keep unchanged): ";
			std::cin.ignore(); 
			std::getline(std::cin, newForename);

			std::cout << "Enter new surname (Leave blank to keep unchanged): ";
			std::getline(std::cin, newSurname);

			std::cout << "Do you want to generate a new swipe card? (yes/no): ";
			std::string generateCardInput;
			std::cin >> generateCardInput;
			if (generateCardInput == "yes") {
				generateCard = true;
			}

			std::cout << "Do you want to change the role? (yes/no): ";
			std::string changeRoleInput;
			std::cin >> changeRoleInput;

			if (changeRoleInput == "yes") {
				newRole = addRole();
			}

			IDCardLog::updateUserInLogFile(index, newForename, newSurname, newRole, generateCard);
		}
		else {
			std::cout << "Invalid index.\n";
		}
	}
	else {
		std::cout << "No users found in the log file.\n\n";
	}
}


std::string User::addRole() {
	int choice;
	// Displaying role options
	std::cout << "Enter a role:\n";
	std::cout << "1. Staff Member\n";
	std::cout << "2. Student\n";
	std::cout << "3. Visitor / Guest\n";
	std::cout << "4. Contract Cleaner\n";
	std::cout << "5. Manager\n";
	std::cout << "6. Security\n";
	std::cout << "7. Emergency Responder\n";

	// Taking user input for the role choice
	do {
		std::cout << "Enter your choice (1-7): ";
		std::cin >> choice;
		// Validating the choice within the given range (1-7) 
	} while (choice < 1 || choice > 7);

	// Returning the corresponding role based on the user's choice
	switch (choice) {
	case 1:
		return "Staff Member";
	case 2:
		return "Student";
	case 3:
		return "Visitor / Guest";
	case 4:
		return "Contract Cleaner";
	case 5:
		return "Manager";
	case 6:
		return "Security";
	case 7:
		return "Emergency Responder";
		// Returning an empty string for an invalid choice this will never be reached because of the way the loop is setup
	default:
		return "No Role";
	}
}

// function to remove role from user
void User::removeRole(std::string removedRole) {
	// Implementation to remove a role from a user
}

// function to display the users alphabeticaly in the log file
void User::displayUsersAlphabetically() {
	// Create a vector to hold user names
	std::vector<std::string> names;

	// Read user data from the file and store in a vector
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();
	std::string token, name; // Declare variables to hold extracted token and user name

	// Check if user data exists in the retrieved data from the file
	if (!userData.empty()) {
		// Loop through each line of user data
		for (const std::string& userString : userData) {
			// Parse userString to extract relevant information (name, role, etc.)
			std::istringstream ss(userString);
			while (std::getline(ss, token, ',')) {
				// Check if the current token contains user's name
				if (token.find("Name:") != std::string::npos) {
					// Extracting the name from the line
					size_t pos = token.find("Name:");
					// Assuming "Name: " has 6 characters because after that is the full name
					name = token.substr(pos + 6); 
					// Add extracted name to the vector
					names.push_back(name); 
					break;
				}
			}
		}

		// Sort the names vector alphabetically
		std::sort(names.begin(), names.end());

		// Display the sorted list of users
		std::cout << "\nALPHABETICAL LIST OF USERS" << std::endl;
		for (const auto& name : names) {
			std::cout << "Name: " << name << std::endl; // Output each user's name
		}
	}
	else {
		std::cout << "No users found in the log file.\n";
	}
}


