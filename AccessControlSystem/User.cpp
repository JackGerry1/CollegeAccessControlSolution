//User.cpp : This file contains functions and attributes specifeid in the User.h file. 

#include "User.h"

// Constructor initializing user details for forename surname role user id and swipecard
User::User(std::string forename, std::string surname, std::vector<std::string> roles)
	: forename(forename), surname(surname), roles(roles), swipeCard("") {}

// function to the combine the forename and surname specifed by the user
std::string User::getFullName() const {
	return forename + " " + surname;
}

// function to get the roles specifed by the user
std::vector<std::string> User::getRoles() const {
	return roles;
}

// function to allow the user to create a user, which will be logged into the ID_Card_List.txt file
void User::addUser() {
	// declare variabels for forename and surname
	std::string newForename, newSurname;

	// get forename from user
	std::cout << "Enter forename: ";
	std::cin >> newForename;

	// get surname from user
	std::cout << "Enter surname: ";
	std::cin >> newSurname;

	// assign to the variables in the constructor so it can be used in the getFullName()
	forename = newForename;
	surname = newSurname;

	// Invoke function to add multiple roles
	roles = addRoles();

	// Logging user information to a log file
	std::string userInfo = "Name: " + getFullName() + ", Roles:";
	for (size_t i = 0; i < roles.size(); ++i) {
		userInfo += " " + roles[i];
		if (i != roles.size() - 1) {
			userInfo += ",";
		}
	}
	userInfo += ", Swipe Card ID: " + swipeCard.addSwipeCard() + "\n";
	IDCardLog::logUserData(userInfo);
	std::cout << "Added User Info: " << userInfo << "\n";
}

std::string User::getRoleFromChoice(int choice) {
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
		return "No Role";
	}
}

int User::displayRoleMenuAndGetChoice() {
	int choice;
	std::cout << "Enter roles:\n";
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

	return choice;
}

std::vector<std::string> User::addRoles() {
	std::vector<std::string> addedRoles;
	int numRoles;
	std::cout << "Enter the number of roles to add: ";
	std::cin >> numRoles;

	for (int i = 0; i < numRoles; ++i) {
		int choice = displayRoleMenuAndGetChoice();
		std::string role = getRoleFromChoice(choice);
		addedRoles.push_back(role);
	}

	return addedRoles;
}

void User::addRoleToUser() {
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();
	if (!userData.empty()) {
		IDCardLog::displayUsersFromLogFile();
		int index;
		std::cout << "Enter the index of the user to add roles: ";
		std::cin >> index;

		if (index >= 0 && index < userData.size()) {
			std::string selectedUser = userData[index];
			std::cout << "Selected User: " << selectedUser << std::endl;

			std::vector<std::string> rolesToAdd = addRoles();

			// Update user's roles
			std::string updatedUser = IDCardLog::updateUserRoles(selectedUser, rolesToAdd);
			userData[index] = updatedUser;
			IDCardLog::updateUserDataFile(userData);

			std::cout << "Roles added to user at index " << index << ":\n";
			std::cout << "Updated User Info: " << updatedUser << std::endl;
		}
		else {
			std::cout << "Invalid index.\n";
		}
	}
	else {
		std::cout << "No users found in the log file.\n\n";
	}
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
			system("cls"); // Clear the screen
			std::cout << "Updating user at index: " << index << std::endl;

			std::string newForename, newSurname;
			std::string newRole;
			bool generateCard = false;

			std::cin.ignore(); // Clear buffer

			std::cout << "Enter new forename (Leave blank to keep unchanged): ";
			std::getline(std::cin, newForename);

			std::cout << "Enter new surname (Leave blank to keep unchanged): ";
			std::getline(std::cin, newSurname);

			std::cout << "Do you want to generate a new swipe card? (yes/no): ";
			std::string generateCardInput;
			std::cin >> generateCardInput;

			if (generateCardInput == "yes") {
				generateCard = true;
			}

			IDCardLog::updateUserInLogFile(index, newForename, newSurname, generateCard);



			// Output the result of the changes
			std::cout << "User updated with:\nForename: " << newForename << "\nSurname: " << newSurname
				<< "\nSwipe card updated: " << (generateCard ? "Yes" : "No") << std::endl;
		}
		else {
			std::cout << "Invalid index.\n";
		}
	}
	else {
		std::cout << "No users found in the log file.\n\n";
	}
}

void User::removeRole() {
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	if (userData.empty()) {
		std::cout << "No users found in the log file.\n";
		return;
	}

	IDCardLog::displayUsersFromLogFile();

	int userIndex;
	std::cout << "Enter the index of the user to remove a role from: ";
	std::cin >> userIndex;

	if (userIndex < 0 || userIndex >= userData.size()) {
		std::cout << "Invalid user index.\n";
		return;
	}

	std::string selectedUser = userData[userIndex];
	std::cout << "Selected User: " << selectedUser << std::endl;

	size_t rolesPos = selectedUser.find("Roles: ");
	if (rolesPos == std::string::npos) {
		std::cout << "Roles information not found for this user.\n";
		return;
	}

	size_t swipeCardIDPos = selectedUser.find("Swipe Card ID: ", rolesPos);
	if (swipeCardIDPos == std::string::npos) {
		std::cout << "Invalid user data format.\n";
		return;
	}

	std::string existingRoles = selectedUser.substr(rolesPos + 7, swipeCardIDPos - (rolesPos + 9));
	std::istringstream rolesStream(existingRoles);
	std::vector<std::string> existingRolesVec;
	std::string roleToken;
	while (std::getline(rolesStream, roleToken, ',')) {
		existingRolesVec.push_back(roleToken);
	}

	if (existingRolesVec.empty()) {
		std::cout << "No roles found for this user.\n";
		return;
	}

	int roleIndex;
	std::cout << "Enter the index of the role to remove (0-" << existingRolesVec.size() - 1 << "): ";
	std::cin >> roleIndex;

	if (roleIndex < 0 || roleIndex >= existingRolesVec.size()) {
		std::cout << "Invalid role index.\n";
		return;
	}

	existingRolesVec.erase(existingRolesVec.begin() + roleIndex);

	std::ostringstream updatedUserStream;
	updatedUserStream << "Name: " << selectedUser.substr(6, rolesPos - 8);
	updatedUserStream << ", Roles: ";

	if (!existingRolesVec.empty()) {
		for (size_t i = 0; i < existingRolesVec.size(); ++i) {
			updatedUserStream << existingRolesVec[i];
			updatedUserStream << ",";
		}
	}
	else {
		updatedUserStream << ",";
	}

	std::string updatedRoles = updatedUserStream.str();
	userData[userIndex] = updatedRoles + selectedUser.substr(swipeCardIDPos - 1);

	size_t found = userData[userIndex].find("  "); // Find position of double space
	while (found != std::string::npos) {
		userData[userIndex].replace(found, 2, " "); // Replace double space with single space
		found = userData[userIndex].find("  ", found + 1); // Search for next occurrence
	}

	IDCardLog::updateUserDataFile(userData);

	std::cout << "Role removed from the user at index " << userIndex << ":\n";
	std::cout << "Updated User Info: " << userData[userIndex] << std::endl;
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


