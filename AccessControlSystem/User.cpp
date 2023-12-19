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

std::vector<std::string> User::addRoles() {
	std::vector<std::string> addedRoles;
	int numRoles;
	std::cout << "Enter the number of roles to add: ";
	std::cin >> numRoles;

	int choice;
	// Displaying role options
	std::cout << "Enter roles:\n";
	for (int i = 0; i < numRoles; ++i) {
		std::cout << "Role " << i + 1 << ":\n";
		std::cout << "1. Staff Member\n";
		std::cout << "2. Student\n";
		std::cout << "3. Visitor / Guest\n";
		std::cout << "4. Contract Cleaner\n";
		std::cout << "5. Manager\n";
		std::cout << "6. Security\n";
		std::cout << "7. Emergency Responder\n";

		// Taking user input for the role choice
		do {
			std::cout << "Enter your choice (1-7) for Role " << i + 1 << ": ";
			std::cin >> choice;
			// Validating the choice within the given range (1-7)
		} while (choice < 1 || choice > 7);

		// Adding the corresponding role based on the user's choice to the addedRoles vector
		switch (choice) {
		case 1:
			addedRoles.push_back("Staff Member");
			break;
		case 2:
			addedRoles.push_back("Student");
			break;
		case 3:
			addedRoles.push_back("Visitor / Guest");
			break;
		case 4:
			addedRoles.push_back("Contract Cleaner");
			break;
		case 5:
			addedRoles.push_back("Manager");
			break;
		case 6:
			addedRoles.push_back("Security");
			break;
		case 7:
			addedRoles.push_back("Emergency Responder");
			break;
		default:
			// Invalid choice will add "No Role"
			addedRoles.push_back("No Role");
			break;
		}
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

			// Request how many roles to add
			int numRoles;
			std::cout << "Enter the number of roles to add: ";
			std::cin >> numRoles;
			std::cin.ignore(); // Clear buffer

			std::vector<std::string> rolesToAdd;
			for (int i = 0; i < numRoles; ++i) {
				int choice;
				// Displaying role options
				std::cout << "Enter role " << i + 1 << ": ";
				std::cin >> choice;
				// Validating the choice within the given range (1-7) 
				if (choice >= 1 && choice <= 7) {
					std::string role = getRoleFromChoice(choice);
					rolesToAdd.push_back(role);
				}
				else {
					std::cout << "Invalid choice. Skipping role addition." << std::endl;
				}
			}

			// Update user's roles
			std::string updatedUser = updateUserRoles(selectedUser, rolesToAdd);
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

std::string User::updateUserRoles(const std::string& userData, const std::vector<std::string>& rolesToAdd) {
	std::string name, roles, swipeCardID;

	size_t namePos = userData.find("Name:");
	if (namePos != std::string::npos) {
		size_t rolePos = userData.find("Role:", namePos);
		if (rolePos != std::string::npos) {
			size_t swipeCardIDPos = userData.find("Swipe Card ID:", rolePos);
			if (swipeCardIDPos != std::string::npos) {
				// Extracting Name
				size_t nameEndPos = rolePos - 2; // End position of Name substring
				name = userData.substr(namePos + 6, nameEndPos - (namePos + 6));

				// Extracting Roles
				size_t rolesEndPos = swipeCardIDPos - 2; // End position of Roles substring
				roles = userData.substr(rolePos + 6, rolesEndPos - (rolePos + 5));

				// Extracting Swipe Card ID
				swipeCardID = userData.substr(swipeCardIDPos + 15);
			}
		}
	}

	// Console output to show initial user data
	std::cout << "Initial User Info - Name: " << name << ", Role: " << roles << ", Swipe Card ID: " << swipeCardID << "\n";

	// Split existing roles into a vector and trim spaces
	std::istringstream rolesStream(roles);
	std::vector<std::string> existingRoles;
	std::string roleToken;
	while (std::getline(rolesStream, roleToken, ',')) {
		// Trim leading and trailing spaces before adding roles to the vector
		roleToken.erase(0, roleToken.find_first_not_of(" \t\r\n"));
		roleToken.erase(roleToken.find_last_not_of(" \t\r\n") + 1);
		existingRoles.push_back(roleToken);
	}

	// Append new roles to the existing ones and trim spaces
	for (const auto& role : rolesToAdd) {
		// Check if the role already exists before appending
		if (std::find(existingRoles.begin(), existingRoles.end(), role) == existingRoles.end()) {
			std::string trimmedRole = role; // Copy the role to trim leading and trailing spaces
			trimmedRole.erase(0, trimmedRole.find_first_not_of(" \t\r\n"));
			trimmedRole.erase(trimmedRole.find_last_not_of(" \t\r\n") + 1);
			existingRoles.push_back(trimmedRole);
		}
	}

	// Reconstruct the updated roles string with trimmed roles
	std::string updatedRoles;
	for (size_t i = 0; i < existingRoles.size(); ++i) {
		if (i != 0) {
			updatedRoles += ", "; // Add a comma and a space before adding a new role (except for the first role)
		}
		updatedRoles += existingRoles[i];
	}

	// Console output to display updated roles
	std::cout << "Updated Roles: " << updatedRoles << "\n";

	// Reconstruct the updated user info
	std::string updatedUser = "Name: " + name + ", Role: " + updatedRoles + ", Swipe Card ID: " + swipeCardID;
	std::cout << "UPDATED USER: " << updatedUser << "\n";
	return updatedUser;
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


