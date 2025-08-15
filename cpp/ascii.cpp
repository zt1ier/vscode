#include <iostream>
#include <vector>
#include <conio.h>
#include <cctype>


char playerIcon = 'P';


// simple struct to hold (x, y) coordinate
struct position {
    int x; // column (horizontal position)
    int y; // row (vertical position)

};


int main() {
    // define simple ASCII map using vector of strings
    // '#' = wall, '.' = floor
    std::vector<std::string> map = {
        "###############",
        "#.............#",
        "#.............#",
        "#.............#",
        "#.............#",
        "#.............#",
        "###############"
    };


    // player starting position (column 1, row 1)
    Position playerPos = {1, 1};

    bool running = true; // game loop control flag
    char lastKey = ' ';  // store last pressed key

    while (running) {
        // make copy of map so we can place the player
        // this way we don’t overwrite original map data
        auto displayMap = map;

        // put player character on map copy
        displayMap[playerPos.y][playerPos.x] = playerIcon;

        // print map
        for (auto &row : displayMap)
            std::cout << row << "\n";

        // show last key pressed
        std::cout << "Pressed '" << lastKey << "' key\n";

        // wait for player input (WASD to move, Q to quit)
        char lowInput = _getch();
        char input = std::toupper(lowInput);
        lastKey = input; // store for next frame

        // store new position as copy of current one
        int newX = playerPos.x;
        int newY = playerPos.y;

        // update intended position based on key pressed
        if (input == 'W') newY--;               // move up
        else if (input == 'S') newY++;          // move down
        else if (input == 'A') newX--;          // move left
        else if (input == 'D') newX++;          // move right
        else if (input == 'Q') {
            std::cout << "Exited";
            running = false; // quit game
        } 
        // check collision with walls
        // only update player position if target tile is not wall ('#')
        if (map[newY][newX] != '#') {
            playerPos.x = newX;
            playerPos.y = newY;
        }
    }

    // exit program
    return 0;
}