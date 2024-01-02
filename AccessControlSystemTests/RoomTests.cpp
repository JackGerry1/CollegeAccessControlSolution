// RoomTets.cpp : This file contains the tests for the Room class
// Include the paths to the required files in the AccessControlSystem project

#include "pch.h"
#include "../AccessControlSystem/Room.h"

/*
References:
URL: https://google.github.io/googletest/primer.html Date Accessed: 15/12/23
URL: https://google.github.io/googletest/advanced.html Date Accessed: 15/12/23
*/

// Test fixture for the Room class
class RoomTest : public ::testing::Test {
protected:
    // Create an instance of the Room class for testing
    Room testRoom{ "BuildingCode", "BuildingName", 2, "Lecture Hall", 101 };
};

// Test the default entry requirements verification (should deny access by default)
TEST_F(RoomTest, VerifyDefaultEntryRequirements) {
    // Simulate user roles and room state
    std::string formattedRoles = "Student";
    std::string roomState = "NORMAL";

    bool accessGranted = testRoom.verifyEntryRequirements(formattedRoles, roomState);

    // Access should be denied by default
    EXPECT_FALSE(accessGranted);
}

// Test setting and retrieving floor number
TEST_F(RoomTest, SetAndGetFloorNumber) {
    testRoom.setFloorNumber(3);

    int floorNumber = testRoom.getFloorNumber();

    EXPECT_EQ(floorNumber, 3);
}

// Test setting and retrieving room type
TEST_F(RoomTest, SetAndGetRoomType) {
    testRoom.setRoomType("Conference Room");

    std::string roomType = testRoom.getRoomType();

    EXPECT_EQ(roomType, "Conference Room");
}

// Test setting and retrieving room number
TEST_F(RoomTest, SetAndGetRoomNumber) {
    testRoom.setRoomNumber(201);

    int roomNumber = testRoom.getRoomNumber();

    EXPECT_EQ(roomNumber, 201);
}

// Test setting and retrieving room state
TEST_F(RoomTest, SetAndGetRoomState) {
    testRoom.setRoomState(RoomState::ROOM_EMERGENCY);

    RoomState roomState = testRoom.getRoomState();

    EXPECT_EQ(roomState, RoomState::ROOM_EMERGENCY);
}

// Test case for roomStateToString function
TEST_F(RoomTest, RoomStateToString) {
    // Test for ROOM_NORMAL state
    RoomState normalState = RoomState::ROOM_NORMAL;
    std::string normalString = Room::roomStateToString(normalState);
    EXPECT_EQ(normalString, "NORMAL");

    // Test for ROOM_EMERGENCY state
    RoomState emergencyState = RoomState::ROOM_EMERGENCY;
    std::string emergencyString = Room::roomStateToString(emergencyState);
    EXPECT_EQ(emergencyString, "EMERGENCY");

    // Test for UNKNOWN_ROOM_STATE state (invalid state)
    RoomState unknownState = static_cast<RoomState>(99); // Invalid state
    std::string unknownString = Room::roomStateToString(unknownState);
    EXPECT_EQ(unknownString, "UNKNOWN_ROOM_STATE");
}
