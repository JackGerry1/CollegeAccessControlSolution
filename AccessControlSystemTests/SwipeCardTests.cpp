// SwipeCardTests.cpp : This file contains the tests for the SwipeCard class
// Include the paths to the required files in the AccessControlSystem project
#include "pch.h"
#include "../AccessControlSystem/SwipeCard.h"  // Include SwipeCard header

/*
References:
GoogleTest (2023a) 'Advanced GoogleTest Topics', GoogleTest.
Available at: https://google.github.io/googletest/advanced.html [Accessed 15th December 2023].

GoogleTest (2023b) 'GoogleTest Primer', GoogleTest.
Available at: https://google.github.io/googletest/primer.html [Accessed 15th December 2023].
*/

// Test case for addSwipeCard function
TEST(SwipeCardTest, AddSwipeCardTest) {
    // blank swipecard object
    SwipeCard swipeCard("");

    // call the addSwipeCard function
    std::string generatedCardID = swipeCard.addSwipeCard();

    // Assert
    // Check if the generated card ID has the correct length
    ASSERT_EQ(generatedCardID.length(), 9);

    // Check if the generated card ID contains only digits
    for (char digit : generatedCardID) {
        ASSERT_TRUE(std::isdigit(digit));
    }
}

// Test case for removeSwipeCard function
TEST(SwipeCardTest, RemoveSwipeCardTest) {
    // Mocked userData for testing
    std::vector<std::string> userData = {
        "Name: John, Roles: Role1,Role2, Swipe Card ID: 12345",
        "Name: Alice, Roles: Student, Swipe Card ID: 54321",
    };

    // Create a SwipeCard object
    SwipeCard swipeCard("");

    // Case 1: Valid user index (userIndex = 1)
    int validUserIndex = 1;
    swipeCard.removeSwipeCard(validUserIndex, userData);
    // Validate if the swipe card is removed for the selected user
    EXPECT_EQ(userData[validUserIndex], "Name: Alice, Roles: Student, Swipe Card ID: ");

    // Case 2: Invalid user index (userIndex = -1)
    int invalidUserIndex = -1;
    testing::internal::CaptureStdout();
    swipeCard.removeSwipeCard(invalidUserIndex, userData);
    std::string output = testing::internal::GetCapturedStdout();
    // Validate if the error message for invalid user index is displayed
    EXPECT_EQ(output, "Invalid user index entered.\n");
}
