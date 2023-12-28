#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class DailyLogFile
{
private:
    static std::string getFormattedDate();
    
public:
    static void logRoomAccessAttempts(const std::string& accessInfo);
    static void viewRoomAccessAttempts();
};

