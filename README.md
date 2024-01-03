# College Access Control Solution
This C++ console application efficiently manages rooms, users, and swipe cards within a college environment. It facilitates user and role management, room and building administration, access logs, and user simulation for testing via an intuitive menu system.

## Installation Instructions

### Prerequisites
- **[Git](https://git-scm.com/)**: Install Git for version control.
- **[Visual Studio](https://visualstudio.microsoft.com/)**: Install Visual Studio IDE for C++ development.

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
- Provides a virtual method (`verifyEntryRequirements()`) that will be overridden in its children's classes.
- Offers getter and setter methods for managing floor number, room type, room number, and room state.
- Implements functionality to convert `RoomState` enum values to their corresponding string representation (`roomStateToString()`).
- Interacts with the `Building` class due to its inheritance relationship for managing building-related attributes.

#### LectureHall Class

- The `LectureHall` class, inheriting from `Room`, represents lecture halls within the system.
- Inherits the attributes and functionalities of the `Room` class and extends them to manage specific functionalities related to lecture halls.
- Provides an overridden method (`verifyEntryRequirements`) to verify access requirements for the lecture hall based on user roles and room state.

#### StaffRoom Class

- The `StaffRoom` class, a child of `Room`, signifies staff rooms within the system.
- Inherits attributes and functionalities from the `Room` class, specializing in functionalities specific to staff rooms.
- Implements an overridden method (`verifyEntryRequirements`) to determine access permissions based on user roles and room state.

#### SecureRoom Class

- The `SecureRoom` class, inheriting from `Room`, represents secure rooms within the system.
- Inherits properties and functionalities from the `Room` class and offers specialized functionalities for secure room access.
- Provides an overridden method (`verifyEntryRequirements`) to validate access based on user roles and room state.

#### TeachingRoom Class

- The `TeachingRoom` class, a subclass of `Room`, denotes teaching rooms within the system.
- Inherits functionalities and properties from the `Room` class and extends them to manage specific functionalities for teaching rooms.
- Implements an overridden method (`verifyEntryRequirements`) to assess access requirements considering user roles and room state.

### BuildingStructureLog Class

- The `BuildingStructureLog` class manages building-related log operations within the system.
- Provides static methods to handle various building data functionalities.
- Includes functions to verify unique buildings (`isDuplicate()`), log building information to specified file locations (`logInfo()`), and display stored file information (`displayFileInfo()`).
- Offers methods to retrieve building information at a specified index (`getBuildingInfo()`), manage room data operations within log files (`readRoomDataFromFile()`), and remove room information based on the index (`removeRoomFromLogFile()`).
- Update room info like floor number, room number, etc by using the (`updateRoomDataFile()`).
- Interacts with the `Building` class to facilitate building-related data management and operations.

### Simulation Class

- Manages the simulation operations within the system for user-room interactions.
- Contains methods to start (`startSimulation()`) and stop (`stopSimulation()`) the simulation.
- Handles the joining and leaving of users from rooms through methods like `joinRoom()` and `leaveRoom()`.
- Extracts user roles (`extractRoles()`) and room information (`extractRoomInfo()`) for access verification.
- Verifies user access to specific rooms based on roles, room type, and state using `verifyRoomAccess()`.
- Generates log messages (`generateLog()`) based on user, room, and access information.
- Utilizes classes such as `User`, `Room`, and its child classes (`LectureHall`, `TeachingRoom`, `StaffRoom`, `SecureRoom`), and `DailyLogFile`.
- Provides functionality to retrieve the current date and time in a formatted string (`getDateAndTime()`).

### DailyLogFile Class

- Manages daily log file operations within the system for room access attempts.
- Provides functionalities to log room access attempts (`logRoomAccessAttempts()`) by appending access information to a daily log file.
- Includes a method (`viewRoomAccessAttempts()`) to display room access attempts stored in the daily log file.
- Utilizes file input/output operations and string formatting to handle log information.
- Contains a private method (`getFormattedDate()`) to generate and return the formatted date as a string for logging purposes.

## Unit Tests (Gtest)

For quality assurance and validation, alongside manual testing, this solution includes unit test files using Google Test (`gtest`). Below are the additional files used for testing:

- `UserTests.cpp`: Unit tests for the `User` class functionalities.
- `SwipeCardTests.cpp`: Unit tests for the `SwipeCard` class operations.
- `LectureHallTests.cpp`: Unit tests specific to the functionalities of the `LectureHall` class.
- `SecureRoomTests.cpp`: Unit tests focusing on the `SecureRoom` class functionalities.
- `StaffRoomTests.cpp`: Unit tests for the `StaffRoom` class.
- `TeachingRoomTests.cpp`: Unit tests covering functionalities of the `TeachingRoom` class.
- `BuildingTests.cpp`: Unit tests related to the `Building` class.
- `RoomTests.cpp`: Unit tests for the `Room` class and its functionalities.
- `SimulationTests.cpp`: Tests for the simulation functionalities.

## References

Clark, M. (2023) 'Creating a Formatted Date String from Date Time in C', CopyProgramming. Available at: [https://copyprogramming.com/howto/c-get-formated-date-string-from-date-time#c11-get-current-date-and-time-as-string](https://copyprogramming.com/howto/c-get-formated-date-string-from-date-time#c11-get-current-date-and-time-as-string) [Accessed 27th December 2023].

Cplusplus.com (2023) 'std::vector::erase', Cplusplus.com. Available at: [https://cplusplus.com/reference/vector/vector/erase/](https://cplusplus.com/reference/vector/vector/erase/) [Accessed 18th December 2023].

Cppreference (2023) 'std::size_t - cppreference.com', en.cppreference.com. Available at: [https://en.cppreference.com/w/cpp/types/size_t](https://en.cppreference.com/w/cpp/types/size_t) [Accessed 18th December 2023].

Gangwar, M. (2023) 'How to Create a Random Number Generator in C++', DigitalOcean. Available at: [https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus](https://www.digitalocean.com/community/tutorials/random-number-generator-c-plus-plus) [Accessed 13th December 2023].

GeeksForGeeks (2023a) 'Sort string of characters', GeeksforGeeks. Available at: [https://www.geeksforgeeks.org/sort-string-characters/](https://www.geeksforgeeks.org/sort-string-characters/) [Accessed 14th December 2023].

GeeksForGeeks (2023b) 'Substring in C++', GeeksforGeeks. Available at: [https://www.geeksforgeeks.org/substring-in-cpp/](https://www.geeksforgeeks.org/substring-in-cpp/) [Accessed 18th December 2023].

GoogleTest (2023a) 'Advanced GoogleTest Topics', GoogleTest. Available at: [https://google.github.io/googletest/advanced.html](https://google.github.io/googletest/advanced.html) [Accessed 15th December 2023].

GoogleTest (2023b) 'GoogleTest Primer', GoogleTest. Available at: [https://google.github.io/googletest/primer.html](https://google.github.io/googletest/primer.html) [Accessed 15th December 2023].

Haleem, A. (2020) 'Exploring Date and Time with Chrono', Medium. Available at: [https://ambreen2006.medium.com/exploring-date-and-time-with-chrono-3a8e9af60f62](https://ambreen2006.medium.com/exploring-date-and-time-with-chrono-3a8e9af60f62) [Accessed 27th December 2023].

Instructables (n.d.) 'How to Do the Singleton Design Pattern in C++', Instructables. Available at: [https://www.instructables.com/How-to-Do-the-Singleton-Design-Pattern-in-C/](https://www.instructables.com/How-to-Do-the-Singleton-Design-Pattern-in-C/) [Accessed 27th December 2023].

Kaushik, A. (2022) 'C++ String Replace Function', Scaler Topics. Available at: [https://www.scaler.com/topics/cpp-string-replace/](https://www.scaler.com/topics/cpp-string-replace/) [Accessed 18th December 2023].

Programiz (2023a) 'C++ File Handling', Programiz. Available at: [https://www.programiz.com/cpp-programming/file-handling](https://www.programiz.com/cpp-programming/file-handling) [Accessed 14th December 2023].

Programiz (2023b) 'C++ Map', Programiz. Available at: [https://www.programiz.com/cpp-programming/map](https://www.programiz.com/cpp-programming/map) [Accessed 30th December 2023].

Ram, V. (2022) 'How to use the string find() in C++', DigitalOcean. Available at: [https://www.digitalocean.com/community/tutorials/string-find-c-plus-plus](https://www.digitalocean.com/community/tutorials/string-find-c-plus-plus) [Accessed 18th December 2023].

Tutorialspoint (2020) 'C++ Date and Time - Tutorialspoint', Tutorialspoint. Available at: [https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm](https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm) [Accessed 27th December 2023].
