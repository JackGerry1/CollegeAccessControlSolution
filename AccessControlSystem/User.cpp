#include "User.h"
#include <iomanip>
#include <vector>
#include <algorithm>

User::User(std::string forename, std::string surname, std::string role, int userID)
	: forename(forename), surname(surname), role(role), userID(1), swipeCard("") {}

int User::getUserID() {
	return userID++;
}

std::string User::getForename() const {
	return forename;
}

std::string User::getSurname() const {
	return surname;
}

std::string User::getFullName() const {
	return forename + " " + surname;
}

void User::addUser() {
	std::string newForename, newSurname, newRole;
	std::cout << "Enter forename: ";
	std::cin >> newForename;

	std::cout << "Enter surname: ";
	std::cin >> newSurname;

	forename = newForename;
	surname = newSurname;

	role = addRole();
	SwipeCard newSwipeCard("");
	swipeCard = newSwipeCard; // Assigning a new swipe card when adding a user

	system("cls");
	std::cout << "Added New User: Name: " << getFullName() << ", Role: " << role << ", Swipe Card ID: " << swipeCard.addSwipeCard() << ", User ID: " << getUserID() << "\n\n";
}

void User::removeUser() {
	// Implementation to remove a user from a database or collection
}

void User::updateUser() {
	// Implementation to update user information
}

std::string User::addRole() {
	int choice;
	std::cout << "Enter a role:\n";
	std::cout << "1. Staff Member\n";
	std::cout << "2. Student\n";
	std::cout << "3. Visitor / Guest\n";
	std::cout << "4. Contract Cleaner\n";
	std::cout << "5. Manager\n";
	std::cout << "6. Security\n";
	std::cout << "7. Emergency Responder\n";

	do {
		std::cout << "Enter your choice (1-7): ";
		std::cin >> choice;
	} while (choice < 1 || choice > 7);

	switch (choice) {
	case 1:
		return "Staff Member";
	case 2:
		return "Student";
	case 3:
		return "Visitor / Guest";
	case 4:
		return "Contract Cleaner";
	case 5:
		return "Manager";
	case 6:
		return "Security";
	case 7:
		return "Emergency Responder";
	default:
		return "";
	}

}


void User::removeRole(std::string removedRole) {
	// Implementation to remove a role from a user
}

bool User::compareByFullName(const User& a, const User& b) {
	return a.getFullName() < b.getFullName();
}

void User::displayUsersAlphabetically(std::vector<User>& users) {
	std::sort(users.begin(), users.end(), compareByFullName);

	std::cout << "\nALPHABETICAL LIST OF USERS" << std::endl;
	for (const auto& user : users) {
		std::cout << "Name: " << user.getFullName() << std::endl;
	}
}
