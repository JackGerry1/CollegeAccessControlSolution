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
    bool access = lectureHall.verifyEntryRequirements("Contract Cleaner", "NORMAL");
    ASSERT_TRUE(access);
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