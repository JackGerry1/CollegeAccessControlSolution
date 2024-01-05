// SecureRoom.cpp : This file contains functions and attributes specifeid in the SecureRoomHall.h file. 
#include "SecureRoom.h"

// Function: verifyEntryRequirements
// Parameters: const std::string& formattedRoles - formatted user roles const std::string& roomState - state of the room
// Objective: Determines if access is granted based on user roles and room state.
bool SecureRoom::verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState)
{
    // Deny access by default
    bool accessGranted = false;

    // Check for Security role - grants access at any time, regardless of mode
    if (formattedRoles.find("Security") != std::string::npos) {
        accessGranted = true;
    }

    // Check the room state first
    if (roomState == "NORMAL" && formattedRoles.find("Manager") != std::string::npos) {
        // Grant access to Manager only in NORMAL mode
        accessGranted = true;
    }
    // Emergency Access State
    else {
        // Grant access to Emergency Responder only in emergency mode
        if (formattedRoles.find("Emergency Responder") != std::string::npos) {
            accessGranted = true;
        }
    }

    return accessGranted;
} // end of verifyEntryRequirements
