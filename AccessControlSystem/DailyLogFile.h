// DailyLogFile.h: This file contains functions and attributes for the DailyLogFile class. 

#pragma once

#include <fstream>    
#include <iostream>  
#include <vector>     
#include <string>     
#include <sstream>    

class DailyLogFile {
private:
    // Function: getFormattedDate to generates and returns the formatted date as a string.
    static std::string getFormattedDate();

public:
    // Function: logRoomAccessAttempts to log room access attempts appending access information to a daily log file.
    static void logRoomAccessAttempts(const std::string& accessInfo);

    // Function: viewRoomAccessAttempts to display room access attempts stored in the daily log file.
    static void viewRoomAccessAttempts();
};
