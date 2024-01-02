// Simulation.h: This file defines functions and attributes for the Simulation class.

#pragma once
#include "User.h" // Assuming User class is included
#include "Room.h" // Assuming Room class is included
#include "LectureHall.h"
#include "TeachingRoom.h"
#include "StaffRoom.h"
#include "SecureRoom.h"
#include "DailyLogFile.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

class Simulation {
public:
    // Start the simulation
    void startSimulation();

    // Extracts roles from a user to join
    void extractRoles(const std::string& userToJoin, std::vector<std::string>& roles);

    // Extracts room information such as type and state
    void extractRoomInfo(const std::string& roomToJoin, std::string& roomType, std::string& roomState);

    // Verifies whether a user has access to a specific room based on role, type, and state
    bool verifyRoomAccess(const std::string& roomType, const std::string& formattedRoles, const std::string& roomState, const std::string& log);

    // Allows a user to join a room
    void joinRoom(const std::string& userToJoin);

    // Handles the process when a user leaves a room
    void leaveRoom(const std::string& log);

    // Generates a log message based on user, room, and access information
    std::string generateLog(const std::string& userToJoin, const std::string& roomToJoin, const std::string& roomState, const std::string& formattedRoles);

    // Stop the simulation
    void stopSimulation();

    // Retrieves the current date and time in a formatted string
    std::string getDateAndTime();
};

