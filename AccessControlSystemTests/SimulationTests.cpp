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

TEST(SimulationTest, ExtractRolesTest) {
    Simulation simulation;
    std::vector<std::string> roles;
    std::string userToJoin = "Name: John Doe, Roles: Student, Staff, Swipe Card ID: 12345";
    simulation.extractRoles(userToJoin, roles);
    // Add your assertions here to validate the extracted roles vector
    ASSERT_EQ(roles.size(), 3);
    ASSERT_EQ(roles[0], "Student");
    ASSERT_EQ(roles[1], " Staff");
}

TEST(SimulationTest, ExtractRoomInfoValid) {
    Simulation simulation;
    std::string roomToJoin = "Room Type: Lecture Hall, Room State: Normal, Building State: Normal";
    std::string roomType, roomState;

    simulation.extractRoomInfo(roomToJoin, roomType, roomState);

    ASSERT_EQ(roomType, "Lecture Hall");
    ASSERT_EQ(roomState, "Normal");
}

TEST(SimulationTest, ExtractRoomInfoNoType) {
    Simulation simulation;
    std::string roomToJoin = "Room State: Normal, Building State: Normal";
    std::string roomType, roomState;

    simulation.extractRoomInfo(roomToJoin, roomType, roomState);

    ASSERT_EQ(roomType, ""); // Room type not found, expecting empty string
}

TEST(SimulationTest, ExtractRoomInfoNoState) {
    Simulation simulation;
    std::string roomToJoin = "Room Type: Lecture Hall, Building State: Normal";
    std::string roomType, roomState;

    simulation.extractRoomInfo(roomToJoin, roomType, roomState);
    ASSERT_EQ(roomState, ""); // Room state not found, expecting empty string
}

TEST(SimulationTest, ExtractRoomInfoNoTypeAndState) {
    Simulation simulation;
    std::string roomToJoin = "Building State: Normal";
    std::string roomType, roomState;

    simulation.extractRoomInfo(roomToJoin, roomType, roomState);

    ASSERT_EQ(roomType, ""); // Room type not found, expecting empty string
    ASSERT_EQ(roomState, ""); // Room state not found, expecting empty string
}

// Testing the generateLog function
TEST(SimulationTest, GenerateLogTest) {
    Simulation simulation;
    std::string userToJoin = "Name: John Doe, Roles: Student, Staff, Swipe Card ID: 12345";
    std::string roomToJoin = "Building Name: BuildingA, Room: Room1, Room Type: Lecture Hall, Room State: NORMAL";
    std::string roomState = "Normal";
    std::string formattedRoles = "Student, Staff";

    std::string expectedLog =
        "User: John Doe, Roles: Student, Staff, Swipe Card ID: 12345, Building Name: BuildingA, Room: Room1, Room Type: Lecture Hall, Room State: Normal";

    std::string generatedLog = simulation.generateLog(userToJoin, roomToJoin, roomState, formattedRoles);
    ASSERT_EQ(generatedLog, expectedLog);
}
