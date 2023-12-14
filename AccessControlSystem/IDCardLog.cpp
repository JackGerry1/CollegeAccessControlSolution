#include "IDCardLog.h"

void IDCardLog::logUserData(const std::string& userInfo) {
    std::ofstream outputFile("LogFiles/ID_Card_List.txt", std::ios::app); // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile << userInfo; // Write the user info to the file
        outputFile.close();
    }
    else {
        std::cerr << "Unable to open file\n";
    }
}
