//SwipeCard.h: This file contains functions and attributes for the swipe class. 

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
    std::string cardID;

// public functions and constructor for the SwipeCard class
public:
    SwipeCard(std::string cardID);

    std::string addSwipeCard();
    void removeSwipeCard(int userIndex, std::vector<std::string>& userData);
    void updateSwipeCard();
};

