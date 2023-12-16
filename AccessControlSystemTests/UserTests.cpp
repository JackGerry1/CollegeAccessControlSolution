// UserTests.cpp : This file contains the tests for the User class
// Include the paths to the required files in the AccessControlSystem project
#include "pch.h"
#include "../AccessControlSystem/User.cpp"
#include "../AccessControlSystem/SwipeCard.cpp"
#include"../AccessControlSystem/IDCardLog.cpp"

// Test for the GetUser ID function
TEST(UserTest, GetUserIDTest) {
	// Create exampe user and check if the id increments
	User user("John", "Doe", "", 1);
	ASSERT_EQ(user.getUserID(), 1);
	ASSERT_EQ(user.getUserID(), 2);
}

// Test for the GetFullName function
TEST(UserTest, GetFullNameTest) {
	// Create exampe user
	User user("John", "Doe", "", 1);

	// Check if the user's full name matches the expected value
	ASSERT_EQ(user.getFullName(), "John Doe");
}

// Test for displaying users alphabetically when the log file is empty
TEST(UserTest, DisplayUsersAlphabetically_EmptyLogFile) {
	// Create example user
	User user("John", "Doe", "", 1);

	// Redirect standard output for capturing
	testing::internal::CaptureStdout();

	// Display users alphabetically (in this case, an empty log file)
	user.displayUsersAlphabetically();

	// Retrieve the captured output
	std::string output = testing::internal::GetCapturedStdout();

	// Check if the output matches the expected message when the log file is empty
	EXPECT_EQ(output, "No users found in the log file.\n");
}
