#include "pch.h"
#include "../AccessControlSystem/User.cpp"
#include "../AccessControlSystem/SwipeCard.cpp"
#include"../AccessControlSystem/IDCardLog.cpp"
TEST(UserTest, GetUserIDTest) {
	User user("John", "Doe", "", 1);
	ASSERT_EQ(user.getUserID(), 1); // Test initial user ID
	ASSERT_EQ(user.getUserID(), 2); // Test the increment of user ID
}

TEST(UserTest, GetForenameTest) {
	User user("John", "Doe", "", 1);
	ASSERT_EQ(user.getForename(), "John");
}

TEST(UserTest, GetSurnameTest) {
	User user("John", "Doe", "", 1);
	ASSERT_EQ(user.getSurname(), "Doe");
}

TEST(UserTest, GetFullNameTest) {
	User user("John", "Doe", "", 1);
	ASSERT_EQ(user.getFullName(), "John Doe");
}

// A test case for displayUsersAlphabetically when the log file is empty
TEST(UserTest, DisplayUsersAlphabetically_EmptyLogFile) {
	User user("John", "Doe", "", 1);
	testing::internal::CaptureStdout();

	// Assuming readUserDataFromFile returns an empty vector for an empty log file
	user.displayUsersAlphabetically();

	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "No users found in the log file.\n");
}

// A test case for displayUsersAlphabetically with user names in log file
// A test case for displayUsersAlphabetically with user names in log file
//TEST(UserTest, DisplayUsersAlphabetically_NonEmptyLogFile) {
//	User user("", "", "", 1);
//	// Mocking the readUserDataFromFile to return some data
//	std::vector<std::string> mockData = {
//		"Name: jack gerry, Role : Visitor / Guest, Swipe Card ID : 805551823, User ID : 1",
//		"Name : jack smith, Role : Manager, Swipe Card ID : 503655319, User ID : 1",
//		"Name : jack gerry, Role : Student, Swipe Card ID : 995636067, User ID : 1",
//		"Name : adam smith, Role : Security, Swipe Card ID : 684549606, User ID : 1"
//	};
//	testing::internal::CaptureStdout();
//
//	// Mock the readUserDataFromFile to return mock data
//	EXPECT_CALL(IDCardLog, readUserDataFromFile()).WillOnce(testing::Return(mockData));
//
//	// Assuming readUserDataFromFile returns mockData
//	user.displayUsersAlphabetically();
//
//	std::string output = testing::internal::GetCapturedStdout();
//	EXPECT_NE(output.find("ALPHABETICAL LIST OF USERS"), std::string::npos);
//	EXPECT_NE(output.find("Name: adam smith"), std::string::npos);
//	EXPECT_NE(output.find("Name: jack gerry"), std::string::npos);
//	EXPECT_NE(output.find("Name: jack gerry"), std::string::npos);
//	EXPECT_NE(output.find("Name: jack smith"), std::string::npos);
//}
