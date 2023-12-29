#include "pch.h"

#include "../AccessControlSystem/StaffRoom.h" 

TEST(StaffRoomTest, SecurityRoleGrantsAccess) {
    StaffRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Security", "NORMAL"));
}

TEST(StaffRoomTest, StaffMemberAccessWithinAllowedTime) {
    StaffRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Staff Member", "NORMAL"));
}

TEST(StaffRoomTest, ContractCleanerAccessWithinAllowedTime) {
    StaffRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Contract Cleaner", "NORMAL"));
}

TEST(StaffRoomTest, ManagerRoleGrantsAccess) {
    StaffRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Manager", "NORMAL"));
}

TEST(StaffRoomTest, EmergencyResponderAccessInEmergencyMode) {
    StaffRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Emergency Responder", "EMERGENCY"));
}

TEST(StaffRoomTest, DenyAccessWhenRolesNotMatched) {
    StaffRoom room("", "", -1, "", -1);
    ASSERT_FALSE(room.verifyEntryRequirements("Invalid Role", "NORMAL"));
}