#include "pch.h"

#include "../AccessControlSystem/LectureHall.h" 

// Test access for Security role
TEST(LectureHallAccessTest, SecurityRoleAccess) {
    LectureHall lectureHall("", "", -1, "", -1);
    bool access = lectureHall.verifyEntryRequirements("Security", "NORMAL");
    ASSERT_TRUE(access);
}

// Test access for Staff Member during allowed hours
TEST(LectureHallAccessTest, StaffMemberRoleAllowedHours) {
    LectureHall lectureHall("", "", -1, "", -1);
    bool access = lectureHall.verifyEntryRequirements("Staff Member", "NORMAL");
    ASSERT_TRUE(access);
}

// Test access for Student during allowed hours
TEST(LectureHallAccessTest, StudentRoleAllowedHours) {
    LectureHall lectureHall("", "", -1, "", -1);
    bool access = lectureHall.verifyEntryRequirements("Student", "NORMAL");
    ASSERT_TRUE(access);
}

// Test access for Contract Cleaner during allowed hours
TEST(LectureHallAccessTest, ContractCleanerRoleAllowedHours) {
    LectureHall lectureHall("", "", -1, "", -1);

    auto currentTime = std::chrono::system_clock::now();
    auto currentHour = std::chrono::time_point_cast<std::chrono::hours>(currentTime).time_since_epoch().count() % 24;
    auto currentMinute = std::chrono::time_point_cast<std::chrono::minutes>(currentTime).time_since_epoch().count() % 60;

    bool access = ((currentHour > 5 && currentHour < 10) || (currentHour == 5 && currentMinute >= 30) ||
        (currentHour > 17 && currentHour < 22) || (currentHour == 17 && currentMinute >= 30) ||
        (currentHour == 10 && currentMinute == 30) || (currentHour == 22 && currentMinute == 30));

    bool expectedAccess = lectureHall.verifyEntryRequirements("Contract Cleaner", "NORMAL");
    ASSERT_EQ(access, expectedAccess);
}

// Test access for Manager at any time
TEST(LectureHallAccessTest, ManagerRoleAnyTime) {
    LectureHall lectureHall("", "", -1, "", -1);
    bool access = lectureHall.verifyEntryRequirements("Manager", "NORMAL");
    ASSERT_TRUE(access);
}

// Test emergency responder access in emergency mode
TEST(LectureHallAccessTest, EmergencyResponderDeniedAccess) {
    LectureHall lectureHall("", "", -1, "", -1);
    bool access = lectureHall.verifyEntryRequirements("Emergency Responder", "NORMAL");
    ASSERT_FALSE(access); // Since default state is denied
    // You might adjust this test based on your expected behavior for emergency mode access
}

// Test emergency responder access in emergency mode
TEST(LectureHallAccessTest, EmergencyResponderAccess) {
    LectureHall lectureHall("", "", -1, "", -1);
    bool access = lectureHall.verifyEntryRequirements("Emergency Responder", "EMERGENCY");
    ASSERT_TRUE(access); 
}