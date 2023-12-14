#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "SwipeCard.h"

class User {
private:
    std::string forename;
    std::string surname;
    std::string role;
    int userID;
    SwipeCard swipeCard; // Composite relationship with SwipeCard

public:
    User(std::string forename, std::string surname, std::string role, int userID);

    void addUser();
    void removeUser();
    void updateUser();
    std::string addRole();
    void removeRole(std::string removedRole);
    static void displayUsersAlphabetically();
    int getUserID();
    std::string getForename() const;
    std::string getSurname() const;
    std::string getFullName() const;
    std::string getRole() const;
};

#endif // USER_H
