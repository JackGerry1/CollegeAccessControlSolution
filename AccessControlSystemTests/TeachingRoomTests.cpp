#include "pch.h"

#include "../AccessControlSystem/TeachingRoom.h" 

TEST(TeachingRoomTest, SecurityRoleGrantsAccess) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Security", "NORMAL"));
}

TEST(TeachingRoomTest, StaffMemberAccessWithinAllowedTime) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Staff Member", "NORMAL"));
}

TEST(TeachingRoomTest, StudentAccessWithinAllowedTime) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Student", "NORMAL"));
}

TEST(TeachingRoomTest, ContractCleanerAccessWithinAllowedTime) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Contract Cleaner", "NORMAL"));
}

TEST(TeachingRoomTest, ManagerRoleGrantsAccess) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Manager", "NORMAL"));
}

TEST(TeachingRoomTest, EmergencyResponderAccessInEmergencyMode) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Emergency Responder", "EMERGENCY"));
}

TEST(TeachingRoomTest, DenyAccessWhenRolesNotMatched) {
    TeachingRoom room("", "", -1, "", -1);
    ASSERT_FALSE(room.verifyEntryRequirements("Invalid Role", "NORMAL"));
}
