#include <iostream>
#include <vector>
#include <conio.h>
#include <cctype>


// simple struct to hold (x, y) coordinate
struct Position {
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
    Position player = {1, 1};

    bool running = true; // game loop control flag
    char lastKey = ' ';  // store last pressed key

    while (running) {
        // makes it so the game "refreshes" and doesn't just print below the old sequence
        // ANSI escape sequence to clear screen and move cursor to top-left
        // \033 = escape character; basically tells terminal "hey this is a command, not a string"
        // [2J = clear entire screen
        // [1;1H = move cursor to row 1 column 1 (top-left)
        std::cout << "\033[2J\033[1;1H";

        // make copy of map so we can place the player
        // this way we don’t overwrite original map data
        auto displayMap = map;

        // put the player character '@' on the map copy
        displayMap[player.y][player.x] = '@';

        // print the map to the terminal
        for (auto &row : displayMap)
            std::cout << row << "\n";

        // show last key pressed
        std::cout << "Pressed '" << lastKey << "' key\n";

        // wait for player input (WASD to move, Q to quit)
        char lowInput = _getch();
        char input = std::toupper(lowInput);
        lastKey = input; // store for next frame

        // store new position as copy of current one
        int newX = player.x;
        int newY = player.y;

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
            player.x = newX;
            player.y = newY;
        }
    }

    // exit program
    return 0;
}