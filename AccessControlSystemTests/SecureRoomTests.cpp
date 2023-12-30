#include "pch.h"

#include "../AccessControlSystem/SecureRoom.h" 

/*
References:
URL: https://google.github.io/googletest/primer.html Date Accessed: 15/12/23
URL: https://google.github.io/googletest/advanced.html Date Accessed: 15/12/23
*/

TEST(SecureRoomTest, SecurityRoleGrantsAccess) {
    SecureRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Security", "NORMAL"));
}

TEST(SecureRoomTest, ManagerRoleGrantsAccessInNormalState) {
    SecureRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Manager", "NORMAL"));
}

TEST(SecureRoomTest, EmergencyResponderAccessInEmergencyMode) {
    SecureRoom room("", "", -1, "", -1);
    ASSERT_TRUE(room.verifyEntryRequirements("Emergency Responder", "EMERGENCY"));
}

TEST(SecureRoomTest, DenyAccessWhenRolesNotMatchedNormalState) {
    SecureRoom room("", "", -1, "", -1);
    ASSERT_FALSE(room.verifyEntryRequirements("Invalid Role", "NORMAL"));
}

TEST(SecureRoomTest, DenyAccessWhenRolesNotMatchedEmergencyState) {
    SecureRoom room("", "", -1, "", -1);
    ASSERT_FALSE(room.verifyEntryRequirements("Invalid Role", "EMERGENCY"));
}