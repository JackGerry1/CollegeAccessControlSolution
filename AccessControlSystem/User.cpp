// User.cpp : This file contains functions and attributes specifeid in the User.h file. 

#include "User.h"

/*
References:
GeeksForGeeks (2023a) 'Sort string of characters', GeeksforGeeks. 
Available at: https://www.geeksforgeeks.org/sort-string-characters/ [Accessed 14th December 2023].

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

Programiz (2023b) 'C++ Map', Programiz. 
Available at: https://www.programiz.com/cpp-programming/map [Accessed 30th December 2023].

Sinha, A. (2022). string::npos in C++. [Online] CodeSpeedy. 
Available at: https://www.codespeedy.com/stringnpos-in-cpp/ [Accessed 18th December 2023].
*/


// Constructor initializing user details for forename surname role user id and swipecard
User::User(std::string forename, std::string surname, std::vector<std::string> roles)
	: forename(forename), surname(surname), roles(roles) {}

// Function: getFullName
// Objective: get full name comprised of forename and surname
std::string User::getFullName() const {
	// Concatenate forename and surname with a space in between
	return forename + " " + surname;
} // end of getFullName

// Function: getRoles
// Objective: get user roles
std::vector<std::string> User::getRoles() const {
	// Return the vector containing the user's roles
	return roles;
} // end of getRoles


// Function: modifyNameInput
// Paramaters: string input, which will be the forename or surname
// Objective: Turn input into this form eg "JACk" becomes "Jack" 
// to allow the sorting users alphabetically to work correctly because it is case sensitive
std::string User::modifyNameInput(const std::string& input) {
	std::string modifiedInput = input;

	// Convert all characters to lowercase
	for (auto& c : modifiedInput) {
		c = std::tolower(c);
	}

	// Capitalise the first character
	if (!modifiedInput.empty()) {
		modifiedInput[0] = std::toupper(modifiedInput[0]);
	}

	return modifiedInput;
} // end of modifyNameInput


// Function: addUser
// Purpose: Allows user creation and logs user information
void User::addUser() {
	// Declare variables for forename and surname
	std::string newForename, newSurname;
	SwipeCard swipeCard("");
	// Get forename and surname from user input
	std::cout << "Enter forename: ";
	std::cin >> newForename;

	// Modify the forename input
	newForename = modifyNameInput(newForename);

	std::cout << "Enter surname: ";
	std::cin >> newSurname;

	// Modify the surname input
	newSurname = modifyNameInput(newSurname);

	// Assign the entered values to the user's forename and surname
	forename = newForename;
	surname = newSurname;

	// Invoke function to add multiple roles for the user
	roles = addRoles();

	// Construct user information string: includes name, roles, and swipe card ID
	std::string userInfo = "Name: " + getFullName() + ", Roles:";
	for (int i = 0; i < roles.size(); ++i) {
		userInfo += " " + roles[i];

		// add a comma along as you are not at the last role for that user
		if (i != roles.size() - 1) {
			userInfo += ",";
		}
	}
	// Add swipe card information to the user's data
	userInfo += ", Swipe Card ID: " + swipeCard.addSwipeCard() + "\n";

	// Log user information to a log file
	IDCardLog::logUserData(userInfo);
	std::cout << "Added User Info: " << userInfo << "\n";
} // end of addUser


// Function: getRoleFromChoice
// Parameters: int choice - integer representing a user's role choice
// Objective: std::string - role corresponding to the given choice
std::string User::getRoleFromChoice(int choice) {
	// Switch statement to determine the role based on the choice parameter
	switch (choice) {
		// Case 1: Staff Member
	case 1:
		return "Staff Member";
		// Case 2: Student
	case 2:
		return "Student";
		// Case 3: Visitor / Guest
	case 3:
		return "Visitor / Guest";
		// Case 4: Contract Cleaner
	case 4:
		return "Contract Cleaner";
		// Case 5: Manager
	case 5:
		return "Manager";
		// Case 6: Security
	case 6:
		return "Security";
		// Case 7: Emergency Responder
	case 7:
		return "Emergency Responder";
		// Default case: No Role - for choices other than 1-7
	default:
		return "No Role";
	}
} // end of getRoleFromChoice


// Function: displayRoleMenuAndGetChoice
// Returns: int - the chosen role's corresponding number
// Objective: Displays a menu of available roles and prompts the user to choose one
int User::displayRoleMenuAndGetChoice() {
	int choice;

	// Displaying the menu of available roles
	std::cout << "Enter roles:\n";
	std::cout << "1. Staff Member\n";
	std::cout << "2. Student\n";
	std::cout << "3. Visitor / Guest\n";
	std::cout << "4. Contract Cleaner\n";
	std::cout << "5. Manager\n";
	std::cout << "6. Security\n";
	std::cout << "7. Emergency Responder\n";

	// Validate user input within the range 1-7
	do {
		std::cout << "Enter your choice (1-7): ";
		std::cin >> choice;
	} while (choice < 1 || choice > 7); // Continue prompting until valid input is provided

	return choice; // Return the user's chosen role number
} // end of displayRoleMenuAndGetChoice

// Function: addRoles
// Returns: std::vector<std::string> - a vector containing the roles added by the user
// Objective: Allows the user to add multiple roles to their profile
std::vector<std::string> User::addRoles() {
	const int maxRoles = 7; // Maximum number of roles allowed
	std::vector<std::string> addedRoles; // Vector to store added roles
	int numRoles;

	// User input: number of roles to add
	std::cout << "Enter the number of roles to add: ";
	std::cin >> numRoles; 

	// Limit the number of roles to the maximum allowed
	if (numRoles > maxRoles) {
		std::cout << "You can add a maximum of " << maxRoles << " roles.\n";
		numRoles = maxRoles; 
	}
	// Loop to prompt the user for each role choice
	for (int i = 0; i < numRoles; ++i) {
		// Get role choice from the displayRoleMenuAndGetChoice function
		int choice = displayRoleMenuAndGetChoice();

		// Retrieve the role string based on the user's choice
		std::string role = getRoleFromChoice(choice);

		// Add the role to the vector of addedRoles
		addedRoles.push_back(role);
	}

	return addedRoles; // Return the vector containing all added roles
} // end of addRoles

// Function: addRoleToUser
// Purpose: Allows addition of roles to a selected user retrieved from the log file
void User::addRoleToUser() {
	// Retrieve user data from the log file
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	// Check if user data is available
	if (!userData.empty()) {
		// Display the users available in the log file
		IDCardLog::displayUsersFromLogFile();

		// User input: index of the user to modify
		int index;
		std::cout << "Enter the index of the user to add roles: ";
		std::cin >> index; 

		// Validate the entered index
		if (index >= 0 && index < userData.size()) {
			std::string selectedUser = userData[index];
			std::cout << "Selected User: " << selectedUser << std::endl;

			// Prompt to add roles to the selected user
			std::vector<std::string> rolesToAdd = addRoles();

			// Update the roles of the selected user
			std::string updatedUser = IDCardLog::updateUserRoles(selectedUser, rolesToAdd);

			// Update user data with the modified user information
			userData[index] = updatedUser;
			IDCardLog::updateUserDataFile(userData);

			// Display confirmation of added roles to the user at the specified index
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
} // end of addRoleToUser

// Function: removeUser
// Objective: Removes a user from the log file based on the user's choice of index
void User::removeUser() {
	// Reading user data from a file and storing it in a vector
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	// Checking if the user data vector is not empty
	if (!userData.empty()) {
		// Displaying available users from the log file
		IDCardLog::displayUsersFromLogFile();

		// Taking user input for the index of the user to remove
		int index;
		std::cout << "Enter the index of the user you want to remove: ";
		std::cin >> index;

		// Removing the user based on the provided index from the log file
		IDCardLog::removeUserFromLogFile(index);
	}
	// error if no user are found in the log file
	else {
		std::cout << "No users found in the log file. Nothing to remove.\n\n";
	}
} // end of removeUser


// Function: updateUser
// Objective: Allows updating user information in the log file based on user input
void User::updateUser() {
	// Reading user data from a file and storing it in a vector
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	// Checking if the user data vector is not empty
	if (!userData.empty()) {
		// Displaying available users from the log file
		IDCardLog::displayUsersFromLogFile();

		int index;
		std::cout << "Enter the index of the user you want to update: ";
		std::cin >> index; // User input: index of the user to update

		// Validating the entered index
		if (index >= 0 && index < userData.size()) {
			system("cls"); // Clear the screen
			std::cout << "Updating user at index: " << index << std::endl;

			std::string newForename, newSurname;
			std::string newRole;
			bool generateCard = false;

			std::cin.ignore(); // Clear buffer

			// Prompting for and receiving new forename and surname
			std::cout << "Enter new forename (Leave blank to keep unchanged): ";
			std::getline(std::cin, newForename);

			// Modify the forename input
			newForename = modifyNameInput(newForename);

			std::cout << "Enter new surname (Leave blank to keep unchanged): ";
			std::getline(std::cin, newSurname);

			// Modify the surname input
			newSurname = modifyNameInput(newSurname);

			// Prompting for generating a new swipe card
			std::cout << "Do you want to generate a new swipe card? (yes/no): ";
			std::string generateCardInput;
			std::cin >> generateCardInput;

			// set generate card to true meaning it will be updated in the updateUserInLogFile funciton
			if (generateCardInput == "yes") {
				generateCard = true;
			}

			// Update the user's information in the log file
			IDCardLog::updateUserInLogFile(index, newForename, newSurname, generateCard);

			// Output the result of the changes
			std::cout << "User updated with:\nForename: " << newForename << "\nSurname: " << newSurname
				<< "\nSwipe card updated: " << (generateCard ? "Yes" : "No") << std::endl;
		}
		// error for invalid index entered
		else {
			std::cout << "Invalid index.\n";
		}
	}
	// erorr for no users in log file
	else {
		std::cout << "No users found in the log file.\n\n";
	}
}

// Function: removeSwipeCardInput
// Objective: get the correct user input and pass into the removeSwipeCard for the rest of the functionality
void User::removeSwipeCardInput() {
	// read data and put into a vector of strings, where each element is a user
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	// blank swipecard declartion
	SwipeCard swipeCard("");

	// make sure that there are users in the log file
	if (userData.empty()) {
		std::cout << "No users found in the log file.\n";
		return;
	}

	// display the current users
	IDCardLog::displayUsersFromLogFile();
	
	// ask for user input for the index of the swipecard that they want removed
	int userIndex;
	std::cout << "Enter the index/line number of the user to remove the swipe card from: ";
	std::cin >> userIndex;

	// Pass userIndex and userData to the SwipeCard removal function
	swipeCard.removeSwipeCard(userIndex, userData);
} // end of removeSwipeCardInput

// Function: removeRole
// Objective: Removes a role from a user's information in the log file
void User::removeRole() {
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();

	// Check if user data vector is empty
	if (userData.empty()) {
		std::cout << "No users found in the log file.\n";
		return;
	}

	// Display available users from the log file
	IDCardLog::displayUsersFromLogFile();

	// prompt for index 
	int userIndex;
	std::cout << "Enter the index of the user to remove a role from: ";
	std::cin >> userIndex;

	// Validate the entered user index
	if (userIndex < 0 || userIndex >= userData.size()) {
		std::cout << "Invalid user index.\n";
		return;
	}

	// outputs the selected user
	std::string selectedUser = userData[userIndex];
	std::cout << "Selected User: " << selectedUser << std::endl;

	// Find the position of the "Roles: " substring in the user's information
	// It identifies the starting point of the roles in the user data
	size_t rolesPos = selectedUser.find("Roles: ");
	if (rolesPos == std::string::npos) {
		std::cout << "Roles information not found for this user.\n";
		return;
	}

	// Find the position of "Swipe Card ID: " after the roles information
	// Identifies the end point of roles and the start of the swipe card data
	size_t swipeCardIDPos = selectedUser.find("Swipe Card ID: ", rolesPos);
	if (swipeCardIDPos == std::string::npos) {
		std::cout << "Invalid user data format.\n";
		return;
	}

	// Extract the existing roles as a substring
	std::string existingRoles = selectedUser.substr(rolesPos + 7, swipeCardIDPos - (rolesPos + 9));

	// Parse the existing roles into a vector using stringstream
	// Separates individual roles into a vector for manipulation
	std::istringstream rolesStream(existingRoles);
	std::vector<std::string> existingRolesVec;
	std::string roleToken;
	while (std::getline(rolesStream, roleToken, ',')) {
		existingRolesVec.push_back(roleToken);
	}

	// Check if no roles are found for this user
	if (existingRolesVec.empty()) {
		std::cout << "No roles found for this user.\n";
		return;
	}

	// ask user for role index
	int roleIndex;
	std::cout << "Enter the index of the role to remove (0-" << existingRolesVec.size() - 1 << "): ";
	std::cin >> roleIndex;

	// Validate the entered role index
	if (roleIndex < 0 || roleIndex >= existingRolesVec.size()) {
		std::cout << "Invalid role index.\n";
		return;
	}

	// Remove the role from the existingRolesVec based on the provided index
	existingRolesVec.erase(existingRolesVec.begin() + roleIndex);

	// Reconstruct the updated user information with the removed role
	std::ostringstream updatedUserStream;

	// add info after the "Name: " up until ", Roles"
	updatedUserStream << "Name: " << selectedUser.substr(6, rolesPos - 8);
	updatedUserStream << ", Roles: ";

	// Append the remaining roles back onto the updated user stream separated by a comma
	if (!existingRolesVec.empty()) {
		for (int i = 0; i < existingRolesVec.size(); ++i) {
			// put the remaining roles into the updated user stream
			updatedUserStream << existingRolesVec[i];
			updatedUserStream << ",";
		}
	}
	// this is for the first role, or if you remove the last role from a user 
	// it keeps the same format to allow roles to be added back again
	else {
		updatedUserStream << ",";
	}

	// Generate the updated user information string 
	std::string updatedUser = updatedUserStream.str();

	// updatedUser contains name and role info and then add the swipecard info for that selected user
	userData[userIndex] = updatedUser + selectedUser.substr(swipeCardIDPos - 1);

	// Replace double spaces with single space in the updated user information
	// Did this because I could not figure out where the double space issue was caused in the above program, 
	// so just decided to replace them with single spaces instead. 
	size_t found = userData[userIndex].find("  ");
	while (found != std::string::npos) {
		userData[userIndex].replace(found, 2, " ");
		found = userData[userIndex].find("  ", found + 1);
	}

	// Update the log file with the modified user information
	IDCardLog::updateUserDataFile(userData);

	// Output the result of the role removal
	std::cout << "Role removed from the user at index " << userIndex << ":\n";
	std::cout << "Updated User Info: " << userData[userIndex] << std::endl;
} // end of removeRole

// Function: displayUsersAlphabetically
// Objective: display current users alphabetically 
void User::displayUsersAlphabetically() {
	// Initialize containers for user data
	std::vector<std::string> names; // Container to store user names
	std::map<std::string, std::vector<std::string>> userRoles; // Map to associate roles with users
	std::map<std::string, std::string> swipeCardIDs; // Map to associate swipe card IDs with users

	// Read user data from the file
	std::vector<std::string> userData = IDCardLog::readUserDataFromFile();
	std::string token, name, swipeID;

	// Proceed if user data exists
	if (!userData.empty()) {
		// Loop through each user data entry
		for (const std::string& userString : userData) {
			std::istringstream ss(userString); // Create a string stream to process user data
			std::vector<std::string> userRolesVector; // Initialize a vector to store user roles

			// Parse user data string into tokens separated by commas
			while (std::getline(ss, token, ',')) {
				// Extract user's name
				if (token.find("Name:") != std::string::npos) {
					size_t namePos = token.find("Name:");
					name = token.substr(namePos + 6); // Extract the user's name from the token
				}
				// Extract user's roles
				else if (token.find("Roles:") != std::string::npos) {
					// Extract existing roles associated with the user
					std::string existingRoles; // Variable to store extracted existing roles
					size_t rolePos = userString.find("Roles:"); // Find the position of "Roles:" in the user string
					size_t startSwipeCardIDPos = userString.find("Swipe Card ID:", rolePos); // Find the position of "Swipe Card ID:" after "Roles:"

					// Check if positions for roles and swipe card ID exist
					if (rolePos != std::string::npos && startSwipeCardIDPos != std::string::npos) {
						// Extract existing roles from the user string
						existingRoles = userString.substr(rolePos + 7, startSwipeCardIDPos - (rolePos + 9)); // Extract roles substring between "Roles:" and "Swipe Card ID:"
						std::istringstream rolesStream(existingRoles); // Create a string stream to process the extracted roles
						std::string roleToken; // Variable to store individual role tokens

						// Split the existing roles into individual role tokens separated by commas
						while (std::getline(rolesStream, roleToken, ',')) {
							userRolesVector.push_back(roleToken); // Store individual roles in the userRolesVector
						}
					}
				}
				// Extract user's swipe card ID
				else if (token.find("Swipe Card ID:") != std::string::npos) {
					size_t swipeCardIDPos = token.find("Swipe Card ID:");
					swipeID = token.substr(swipeCardIDPos + 15); // Extract the swipe card ID from the token
				}
			}

			// Store user data into respective containers
			names.push_back(name);
			userRoles[name] = userRolesVector;
			swipeCardIDs[name] = swipeID; // Associate swipe card ID with the user's name
		}

		// Sort user names alphabetically
		std::sort(names.begin(), names.end());

		// Display sorted user information in the form
		// Name: Jack Blackwood, Roles: Student, Swipe Card ID: 559072654
		std::cout << "\nALPHABETICAL LIST OF USERS" << std::endl;
		for (const auto& name : names) {
			std::cout << "Name: " << name << ", Roles: ";
			// Display user roles there can be more than one so that is why it is in a nested loop
			for (const auto& role : userRoles[name]) {
				std::cout << role << ",";
			}
			// Retrieve and append swipe card ID using the user's name
			std::cout << " Swipe Card ID: " << swipeCardIDs[name] << std::endl; 
		}
	}
	else {
		// If no user data found in the log file
		std::cout << "No users found in the log file.\n";
	}
} // end of displayUsersAlphabetically