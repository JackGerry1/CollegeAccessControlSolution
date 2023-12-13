#include "pch.h"
#include "../AccessControlSystem/User.cpp"
#include "../AccessControlSystem/SwipeCard.cpp"
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

TEST(UserTest, CompareByFullNameTest) {
    User user1("John", "Doe", "", 1);
    User user2("Jane", "Smith", "", 2);

    // Test if compareByFullName sorts correctly
    ASSERT_FALSE(User::compareByFullName(user1, user2)); // John Doe < Jane Smith
    ASSERT_TRUE(User::compareByFullName(user2, user1)); // Jane Smith > John Doe
}

TEST(UserTest, DisplayUsersAlphabeticallyTest) {
    std::vector<User> users = {
        User("John", "Doe", "", 1),
        User("Jane", "Smith", "", 2),
        User("Alice", "Johnson", "", 3)
    };

    // Sort users and check output
    testing::internal::CaptureStdout(); // Redirect stdout
    User::displayUsersAlphabetically(users);
    std::string output = testing::internal::GetCapturedStdout(); // Get printed output

    // Check if the output contains expected user names in alphabetical order
    ASSERT_NE(output.find("Alice Johnson"), std::string::npos);
    ASSERT_LT(output.find("Alice Johnson"), output.find("Jane Smith"));
    ASSERT_LT(output.find("Jane Smith"), output.find("John Doe"));
}