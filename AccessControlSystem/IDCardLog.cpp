//IDCardLog.cpp : This file contains functions and attributes specifeid in the IDCardLog.h file.

#include "IDCardLog.h"

/*
References:
Cplusplus.com (2023) 'std::vector::erase', Cplusplus.com.
Available at: https://cplusplus.com/reference/vector/vector/erase/ [Accessed 18th December 2023].

Kaushik, A. (2022) 'C++ String Replace Function', Scaler Topics.
Available at: https://www.scaler.com/topics/cpp-string-replace/ [Accessed 18th December 2023].

Ram, V. (2022) 'How to use the string find() in C++', DigitalOcean.
Available at: https://www.digitalocean.com/community/tutorials/string-find-c-plus-plus [Accessed 18th December 2023].

Cppreference (2023) 'std::size_t - cppreference.com', en.cppreference.com.
Available at: https://en.cppreference.com/w/cpp/types/size_t [Accessed 18th December 2023].

GeeksForGeeks (2023b) 'Substring in C++', GeeksforGeeks.
Available at: https://www.geeksforgeeks.org/substring-in-cpp/ [Accessed 18th December 2023].

Programiz (2023a) 'C++ File Handling', Programiz. 
Available at: https://www.programiz.com/cpp-programming/file-handling [Accessed 14th December 2023].

Instructables (n.d.) 'How to Do the Singleton Design Pattern in C++', Instructables. 
Available at: https://www.instructables.com/How-to-Do-the-Singleton-Design-Pattern-in-C/ [Accessed 27th December 2023].

Sinha, A. (2022). string::npos in C++. [Online] CodeSpeedy.
Available at: https://www.codespeedy.com/stringnpos-in-cpp/ [Accessed 18th December 2023].
*/

// Set the IDCardLog instance to a nullptr;
IDCardLog* IDCardLog::instance = nullptr;

// Blank Constructor for IDCardLog
IDCardLog::IDCardLog() {}

// Function: getInstance
// Objective: If no instance of the IDCardLog class exists create one, whilst preventing it from creating multiple of them. 
IDCardLog* IDCardLog::getInstance() {
	// only create new instance if one does not exist
	// else return the one that currently exists. 
	if (!instance) {
		instance = new IDCardLog();
	}
	return instance;
} // end of getInstance

// Function: logUserData
// Objective: Log user data when creating a new user
void IDCardLog::logUserData(const std::string& userInfo) {
	// Open the file in append mode within the "LogFiles" directory
	std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::app);

	// Check if the file is successfully opened
	if (outputFile.is_open()) {
		// Write user information to the file
		outputFile << userInfo;

		// Close the file after writing
		outputFile.close();
	}
	// If the file couldn't be opened, display an error message to standard error
	else {
		std::cerr << "Unable to open file\n";
	}
} // end of logUserData

// Function: readUserDataFromFile
// Objective: read user data from the file in a vector friendy form
std::vector<std::string> IDCardLog::readUserDataFromFile() {
	// Open the file for reading
	std::ifstream inputFile("LogFiles/ID_Card_List.txt");

	// Vector to hold user data read from the file
	std::vector<std::string> userData;

	// Check if the file was opened successfully
	if (inputFile.is_open()) {
		// Temporary variable to store each line read from the file
		std::string line;

		// Read each line from the file and add it to the vector
		while (std::getline(inputFile, line)) {
			userData.push_back(line);
		}

		// Close the file after reading
		inputFile.close();
	}
	// If the file couldn't be opened, display an error message
	else {
		std::cerr << "Unable to open file\n";
	}

	// Return the vector containing user data read from the file
	return userData;
} // end of readUserDataFromFile


// function to displayUsersfrom the Log File
void IDCardLog::displayUsersFromLogFile() {
	// Read user data from the log file and store in a vector of strings
	std::vector<std::string> userData = readUserDataFromFile();

	// Check if user data is available
	if (!userData.empty()) {
		// Display header for user list
		std::cout << "Current Users:\n";

		// Loop through the user data vector and display each user's information
		for (int i = 0; i < userData.size(); ++i) {
			std::cout << i << ". " << userData[i] << '\n'; // Display user information with index
		}

		// Add an extra line for readability
		std::cout << "\n";
	}
	else {
		// Display message if no users are found in the log file
		std::cout << "No users found in the log file.\n";
	}
} // end of displayUsersFromLogFile

// Function: updateUserRoles
// Paramaters: string userData, vector of rolesToAdd
// Objective: update the users roles for a specific user
std::string IDCardLog::updateUserRoles(const std::string& userData, const std::vector<std::string>& rolesToAdd) {
	// Make a copy of the input user data
	std::string updatedUser = userData;

	// Find the starting position of the 'Roles: ' substring in the user data
	size_t rolesPos = updatedUser.find("Roles: ");

	// Check if 'Roles: ' substring is found
	if (rolesPos != std::string::npos) {
		// Find the position of 'Swipe Card ID: ' after 'Roles: ' substring
		size_t swipeCardIDPos = updatedUser.find("Swipe Card ID: ", rolesPos);

		// Check if 'Swipe Card ID: ' is found after 'Roles: '
		if (swipeCardIDPos != std::string::npos) {
			// Find the end position of roles, considering it ends at the "," which is just before "Swipe Card ID: "
			size_t endOfRolesPos = updatedUser.find(",", rolesPos);
			if (endOfRolesPos == std::string::npos || endOfRolesPos > swipeCardIDPos) {
				endOfRolesPos = swipeCardIDPos;
			}

			// Extract existing roles as a substring, which is after "Roles: " but before "Swipe Card ID: "
			std::string existingRoles = updatedUser.substr(rolesPos + 7, endOfRolesPos - (rolesPos + 7));

			// Create a stringstream to tokenize the existing roles
			std::istringstream rolesStream(existingRoles); 

			// Vector to store existing roles
			std::vector<std::string> existingRolesVec; 
			
			// variable to store each role, before it goes into the vector of roles
			std::string roleToken; 

			// Tokenize the existing roles based on commas and store them in a vector
			while (std::getline(rolesStream, roleToken, ',')) {
				existingRolesVec.push_back(roleToken); 
			}

			// Append new roles that are not already present in the existing roles vector at the end of it
			for (const auto& newRole : rolesToAdd) {
				// Check if the new role is not already in the existing roles vector
				if (std::find(existingRolesVec.begin(), existingRolesVec.end(), newRole) == existingRolesVec.end()) {
					// If the new role is not found in existing roles, add it to the vector
					existingRolesVec.push_back(newRole);
				}
			}

			// Join roles into a string with commas
			std::string updatedRoles;
			for (int i = 0; i < existingRolesVec.size(); ++i) {
				// dont need to append a comma if the it is the first role
				if (i != 0) {
					updatedRoles += ", ";
				}
				updatedRoles += existingRolesVec[i];
			}

			// Replace the old roles with the updated roles in the user data
			updatedUser.replace(rolesPos + 7, endOfRolesPos - (rolesPos + 7), updatedRoles);
		}
	}

	// Return the updated user data
	return updatedUser;
} // end of updateUserRoles

// Function: updateUserDataFile
// Paramaters: vector of updatedUserInfo
// Objective: update the users info for a specific user
void IDCardLog::updateUserDataFile(const std::vector<std::string>& updatedUserData) {
	// Open the file in truncation mode to clear its contents or create a new file
	std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::trunc);

	// Check if the file was opened successfully
	if (outputFile.is_open()) {
		// Iterate through each updated user data in the vector
		for (const std::string& user : updatedUserData) {
			outputFile << user << "\n"; // Write each updated user data to the file
		}

		outputFile.close(); // Close the file after writing
		std::cout << "User data updated in the log file.\n"; // Display success message
	}
	else {
		std::cerr << "Unable to open file\n"; // Display an error message if the file couldn't be opened
	}
} // end of updateUserDataFile


// Function: removeUserFromLogFile
// Paramaters: index of user
// Objective: remove a specifc user from the log file and rewrite the log file. 
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
} // end of removeUserFromLogFile


// Function: updateUserInLogFile
// Paramaters: new forename, surname and whether true/false for updating swipecard and index of user to update
// Objective: update the user infomration based on the user input
void IDCardLog::updateUserInLogFile(int index, const std::string& newForename, const std::string& newSurname, bool generateCard) {
	// Read user data from the log file and store it in a vector of strings
	std::vector<std::string> userData = readUserDataFromFile();

	if (index >= 0 && index < userData.size()) {
		// Check if the provided index is within the bounds of available user data
		std::string& userToUpdate = userData[index]; // Get the user information at the provided index

		// Extract existing role and swipe card ID from the user data
		std::string existingRole, swipeCardID;

		// Find the starting position of the 'Role: ' substring in the user data
		size_t roleStart = userToUpdate.find("Role: ");
		if (roleStart != std::string::npos) {
			// Find the end position of the individual role substring, which is before the ","
			size_t roleEnd = userToUpdate.find(",", roleStart);
			// Extract the existing role information from the user data for each role, which is between "Role: " and "," after it
			existingRole = userToUpdate.substr(roleStart + 6, roleEnd - roleStart - 6);
		}

		// Find the starting position of the 'Swipe Card ID: ' substring in the user data
		size_t swipeCardStart = userToUpdate.find("Swipe Card ID: ");
		if (swipeCardStart != std::string::npos) {
			// Extract the existing swipe card ID information from the user data, which is after "Swipe Card ID: "
			swipeCardID = userToUpdate.substr(swipeCardStart + 15);
		}

		// Update forename and/or surname if required

		// find where the name stars, which is after the "Name: "
		size_t nameStart = userToUpdate.find("Name: ") + 6;

		// Find the comma after the name, which is where the role starts
		size_t commaPosition = userToUpdate.find(",", nameStart);

		// Find the space between forename and surname
		size_t surnameStart = userToUpdate.find(" ", nameStart); 

		// Update surname if provided
		if (!newSurname.empty()) {
			// Check if the surname exists in the user data
			if (surnameStart != std::string::npos) {
				// Find the position of the space after the current surnameStart position
				size_t spaceAfterSurname = userToUpdate.find(" ", surnameStart + 1);
				// Calculate the length of the current surname
				size_t surnameLength = (spaceAfterSurname != std::string::npos) ? spaceAfterSurname - (surnameStart + 1) : userToUpdate.length() - (surnameStart + 1);
				// Replace the current surname with the new surname in the user data
				userToUpdate.replace(surnameStart + 1, surnameLength, newSurname + ",");
			}
		}

		// Update forename if provided
		if (!newForename.empty()) {
			// Find the position of the space after the current forename
			size_t spaceAfterName = userToUpdate.find(" ", nameStart);
			// Calculate the length of the current forename
			size_t forenameLength = (spaceAfterName != std::string::npos) ? spaceAfterName - nameStart : userToUpdate.length() - nameStart;
			// Replace the current forename with the new forename in the user data
			userToUpdate.replace(nameStart, forenameLength, newForename);
		}

		// Generate a new swipe card if requested
		if (generateCard) {
			// Create a new SwipeCard object
			SwipeCard card("");
			// Generate a new swipe card ID
			swipeCardID = card.addSwipeCard();
			// Replace the existing swipe card ID with the new one in the user data
			userToUpdate.replace(userToUpdate.find("Swipe Card ID: ") + 15, userToUpdate.find("\n") - (userToUpdate.find("Swipe Card ID: ") + 15), swipeCardID);
		}

		// Display success message and update the log file with the modified user data
		std::cout << "User information updated.\n"; 
		updateUserDataFile(userData); 
	}
	// Display error message for invalid index
	else {
		std::cout << "Invalid index.\n"; 
	}
} // end of updateUserInLogFile

