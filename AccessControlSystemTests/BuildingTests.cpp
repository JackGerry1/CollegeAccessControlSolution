// BuildingTests.cpp : This file contains the tests for the Building class
// Include the paths to the required files in the AccessControlSystem project

#include "pch.h"
#include "../AccessControlSystem/Building.cpp"
#include "../AccessControlSystem/Room.cpp"
#include "../AccessControlSystem/BuildingStructureLog.cpp"

/*
References:
URL: https://google.github.io/googletest/primer.html Date Accessed: 15/12/23
URL: https://google.github.io/googletest/advanced.html Date Accessed: 15/12/23
*/

// Test cases for setBuildingCode and getBuildingCode functions
TEST(BuildingTest, SetAndGetBuildingCode) {
    Building building("", "");
    const std::string testBuildingCode = "ABC123";

    building.setBuildingCode(testBuildingCode);
    EXPECT_EQ(building.getBuildingCode(), testBuildingCode);
}

// Test cases for setBuildingName and getBuildingName functions
TEST(BuildingTest, SetAndGetBuildingName) {
    Building building("", "");
    const std::string testBuildingName = "Example Building";

    building.setBuildingName(testBuildingName);
    EXPECT_EQ(building.getBuildingName(), testBuildingName);
}

// Test case to check if BUILDING_NORMAL is correctly converted to "NORMAL"
TEST(BuildingTest, BuildingStateToString_Normal) {
    Building building("", "");
    std::string result = building.buildingStateToString(BuildingState::BUILDING_NORMAL);
    EXPECT_EQ(result, "NORMAL");
}

// Test case to check if BUILDING_EMERGENCY is correctly converted to "EMERGENCY"
TEST(BuildingTest, BuildingStateToString_Emergency) {
    Building building("", "");
    std::string result = building.buildingStateToString(BuildingState::BUILDING_EMERGENCY);
    EXPECT_EQ(result, "EMERGENCY");
}

// Test case to check if an unknown state is handled correctly
TEST(BuildingTest, BuildingStateToString_UnknownState) {
    Building building("", "");
    std::string result = building.buildingStateToString(static_cast<BuildingState>(5)); // Using an arbitrary unknown state
    EXPECT_EQ(result, "UNKNOWN_BUILDING_STATE");
}

// Test case for removeRoom function
TEST(BuildingTest, RemoveRoom) {
    // Mocked roomData for testing
    std::vector<std::string> roomData = {
        "Building Name: A, Room: 101, Room Type: Lecture, Room State: Normal, Building State: Normal",
        "Building Name: B, Room: 201, Room Type: Office, Room State: Normal, Building State: Emergency"
    };

    // Mocked input for the index to remove
    int index = 1; // Assuming room index 1 is selected for removal

    // Simulate the behavior of removing a room based on the provided index
    if (!roomData.empty() && index >= 0 && index < static_cast<int>(roomData.size())) {
        roomData.erase(roomData.begin() + index);

        // Validate the expected roomData after removal
        std::vector<std::string> expectedRoomData = {
            "Building Name: A, Room: 101, Room Type: Lecture, Room State: Normal, Building State: Normal"
        };

        ASSERT_EQ(roomData, expectedRoomData);
    }
    else {
        std::cout << "Invalid room index or no rooms found.\n";
    }
}

// Test case for changeRoomAndBuildingState function
TEST(BuildingTest, ChangeRoomAndBuildingState) {
    // Prepare mock room data for testing
    std::vector<std::string> roomData = {
        "Building Name: BuildingA, Room: Room1, Room State: NORMAL, Building State: NORMAL",
        "Building Name: BuildingA, Room: Room2, Room State: NORMAL, Building State: NORMAL",
        "Building Name: BuildingB, Room: Room3, Room State: NORMAL, Building State: NORMAL",
    };

    // Mock user input
    std::istringstream mockInput("1\n"); // Assume selecting Room2 (index 1)

    // Mock cout for capturing output
    std::ostringstream mockOutput;

    // Redirecting cin and cout for testing
    std::streambuf* originalInput = std::cin.rdbuf(mockInput.rdbuf());
    std::streambuf* originalOutput = std::cout.rdbuf(mockOutput.rdbuf());

    // Execute the changeRoomAndBuildingState function
    Building buildingUnderTest("", "");
    buildingUnderTest.changeRoomAndBuildingState();

    // Restore cin and cout to original states
    std::cin.rdbuf(originalInput);
    std::cout.rdbuf(originalOutput);

    // Assertions to validate the expected changes in roomData and Building Structure Log
    ASSERT_EQ(roomData[0].find("Room State: EMERGENCY"), std::string::npos);
    ASSERT_EQ(roomData[1].find("Room State: EMERGENCY"), std::string::npos);
    ASSERT_EQ(roomData[2].find("Room State: EMERGENCY"), std::string::npos);
}

// Test case for updateRoom function
TEST(BuildingTest, UpdateRoom) {
    // Prepare mock room data for testing
    std::vector<std::string> roomData = {
        "Building Name: BuildingA, Room: Room1, Room Type: Lecture Hall, Room State: NORMAL, Building State: NORMAL",
        "Building Name: BuildingA, Room: Room2, Room Type: Teaching Room, Room State: NORMAL, Building State: NORMAL",
        "Building Name: BuildingB, Room: Room3, Room Type: Staff Room, Room State: NORMAL, Building State: NORMAL",
    };

    // Prepare mock user input
    std::istringstream mockInput("1\nno\nno\n"); // Assume selecting Room2 (index 1), and choosing not to update room number and room type

    // Mock cout for capturing output
    std::ostringstream mockOutput;

    // Redirecting cin and cout for testing
    std::streambuf* originalInput = std::cin.rdbuf(mockInput.rdbuf());
    std::streambuf* originalOutput = std::cout.rdbuf(mockOutput.rdbuf());

    // Execute the updateRoom function
     Building buildingUnderTest("", "");
    buildingUnderTest.updateRoom();

    // Restore cin and cout to original states
    std::cin.rdbuf(originalInput);
    std::cout.rdbuf(originalOutput);

    // result if not updating any information
    ASSERT_EQ(roomData[1], "Building Name: BuildingA, Room: Room2, Room Type: Teaching Room, Room State: NORMAL, Building State: NORMAL");
}