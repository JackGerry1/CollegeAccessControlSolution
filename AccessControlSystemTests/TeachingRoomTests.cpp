// TeachingRoomTests.cpp : This file contains the tests for the TeachingRoom class
// Include the paths to the required files in the AccessControlSystem project
#include "pch.h"
#include "../AccessControlSystem/TeachingRoom.h" 

/*
References:

GoogleTest (2023a) 'Advanced GoogleTest Topics', GoogleTest.
Available at: https://google.github.io/googletest/advanced.html [Accessed 15th December 2023].

GoogleTest (2023b) 'GoogleTest Primer', GoogleTest.
Available at: https://google.github.io/googletest/primer.html [Accessed 15th December 2023].

Tutorialspoint (2020) 'C++ Date and Time - Tutorialspoint', Tutorialspoint.
Available at: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm [Accessed 27th December 2023].

Haleem, A. (2020) 'Exploring Date and Time with Chrono', Medium.
Available at: https://ambreen2006.medium.com/exploring-date-and-time-with-chrono-3a8e9af60f62 [Accessed 27th December 2023].

*/

// Test: Security Role Grants Access to Teaching Room
TEST(TeachingRoomTest, SecurityRoleGrantsAccess) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Security", "NORMAL"));
}

// Test: Staff Member Access within Allowed Time in Teaching Room
TEST(TeachingRoomTest, StaffMemberAccessWithinAllowedTime) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Staff Member", "NORMAL"));
}

// Test: Student Access within Allowed Time in Teaching Room
TEST(TeachingRoomTest, StudentAccessWithinAllowedTime) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Student", "NORMAL"));
}

// Test: Contract Cleaner Access within Allowed Time in Teaching Room
TEST(TeachingRoomTest, ContractCleanerAccessWithinAllowedTime) {
    TeachingRoom room("", "", -1, "", -1);

    // Get current time and convert into hours and minutes to be compared later
    auto currentTime = std::chrono::system_clock::now();
    auto currentHour = std::chrono::time_point_cast<std::chrono::hours>(currentTime).time_since_epoch().count() % 24;
    auto currentMinute = std::chrono::time_point_cast<std::chrono::minutes>(currentTime).time_since_epoch().count() % 60;

    // Evaluate access based on time conditions for a Contract Cleaner in NORMAL mode (05:30 to 10:30 and 17:30 to 22:30)
    bool access = ((currentHour > 5 && currentHour < 10) || (currentHour == 5 && currentMinute >= 30) ||
        (currentHour > 17 && currentHour < 22) || (currentHour == 17 && currentMinute >= 30) ||
        (currentHour == 10 && currentMinute == 30) || (currentHour == 22 && currentMinute == 30));

    bool expectedAccess = room.verifyEntryRequirements("Contract Cleaner", "NORMAL");
    ASSERT_EQ(access, expectedAccess);
}

// Test: Manager Role Grants Access to Teaching Room
TEST(TeachingRoomTest, ManagerRoleGrantsAccess) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Manager", "NORMAL"));
}

// Test: Emergency Responder Access in Emergency Mode to Teaching Room
TEST(TeachingRoomTest, EmergencyResponderAccessInEmergencyMode) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Emergency Responder", "EMERGENCY"));
}

// Test: Deny Access when Roles Not Matched in Teaching Room
TEST(TeachingRoomTest, DenyAccessWhenRolesNotMatched) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_FALSE(room.verifyEntryRequirements("Invalid Role", "NORMAL"));
}
