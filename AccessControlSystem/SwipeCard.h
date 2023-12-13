#ifndef SWIPECARD_H
#define SWIPECARD_H

#include <string>

class SwipeCard {
private:
    std::string cardID;

public:
    SwipeCard(std::string cardID);

    std::string addSwipeCard();
    void removeSwipeCard();
    void updateSwipeCard();
};

#endif // SWIPECARD_H