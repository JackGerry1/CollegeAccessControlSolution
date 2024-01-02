//SwipeCard.h: This file contains functions and attributes for the SwipeCard class. 

#pragma once

// include the libraries for the SwipeCard.cpp file
#include <string>
#include "IDCardLog.h"
#include <iostream>
#include <vector>
#include <sstream> 
#include <cstdlib>

// create class with priveate attribute for cardID
class SwipeCard {
private:
    // cardId variable declaratioj
    std::string cardID;

// public functions and constructor for the SwipeCard class
public:
    // basic constructor only needing a cardID
    SwipeCard(std::string cardID);

    // Function to add a swipe card
    std::string addSwipeCard();

    // Function to remove a swipe card from a specific user index from the vector of strings containing the user data
    void removeSwipeCard(int userIndex, std::vector<std::string>& userData);
};

