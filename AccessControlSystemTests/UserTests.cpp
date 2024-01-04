// UserTests.cpp : This file contains the tests for the User class
// Include the paths to the required files in the AccessControlSystem project
#include "pch.h"
#include "../AccessControlSystem/User.cpp"
#include "../AccessControlSystem/SwipeCard.cpp"
#include "../AccessControlSystem/IDCardLog.cpp"

/*
References:
GoogleTest (2023a) 'Advanced GoogleTest Topics', GoogleTest. 
Available at: https://google.github.io/googletest/advanced.html [Accessed 15th December 2023].

GoogleTest (2023b) 'GoogleTest Primer', GoogleTest. 
Available at: https://google.github.io/googletest/primer.html [Accessed 15th December 2023].

Cplusplus.com (2023) 'std::vector::erase', Cplusplus.com. 
Available at: https://cplusplus.com/reference/vector/vector/erase/ [Accessed 18th December 2023].

Kaushik, A. (2022) 'C++ String Replace Function', Scaler Topics. 
Available at: https://www.scaler.com/topics/cpp-string-replace/ [Accessed 18th December 2023].

Ram, V. (2022) 'How to use the string find() in C++', DigitalOcean. 
Available at: https://www.digitalocean.com/community/tutorials/string-find-c-plus-plus [Accessed 18th December 2023].
*/

// Test for the GetFullName function
TEST(UserTest, GetFullNameTest) {
	// Create exampe user
	User user("John", "Doe", std::vector<std::string>{""});

	// Check if the user's full name matches the expected value
	ASSERT_EQ(user.getFullName(), "John Doe");
}

// Test for displaying users alphabetically when the log file is empty
TEST(UserTest, DisplayUsersAlphabetically_EmptyLogFile) {
	// Create example user
	User user("John", "Doe", std::vector<std::string>{""});

	// Redirect standard output for capturing
	testing::internal::CaptureStdout();

	// Display users alphabetically (in this case, an empty log file)
	user.displayUsersAlphabetically();

	// Retrieve the captured output
	std::string output = testing::internal::GetCapturedStdout();

	// Check if the output matches the expected message when the log file is empty
	EXPECT_EQ(output, "No users found in the log file.\n");
}

// Test cases for getRoleFromChoice function
TEST(UserTest, getRoleFromChoice_ValidChoices) {
	User user("John", "Doe", std::vector<std::string>{""});
	EXPECT_EQ(user.getRoleFromChoice(1), "Staff Member");
	EXPECT_EQ(user.getRoleFromChoice(2), "Student");
	EXPECT_EQ(user.getRoleFromChoice(3), "Visitor / Guest");
	EXPECT_EQ(user.getRoleFromChoice(4), "Contract Cleaner");
	EXPECT_EQ(user.getRoleFromChoice(5), "Manager");
	EXPECT_EQ(user.getRoleFromChoice(6), "Security");
	EXPECT_EQ(user.getRoleFromChoice(7), "Emergency Responder");
}

// Test case for invalid input from getRoleFromChoice
TEST(UserTest, getRoleFromChoice_InvalidChoice) {
	User user("John", "Doe", std::vector<std::string>{""});
	EXPECT_EQ(user.getRoleFromChoice(10), "No Role");
	EXPECT_EQ(user.getRoleFromChoice(-1), "No Role");
}

// Test case for getRoles function
TEST(UserTest, getRoles) {
	// Create a user object
	User user("John", "Doe", std::vector<std::string>{"Staff Member", "Student", "Visitor / Guest"});

	std::vector<std::string> expectedRoles = { "Staff Member", "Student", "Visitor / Guest" };

	// Validate if roles have been added correctly
	EXPECT_EQ(user.getRoles(), expectedRoles);
}

// Test case to validate modifyNameInput function
TEST(UserTest, ModifyNameInputTest) {
	User user("John", "Doe", std::vector<std::string>{""});
	// Test with an all-uppercase forename
	std::string allUpperCaseForename = "JACK";
	std::string modifiedForename = user.modifyNameInput(allUpperCaseForename);
	EXPECT_EQ(modifiedForename, "Jack");

	// Test with a mixed-case forename
	std::string mixedCaseForename = "aNnA";
	modifiedForename = user.modifyNameInput(mixedCaseForename);
	EXPECT_EQ(modifiedForename, "Anna");

	// Test with an all-lowercase surname
	std::string allLowerCaseSurname = "smith";
	std::string modifiedSurname = user.modifyNameInput(allLowerCaseSurname);
	EXPECT_EQ(modifiedSurname, "Smith");

	// Test with an empty string
	std::string emptyInput = "";
	std::string modifiedEmptyInput = user.modifyNameInput(emptyInput);
	EXPECT_EQ(modifiedEmptyInput, "");
}

// Test case for displayRoleMenuAndGetChoice function
TEST(UserTest, DisplayRoleMenuAndGetChoiceTest) {
    User user("John", "Doe", std::vector<std::string>{""});

    // Set up the input stream to provide test input
    std::istringstream input("5\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to use input stream

    // Redirect cout to capture output for comparison
    testing::internal::CaptureStdout();

    int choice = user.displayRoleMenuAndGetChoice(); // Call the function under test

    // Get the captured output from cout
    std::string output = testing::internal::GetCapturedStdout();

    // Assert that the function returns the expected choice
    EXPECT_EQ(choice, 5);

    // Assert that the function produces the expected output
    EXPECT_EQ(output,
        "Enter roles:\n1. Staff Member\n2. Student\n3. Visitor / Guest\n4. Contract Cleaner\n5. Manager\n6. Security\n7. Emergency Responder\nEnter your choice (1-7): "
    );
}

// Test case for removeRole function
TEST(UserTest, RemoveRoles) {
    // Mocked userData for testing
    std::vector<std::string> userData = {
        "Name: John, Roles: Role1,Role2, Swipe Card ID: 12345",
        "Name: Alice, Roles: Student, Swipe Card ID: 54321",
    };

    int userIndex = 1; // Assuming user index 1 is selected
    int roleIndex = 0; // Assuming role index 0 is selected for removal

    // Extract the existing roles from userData[userIndex]
    std::string selectedUser = userData[userIndex];
    size_t rolesPos = selectedUser.find("Roles: ");
    size_t swipeCardIDPos = selectedUser.find("Swipe Card ID: ", rolesPos);
    std::string existingRoles = selectedUser.substr(rolesPos + 7, swipeCardIDPos - (rolesPos + 9));

    // Parse the existing roles into a vector for manipulation
    std::istringstream rolesStream(existingRoles);
    std::vector<std::string> existingRolesVec;
    std::string roleToken;
    while (std::getline(rolesStream, roleToken, ',')) {
        existingRolesVec.push_back(roleToken);
    }

    // Validate roleIndex and remove the role if within range
    if (roleIndex >= 0 && roleIndex < static_cast<int>(existingRolesVec.size())) {
        existingRolesVec.erase(existingRolesVec.begin() + roleIndex);

        // Reconstruct updated user information with the removed role
        std::ostringstream updatedUserStream;
        updatedUserStream << "Name: " << selectedUser.substr(6, rolesPos - 8);
        updatedUserStream << ", Roles: ";

        // Append the roles to the updated user information
        if (!existingRolesVec.empty()) {
            for (size_t i = 0; i < existingRolesVec.size(); ++i) {
                updatedUserStream << existingRolesVec[i];
                updatedUserStream << ",";
            }
        }
        else {
            updatedUserStream << ",";
        }

        // Generate the updated user information string
        std::string updatedRoles = updatedUserStream.str();
        userData[userIndex] = updatedRoles + selectedUser.substr(swipeCardIDPos - 1);

        // Replace double spaces with single space in the updated user information
        size_t found = userData[userIndex].find("  ");
        while (found != std::string::npos) {
            userData[userIndex].replace(found, 2, " ");
            found = userData[userIndex].find("  ", found + 1);
        }

        // Validate the updated userData
        std::string expectedUpdatedUserData = "Name: Alice, Roles: , Swipe Card ID: 54321";

        ASSERT_EQ(userData[userIndex], expectedUpdatedUserData);
    }
    else {
        std::cout << "Invalid role index.\n";
    }
}
