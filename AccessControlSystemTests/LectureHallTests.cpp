// LectureHallTests.cpp : This file contains the tests for the LectureHall class
// Include the paths to the required files in the AccessControlSystem project

#include "pch.h"
#include "../AccessControlSystem/LectureHall.h" 

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

// Test: Security Role Access
TEST(LectureHallAccessTest, SecurityRoleAccess) {
    // Create a LectureHall instance
    LectureHall lectureHall("", "", -1, "", -1);

    // Check access for a Security role in NORMAL mode
    bool access = lectureHall.verifyEntryRequirements("Security", "NORMAL");
    ASSERT_TRUE(access); // Expects the access to be true
}

// Test: Staff Member Role Allowed Hours
TEST(LectureHallAccessTest, StaffMemberRoleAllowedHours) {
    // Create a LectureHall instance
    LectureHall lectureHall("", "", -1, "", -1);

    // Check access for a Staff Member role in NORMAL mode
    bool access = lectureHall.verifyEntryRequirements("Staff Member", "NORMAL");
    ASSERT_TRUE(access); // Expects the access to be true
}

// Test: Student Role Allowed Hours
TEST(LectureHallAccessTest, StudentRoleAllowedHours) {
    // Create a LectureHall instance
    LectureHall lectureHall("", "", -1, "", -1);

    // Check access for a Student role in NORMAL mode
    bool access = lectureHall.verifyEntryRequirements("Student", "NORMAL");
    ASSERT_TRUE(access); // Expects the access to be true
}

// Test: Contract Cleaner Role Allowed Hours
TEST(LectureHallAccessTest, ContractCleanerRoleAllowedHours) {
    // Create a LectureHall instance
    LectureHall lectureHall("", "", -1, "", -1);

    // Get the current time for evaluation
    auto currentTime = std::chrono::system_clock::now();
    auto currentHour = std::chrono::time_point_cast<std::chrono::hours>(currentTime).time_since_epoch().count() % 24;
    auto currentMinute = std::chrono::time_point_cast<std::chrono::minutes>(currentTime).time_since_epoch().count() % 60;

    // Evaluate access based on time conditions for a Contract Cleaner in NORMAL mode (05:30 to 10:30 and 17:30 to 22:30)
    bool access = ((currentHour > 5 && currentHour < 10) || (currentHour == 5 && currentMinute >= 30) ||
        (currentHour > 17 && currentHour < 22) || (currentHour == 17 && currentMinute >= 30) ||
        (currentHour == 10 && currentMinute == 30) || (currentHour == 22 && currentMinute == 30));

    bool expectedAccess = lectureHall.verifyEntryRequirements("Contract Cleaner", "NORMAL");
    ASSERT_EQ(access, expectedAccess); // Compares calculated access with expected result
}

// Test: Manager Role Any Time
TEST(LectureHallAccessTest, ManagerRoleAnyTime) {
    // Create a LectureHall instance
    LectureHall lectureHall("", "", -1, "", -1);

    // Check access for a Manager role in NORMAL mode
    bool access = lectureHall.verifyEntryRequirements("Manager", "NORMAL");
    ASSERT_TRUE(access); // Expects the access to be true
}

// Test: Emergency Responder Denied Access in Normal Mode
TEST(LectureHallAccessTest, EmergencyResponderDeniedAccess) {
    // Create a LectureHall instance
    LectureHall lectureHall("", "", -1, "", -1);

    // Check access for an Emergency Responder role in NORMAL mode
    bool access = lectureHall.verifyEntryRequirements("Emergency Responder", "NORMAL");
    ASSERT_FALSE(access); // Expects the access to be false
}

// Test: Emergency Responder Access in Emergency Mode
TEST(LectureHallAccessTest, EmergencyResponderAccess) {
    // Create a LectureHall instance
    LectureHall lectureHall("", "", -1, "", -1);

    // Check access for an Emergency Responder role in EMERGENCY mode
    bool access = lectureHall.verifyEntryRequirements("Emergency Responder", "EMERGENCY");
    ASSERT_TRUE(access); // Expects the access to be true
}
