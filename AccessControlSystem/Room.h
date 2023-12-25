#pragma once
#include <string>
#include "Building.h"

enum class RoomState {
    ROOM_NORMAL,
    ROOM_EMERGENCY
};

class Room : public Building {
private:
    int floorNumber;
    std::string roomType;
    int roomNumber;
    RoomState roomState;

public:
    Room(std::string buildingCode, std::string buildingName, int floorNumber, std::string roomType, int roomNumber);
    ~Room();

    bool verifyEntryRequirements();
    static std::string roomStateToString(RoomState state);
    // Getters and setters
    void setFloorNumber(int floorNumber);
    int getFloorNumber() const;

    void setRoomType(const std::string& roomType);
    std::string getRoomType() const;

    void setRoomNumber(int roomNumber);
    int getRoomNumber() const;

    void setRoomState(RoomState roomState);
    RoomState getRoomState() const;
};

