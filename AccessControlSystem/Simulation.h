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

    void extractRoles(const std::string& userToJoin, std::vector<std::string>& roles);

    void extractRoomInfo(const std::string& roomToJoin, std::string& roomType, std::string& roomState);

    bool verifyRoomAccess(const std::string& roomType, const std::string& formattedRoles, const std::string& roomState, const std::string& log);

    // Attempt for a user to join a room, return true if successful
    void joinRoom(const std::string& userToJoin);

    void leaveRoom(const std::string& log);

    std::string generateLog(const std::string& userToJoin, const std::string& roomToJoin, const std::string& roomState, const std::string& formattedRoles);

    // Stop the simulation
    void stopSimulation();
    std::string getDateAndTime();
};
