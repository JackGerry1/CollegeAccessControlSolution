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

    auto currentTime = std::chrono::system_clock::now();
    auto currentHour = std::chrono::time_point_cast<std::chrono::hours>(currentTime).time_since_epoch().count() % 24;
    auto currentMinute = std::chrono::time_point_cast<std::chrono::minutes>(currentTime).time_since_epoch().count() % 60;

    bool access = ((currentHour > 5 && currentHour < 10) || (currentHour == 5 && currentMinute >= 30) ||
        (currentHour > 17 && currentHour < 22) || (currentHour == 17 && currentMinute >= 30) ||
        (currentHour == 10 && currentMinute == 30) || (currentHour == 22 && currentMinute == 30));

    bool expectedAccess = room.verifyEntryRequirements("Contract Cleaner", "NORMAL");
    ASSERT_EQ(access, expectedAccess);
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