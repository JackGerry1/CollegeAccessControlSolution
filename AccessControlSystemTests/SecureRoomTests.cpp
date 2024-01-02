// SecureRoomTests.cpp : This file contains the tests for the SecureRoom class
// Include the paths to the required files in the AccessControlSystem project

#include "pch.h"
#include "../AccessControlSystem/SecureRoom.h" 

/*
References:
URL: https://google.github.io/googletest/primer.html Date Accessed: 15/12/23
URL: https://google.github.io/googletest/advanced.html Date Accessed: 15/12/23
*/

// Test: Security Role Grants Access
TEST(SecureRoomTest, SecurityRoleGrantsAccess) {
    // Create a SecureRoom instance
    SecureRoom room("", "", -1, "", -1);

    // Validate if Security role grants access in NORMAL state
    ASSERT_TRUE(room.verifyEntryRequirements("Security", "NORMAL"));
}

// Test: Manager Role Grants Access in Normal State
TEST(SecureRoomTest, ManagerRoleGrantsAccessInNormalState) {
    // Create a SecureRoom instance
    SecureRoom room("", "", -1, "", -1);

    // Validate if Manager role grants access in NORMAL state
    ASSERT_TRUE(room.verifyEntryRequirements("Manager", "NORMAL"));
}

// Test: Emergency Responder Access in Emergency Mode
TEST(SecureRoomTest, EmergencyResponderAccessInEmergencyMode) {
    // Create a SecureRoom instance
    SecureRoom room("", "", -1, "", -1);

    // Validate if Emergency Responder role grants access in EMERGENCY mode
    ASSERT_TRUE(room.verifyEntryRequirements("Emergency Responder", "EMERGENCY"));
}

// Test: Deny Access When Roles Not Matched in Normal State
TEST(SecureRoomTest, DenyAccessWhenRolesNotMatchedNormalState) {
    // Create a SecureRoom instance
    SecureRoom room("", "", -1, "", -1);

    // Validate if access is denied when an invalid role is provided in NORMAL state
    ASSERT_FALSE(room.verifyEntryRequirements("Invalid Role", "NORMAL"));
}

// Test: Deny Access When Roles Not Matched in Emergency State
TEST(SecureRoomTest, DenyAccessWhenRolesNotMatchedEmergencyState) {
    // Create a SecureRoom instance
    SecureRoom room("", "", -1, "", -1);

    // Validate if access is denied when an invalid role is provided in EMERGENCY state
    ASSERT_FALSE(room.verifyEntryRequirements("Invalid Role", "EMERGENCY"));
}
