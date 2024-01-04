// SimulationTests.cpp : This file contains the tests for the Simulation class
// Include the paths to the required files in the AccessControlSystem project

#include "pch.h"
#include "../AccessControlSystem/Simulation.h"  
#include "../AccessControlSystem/LectureHall.h"  
#include "../AccessControlSystem/TeachingRoom.h"  
#include "../AccessControlSystem/StaffRoom.h"  
#include "../AccessControlSystem/SecureRoom.h"  
#include "../AccessControlSystem/Simulation.cpp"  
#include "../AccessControlSystem/LectureHall.cpp"  
#include "../AccessControlSystem/TeachingRoom.cpp"  
#include "../AccessControlSystem/StaffRoom.cpp"  
#include "../AccessControlSystem/SecureRoom.cpp"  
#include "../AccessControlSystem/DailyLogFile.h"
#include "../AccessControlSystem/DailyLogFile.cpp"

/*
References:
GoogleTest (2023a) 'Advanced GoogleTest Topics', GoogleTest.
Available at: https://google.github.io/googletest/advanced.html [Accessed 15th December 2023].

GoogleTest (2023b) 'GoogleTest Primer', GoogleTest.
Available at: https://google.github.io/googletest/primer.html [Accessed 15th December 2023].
*/

// Test: Extract Roles from User Information
TEST(SimulationTest, ExtractRolesTest) {
    Simulation simulation;
    std::vector<std::string> roles;
    std::string userToJoin = "Name: John Doe, Roles: Student, Staff, Swipe Card ID: 12345";

    // Extract roles from the user information
    simulation.extractRoles(userToJoin, roles);

    // Assertions to validate the extracted roles vector
    ASSERT_EQ(roles.size(), 3);
    ASSERT_EQ(roles[0], "Student");
    ASSERT_EQ(roles[1], " Staff");
}

// Test: Extract Room Information with Valid Data
TEST(SimulationTest, ExtractRoomInfoValid) {
    Simulation simulation;
    std::string roomToJoin = "Room Type: Lecture Hall, Room State: Normal, Building State: Normal";
    std::string roomType, roomState;

    // Extract room type and state from room information
    simulation.extractRoomInfo(roomToJoin, roomType, roomState);

    // Validate the extracted room type and state
    ASSERT_EQ(roomType, "Lecture Hall");
    ASSERT_EQ(roomState, "Normal");
}

// Test: Extract Room Information with Missing Room Type
TEST(SimulationTest, ExtractRoomInfoNoType) {
    Simulation simulation;
    std::string roomToJoin = "Room State: Normal, Building State: Normal";
    std::string roomType, roomState;

    // Extract room type and state from room information
    simulation.extractRoomInfo(roomToJoin, roomType, roomState);

    // Validate the extracted room type (expecting an empty string as room type is missing)
    ASSERT_EQ(roomType, "");
}

// Test: Extract Room Information with Missing Room State
TEST(SimulationTest, ExtractRoomInfoNoState) {
    Simulation simulation;
    std::string roomToJoin = "Room Type: Lecture Hall, Building State: Normal";
    std::string roomType, roomState;

    // Extract room type and state from room information
    simulation.extractRoomInfo(roomToJoin, roomType, roomState);

    // Validate the extracted room state (expecting an empty string as room state is missing)
    ASSERT_EQ(roomState, "");
}

// Test: Generate Log with User and Room Information
TEST(SimulationTest, GenerateLogTest) {
    Simulation simulation;
    std::string userToJoin = "User: John Doe, Roles: Student, Staff Member, Swipe Card ID: 166657405, Building Name: ART, Room: KA412, Room Type: Teaching Room, Room State: NORMAL";
    std::string roomToJoin = "Building Name: ART, Room: KA412, Room Type: Teaching Room, Room State: NORMAL";
    std::string roomState = "NORMAL";
    std::string formattedRoles = "Student, Staff Member, ";

    std::string expectedLog =
        "User: ART, Room: KA412, Room Type: Teaching Room, Room State: NORMAL, Roles: Student, Staff Member, Swipe Card ID: 166657405, Building Name: ART, Room: KA412, Room Type: Teaching Room, Room State: NORMAL, Building Name: ART, Room: KA412, Room Type: Teaching Room, Room State: NORMAL";

    // Generate log based on user and room information
    std::string generatedLog = simulation.generateLog(userToJoin, roomToJoin, roomState, formattedRoles);

    // Validate the generated log
    ASSERT_EQ(generatedLog, expectedLog);
}
