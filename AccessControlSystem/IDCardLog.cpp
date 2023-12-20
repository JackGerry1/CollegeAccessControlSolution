//IDCardLog.cpp : This file contains functions and attributes specifeid in the IDCardLog.h file.

#include "IDCardLog.h"

// function to log users data addition
void IDCardLog::logUserData(const std::string& userInfo) {
	// Open the file in append mode
	std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::app);

	// if the file can be opened write to that file
	if (outputFile.is_open()) {
		outputFile << userInfo;
		outputFile.close();
	}
	// Display an error message if the file couldn't be opened
	else {
		std::cerr << "Unable to open file\n";
	}
}

// function to read text file
std::vector<std::string> IDCardLog::readUserDataFromFile() {
	// Open the file for reading
	std::ifstream inputFile("LogFiles/ID_Card_List.txt");

	// Vector to hold user data read from the file
	std::vector<std::string> userData;

	// Check if the file was opened successfully
	if (inputFile.is_open()) {
		// store the line in this variable
		std::string line;
		// for every line in the file add it to the end of vector
		while (std::getline(inputFile, line)) {
			userData.push_back(line);
		}
		inputFile.close();
	}
	// Display an error message if the file couldn't be opened
	else {
		std::cerr << "Unable to open file\n";
	}
	// Return the vector containing user data read from the file
	return userData;
}

// function to displayUsersfrom the Log File
void IDCardLog::displayUsersFromLogFile() {
	// Read user data from the log file and store in vector of strings
	std::vector<std::string> userData = readUserDataFromFile();

	// Check if user data exists
	if (!userData.empty()) {
		std::cout << "Current Users:\n";
		// loop for vector and output each user's data from the vector
		for (const std::string& user : userData) {
			std::cout << user << std::endl;
		}
		// newline for readablity
		std::cout << "\n";
	}
	// If no user data is available, display a message
	else {
		std::cout << "No users found in the log file.\n";
	}
}
std::string IDCardLog::updateUserRoles(const std::string& userData, const std::vector<std::string>& rolesToAdd) {
	std::string updatedUser = userData;
	std::cout << "USERDATA START: " << userData << "\n";
	size_t rolesPos = updatedUser.find("Roles: ");

	if (rolesPos != std::string::npos) {
		size_t swipeCardIDPos = updatedUser.find("Swipe Card ID: ", rolesPos);
		if (swipeCardIDPos != std::string::npos) {
			size_t endOfRolesPos = updatedUser.find(",", rolesPos);
			if (endOfRolesPos == std::string::npos || endOfRolesPos > swipeCardIDPos) {
				endOfRolesPos = swipeCardIDPos;
			}
			std::string existingRoles = updatedUser.substr(rolesPos + 7, endOfRolesPos - (rolesPos + 7));

			// Split existing roles into a vector
			std::istringstream rolesStream(existingRoles);
			std::vector<std::string> existingRolesVec;
			std::string roleToken;
			while (std::getline(rolesStream, roleToken, ',')) {
				existingRolesVec.push_back(roleToken);
			}

			// Append new roles
			for (const auto& newRole : rolesToAdd) {
				// Check if the role already exists
				if (std::find(existingRolesVec.begin(), existingRolesVec.end(), newRole) == existingRolesVec.end()) {
					existingRolesVec.push_back(newRole);
				}
			}

			// Join roles into a string with commas
			std::string updatedRoles;
			for (size_t i = 0; i < existingRolesVec.size(); ++i) {
				if (i != 0) {
					updatedRoles += ", ";
				}
				updatedRoles += existingRolesVec[i];
			}

			// Replace the old roles with updated roles
			updatedUser.replace(rolesPos + 7, endOfRolesPos - (rolesPos + 7), updatedRoles);
		}
	}
	std::cout << "USERDATA end: " << updatedUser << "\n";
	return updatedUser;
}
void IDCardLog::updateUserDataFile(const std::vector<std::string>& updatedUserData) {
	std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::trunc); // Open file in truncation mode to clear its contents

	if (outputFile.is_open()) {
		for (const std::string& user : updatedUserData) {
			outputFile << user << "\n"; // Write each updated user data to the file
		}
		outputFile.close(); // Close the file after writing
		std::cout << "User data updated in the log file.\n";
	}
	else {
		std::cerr << "Unable to open file\n"; // Display an error message if the file couldn't be opened
	}
}

// function to remove a user from the log file
void IDCardLog::removeUserFromLogFile(int index) {
	// Read user data from the log file and store in vector
	std::vector<std::string> userData = readUserDataFromFile();

	// Check if the index is within the bounds of user data, which is how many lines are in the file
	if (index >= 0 && index < userData.size()) {
		// Display the user being removed
		std::cout << "Removing user: " << userData[index] << std::endl;

		// Erase the user data at the specified index
		userData.erase(userData.begin() + index);

		// Open the file in truncation mode to clear it
		std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::trunc);
		if (outputFile.is_open()) {
			// Write the updated user data back to the file
			for (const std::string& user : userData) {
				outputFile << user << "\n";
			}
			outputFile.close(); // Close the file after writing

			// Indicate successful removal
			std::cout << "User removed from the log file.\n";
		}
		// Error message if unable to open the file
		else {
			std::cerr << "Unable to open file\n";
		}
	}
	// Display an error if the index is out of bounds
	else {
		std::cout << "Invalid index.\n";
	}
}

void IDCardLog::updateUserInLogFile(int index, const std::string& newForename, const std::string& newSurname, bool generateCard) {
	std::vector<std::string> userData = readUserDataFromFile();

	if (index >= 0 && index < userData.size()) {
		std::string& userToUpdate = userData[index];

		// Extract existing role and swipe card ID from the user data
		std::string existingRole, swipeCardID;
		size_t roleStart = userToUpdate.find("Role: ");
		if (roleStart != std::string::npos) {
			size_t roleEnd = userToUpdate.find(",", roleStart);
			existingRole = userToUpdate.substr(roleStart + 6, roleEnd - roleStart - 6);
		}

		size_t swipeCardStart = userToUpdate.find("Swipe Card ID: ");
		if (swipeCardStart != std::string::npos) {
			swipeCardID = userToUpdate.substr(swipeCardStart + 15);
		}

		// Update forename and/or surname if provided
		size_t nameStart = userToUpdate.find("Name: ") + 6;
		size_t commaPosition = userToUpdate.find(",", nameStart); // Find the comma after the name
		size_t surnameStart = userToUpdate.find(" ", nameStart); // Find the space between forename and surname


		// Update surname if provided
		if (!newSurname.empty()) {
			if (surnameStart != std::string::npos) {
				size_t spaceAfterSurname = userToUpdate.find(" ", surnameStart + 1);
				size_t surnameLength = (spaceAfterSurname != std::string::npos) ? spaceAfterSurname - (surnameStart + 1) : userToUpdate.length() - (surnameStart + 1);

				userToUpdate.replace(surnameStart + 1, surnameLength, newSurname + ",");

			}
		}

		// Update forename if provided
		//TODO HAVE A RANT HERE
		// TODO FIX THAT COMMA SOMETIMES APPEARS AFTER ADDING A SURNAME AND SOMETIMES DOESN'T?
		// TODO SET BREAKPOINT AT THIS FUNCTION AND GO THROUGH AND CHECK THESE NESTED IF ELSE STATEMENTS I HAVE A FEELING THEY NEVER GET CALLED
		if (!newForename.empty()) {
			size_t spaceAfterName = userToUpdate.find(" ", nameStart);
			size_t forenameLength = (spaceAfterName != std::string::npos) ? spaceAfterName - nameStart : userToUpdate.length() - nameStart;

			userToUpdate.replace(nameStart, forenameLength, newForename);

		}


		if (generateCard) {
			SwipeCard card("");
			swipeCardID = card.addSwipeCard();
			userToUpdate.replace(userToUpdate.find("Swipe Card ID: ") + 15, userToUpdate.find("\n") - (userToUpdate.find("Swipe Card ID: ") + 15), swipeCardID);
		}

		std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::trunc);
		if (outputFile.is_open()) {
			for (const std::string& user : userData) {
				outputFile << user << "\n";
			}
			outputFile.close();
			std::cout << "User information updated.\n";
		}
		else {
			std::cerr << "Unable to open file\n";
		}
	}
	else {
		std::cout << "Invalid index.\n";
	}
}
