//SwipeCard.cpp : This file contains functions and attributes specifeid in the SwipeCard.h file. 

#include "SwipeCard.h"

/* References:
    Gangwar, M. (2023) 'How to Create a Random Number Generator in C++', DigitalOcean. 
    Available at: https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus [Accessed 13th December 2023].
    
    Cplusplus.com (2023) 'std::vector::erase', Cplusplus.com. 
    Available at: https://cplusplus.com/reference/vector/vector/erase/ [Accessed 18th December 2023].

    Sinha, A. (2022). string::npos in C++. [Online] CodeSpeedy.
    Available at: https://www.codespeedy.com/stringnpos-in-cpp/ [Accessed 18th December 2023].
*/

// Constructor initializing with the cardID for the SwipeCard
SwipeCard::SwipeCard(std::string cardID)
    : cardID(cardID) {} 

// Function: addSwipeCard
// Objective: to add a swipe card
std::string SwipeCard::addSwipeCard() {
    // Initialize a stringstream for creating the card ID
    std::stringstream ss;
    
    // Seed the random number generator
    srand((unsigned)time(NULL)); 

    // Generating a random card ID with 9 digits from 0 to 9
    for (int i = 0; i < 9; i++) {
        ss << rand() % 10; 
    }
    
    // Assign and return the generated card ID to the cardID variable
    cardID = ss.str(); 
    return cardID; 
} // end of addSwipeCard

// Function: removeSwipeCard
// Paramaters: Index of user that is having swipe card removed, and the vector of data from the IDCardLogFile
// Objective: to remove a swipe card
void SwipeCard::removeSwipeCard(int userIndex, std::vector<std::string>& userData) {
    // Check if the userIndex is within the bounds of the userData vector
    if (userIndex >= 0 && userIndex < userData.size()) {
        // Get the user's line from the vector
        std::string& userLine = userData[userIndex];

        // Find the position of the "Swipe Card ID:" within the user's line
        size_t swipeCardPos = userLine.find("Swipe Card ID:");

        // If "Swipe Card ID:" is found in the user's line
        if (swipeCardPos != std::string::npos) {
            // Erase the swipe card ID from the user's line
            // The erase function removes characters starting from swipeCardPos + 15 (where the start of the cardID is) to the end of the string
            userLine.erase(swipeCardPos + 15, userLine.size() - (swipeCardPos + 15));
        }

        // Update the user data file with the modified userData vector
        IDCardLog::updateUserDataFile(userData);

        // Display a message confirming the removal of the swipe card for the selected user
        std::cout << "Swipe card removed for the selected user.\n";
    }
    else {
        // Display an error message for an invalid user index
        std::cout << "Invalid user index entered.\n";
    }
} // end of removeSwipeCard