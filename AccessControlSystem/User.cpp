#include "User.h"
#include "IDCardLog.h"
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>

User::User(std::string forename, std::string surname, std::string role, int userID)
	: forename(forename), surname(surname), role(role), userID(1), swipeCard("") {}

int User::getUserID() {
	return userID++;
}

std::string User::getForename() const {
	return forename;
}

std::string User::getSurname() const {
	return surname;
}

std::string User::getFullName() const {
	return forename + " " + surname;
}

std::string User::getRole() const {
	return role;
}

void User::addUser() {
	std::string newForename, newSurname, newRole;
	std::cout << "Enter forename: ";
	std::cin >> newForename;

	std::cout << "Enter surname: ";
	std::cin >> newSurname;

	forename = newForename;
	surname = newSurname;

	role = addRole();
	SwipeCard newSwipeCard("");
	swipeCard = newSwipeCard; // Assigning a new swipe card when adding a user

	system("cls");

	std::string userInfo = "Name: " + getFullName() + ", Role: " + getRole() + ", Swipe Card ID: " + swipeCard.addSwipeCard() + ", User ID: " + std::to_string(getUserID()) + "\n";
	// Outputting to a file
	IDCardLog::logUserData(userInfo); // Call the function in IDCardLog to write the user info to a file
	std::cout << "Added User Info: " << userInfo << "\n";
	
}

void User::removeUser() {
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	if (!userData.empty()) {
		IDCardLog::displayUsersFromLogFile();

		int index;
		std::cout << "Enter the index of the user you want to remove: ";
		std::cin >> index;

		IDCardLog::removeUserFromLogFile(index);
	}
	else {
		std::cout << "No users found in the log file. Nothing to remove.\n\n";
	}
}


void User::updateUser() {
	// Implementation to update user information
}

std::string User::addRole() {
	int choice;
	std::cout << "Enter a role:\n";
	std::cout << "1. Staff Member\n";
	std::cout << "2. Student\n";
	std::cout << "3. Visitor / Guest\n";
	std::cout << "4. Contract Cleaner\n";
	std::cout << "5. Manager\n";
	std::cout << "6. Security\n";
	std::cout << "7. Emergency Responder\n";

	do {
		std::cout << "Enter your choice (1-7): ";
		std::cin >> choice;
	} while (choice < 1 || choice > 7);

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
	default:
		return "";
	}

}


void User::removeRole(std::string removedRole) {
	// Implementation to remove a role from a user
}

void User::displayUsersAlphabetically() {
	std::vector<std::string> names; // Create a vector to hold user names

	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();
	std::string token, name;
	if (!userData.empty()) {
		for (const std::string& userString : userData) {
			// Parse userString to extract relevant information (name, role, etc.)
			std::istringstream ss(userString);
			while (std::getline(ss, token, ',')) {
				if (token.find("Name:") != std::string::npos) {
					// Extracting the name from the line
					size_t pos = token.find("Name:");
					name = token.substr(pos + 6); // Assuming "Name: " has 6 characters
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
			std::cout << "Name: " << name << std::endl;
		}
	}
	else {
		std::cout << "No users found in the log file.\n";
	}
}

