//SwipeCard.cpp : This file contains functions and attributes specifeid in the SwipeCard.h file. 

#include "SwipeCard.h"

/* References:
    URL: https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus Date Accessed: 13/10/23
*/

//TODO: create a get cardID function to get the value outside this class?
// also update the .h file to include this new function 

// Constructor initializing with the cardID for the SwipeCard
SwipeCard::SwipeCard(std::string cardID)
    : cardID(cardID) {} 

// function to add a swipe card
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
}

// function to remove a swipe card
void SwipeCard::removeSwipeCard() {
    // Implement removal of a swipe card
}

// function ot update a swipe card
void SwipeCard::updateSwipeCard() {
    // Implement updating of swipe card details
}