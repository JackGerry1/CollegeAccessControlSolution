#include "SwipeCard.h"
#include <sstream> // For stringstream
#include <cstdlib>

/* References:
    URL: https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus Date Accessed: 13/10/23

*/

//TODO: create a get cardID function to get the value outside this class?
// also update the .h file to include this new function 

SwipeCard::SwipeCard(std::string cardID)
    : cardID(cardID) {}

std::string SwipeCard::addSwipeCard() {
    std::stringstream ss;

    // Providing a seed value to make sure rand() is different every time program is run. 
    srand((unsigned)time(NULL));

    // Generating a random card ID
    for (int i = 0; i < 9; i++) {
        ss << rand() % 10;
    }

    cardID = ss.str();
    return cardID;
}

void SwipeCard::removeSwipeCard() {
    // Implement removal of a swipe card
}

void SwipeCard::updateSwipeCard() {
    // Implement updating of swipe card details
}