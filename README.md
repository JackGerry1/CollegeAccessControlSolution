# College Access Control Solution
This C++ console application efficiently manages rooms, users, and swipe cards within a college environment. It facilitates user and role management, room and building administration, access logs, and user simulation for testing via an intuitive menu system.

## Installation Instructions

### Prerequisites
- **Git**: Install Git for version control.
- **Visual Studio**: Install Visual Studio IDE for C++ development.

### Steps
1. **Clone Repository**: Open Git Bash or your command line and run:
    ```bash
    git clone https://github.com/JackGerry1/CollegeAccessControlSolution.git
    ```

2. **Open Project in Visual Studio**:
    - Launch Visual Studio.
    - Go to `File > Open > Project/Solution`.
    - Navigate to the cloned repository folder and select the appropriate solution file.

3. **Build and Compile**:
    - Set up the build configuration (Debug/Release).
    - Press `Ctrl + Shift + B` or navigate to `Build > Build Solution` to compile the project.

4. **Run the Program**:
    - Set the startup project if needed.
    - Press `F5` or go to `Debug > Start Debugging` to run the program.

5. **Deploying the Program**:
    - If needed, create an installer or package as per deployment requirements.


## Key Features

- **User & Role Management**: Admins can add, remove, and update users and their unique swipe cards, along with assigning or removing roles.
- **Room & Building Administration**: Add, remove, and update buildings and rooms, altering room states between "NORMAL" and "EMERGENCY," affecting building status.
- **Access Control Logic**: Access to rooms is governed by room state, type, time, and user roles. Emergency states limit access to designated staff only.
- **Log Files**: Three log files capture user and card information, access attempts, and the college's room and building structure.
- **User Simulation**: Enables admins to simulate users accessing rooms, and generating log entries. If access is granted, admins can also log users leaving the room.

## Class Responsibilities
Below, you'll find detailed explanations for each class within the system, outlining their responsibilities and functionalities.

### User Class

- The `User` class represents an individual within the system and manages user-related functionalities.
- It encapsulates information such as the user's forename, surname, and roles held within the institution.
- This class facilitates various operations including adding, removing, and updating user data, such as roles or names.
- Alongside methods to display users alphabetically, and select users for swipe card removal.
- The `User` class interacts with the `IDCardLog` class to manage user-related log files and operations, such as adding, removing, displaying and updating user information.
- It also interacts with the `SwipeCard` class to handle functionalities related to adding and removing swipe cards, forming a composition relationship. 

### SwipeCard Class

- The `SwipeCard` class manages functionalities related to swipe cards within the system.
- It includes a constructor requiring a cardID to initialize a swipe card object.
- Provides a method (`addSwipeCard()`) to add a new swipe card to the system.
- Offers a function (`removeSwipeCard()`) to remove a swipe card from a specific user's index, specified in the `User` class.
- Works in conjunction with the `IDCardLog` class for updating the log file when a swipe card has been removed from a user.

### IDCardLog Class

- The `IDCardLog` class manages operations related to logging user data and interactions with ID cards within the system.
- Utilizes the Singleton design pattern for a single instance throughout the program's execution.
- Provides functionalities to log user data (`logUserData()`), read user data from a file (`readUserDataFromFile()`), and display all users' data stored in the log file (`displayUsersFromLogFile()`).
- Includes methods to remove a user's data from the log file based on the index (`removeUserFromLogFile()`), update user information (`updateUserInLogFile()`), update user roles (`updateUserRoles()`), and update the entire user data file with provided updated data (`updateUserDataFile()`).
- Manages interactions with the `User` class to handle user-related data and operations.

### Building Class

- The `Building` class manages functionalities related to buildings within the system.
- It includes attributes such as a unique building code, building name, and the current state of the building (Normal or Emergency).
- Utilizes an enum (`BuildingState`) to represent the state of a building.
- Maintains a collection of rooms (`Room*`) associated with the building.
- Provides methods to add (`addRoom()`), remove (`removeRoom()`), update (`updateRoom()`), and change the state (`changeRoomAndBuildingState()`) of rooms and the encompassing building.
- Offers functionalities (`addBuilding()`) to add new buildings to the system.
- Includes getter and setter methods for managing building code and name.
- Interacts with the `BuildingStructureLog` class for adding, removing and updating rooms in the log file.

### Room Class

- The `Room` class manages functionalities related to individual rooms within a building in the system.
- Inherits attributes from the `Building` class and includes additional details specific to rooms.
- It encompasses attributes such as floor number, room type (e.g., Lecture Hall, Teaching Room), room number, and the state of the room (Normal or Emergency).
- Utilizes an enum (`RoomState`) to represent the state of a room.
- Provides a virtual method (`verifyEntryRequirements()`) that will be implemented in its children's classes.
- Offers getter and setter methods for managing floor number, room type, room number, and room state.
- Implements functionality to convert `RoomState` enum values to their corresponding string representation (`roomStateToString()`).
- Interacts with the `Building` class due to its inheritance relationship for managing building-related attributes.

