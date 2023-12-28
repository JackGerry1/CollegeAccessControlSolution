#include "SecureRoom.h"

bool SecureRoom::verifyEntryRequirements(const std::string& formattedRoles, const std::string& roomState)
{
	// Deny access by default
	bool accessGranted = false;

	// Security: Access at any time, regardless of mode
	if (formattedRoles.find("Security") != std::string::npos) {
		accessGranted = true;
	}

	// Check the room state first
	if (roomState == "NORMAL" && formattedRoles.find("Manager") != std::string::npos) {
		accessGranted = true;
	}
	else {
		// Emergency mode access
		if (formattedRoles.find("Emergency Responder") != std::string::npos) {
			// Emergency Responder: Access only in emergency mode
			accessGranted = true;
		}

	}

	return accessGranted;
}
