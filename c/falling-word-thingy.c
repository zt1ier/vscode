// September 9, 2025
// THIS GAME IS A NESTED NIGHTMARE PLEASE TURN BACK

#include <stdio.h>
#include <stdlib.h> // rand() and srand() --- rng
#include <string.h> // strlen() --- length of string, how many characters
#include <conio.h> // getch() --- read input without needing to press Enter
#include <unistd.h> // sleep() --- time elapsed
#include <time.h> // also used for rng


int clamp(int value, int min, int max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}


int main() {

    srand(time(NULL)); // randomizes internal seed

    const float DURATION = 1.25;

    char *gameGrid[] = {
        "....................",
        "....................",
        "....................",
        "....................",
        "....................",
        "....................",
        "....................",
    };


    // OT names idk
    char *words[] = {
        "Abraham",
        "Bathsheba",
        "Canaan",
        "David",
        "E",
        "F",
        "G",
        "Hagar",
        "Israel",
        "Joshua",
        "K",
        "L",
        "Moses",
        "Nahor",
        "O",
        "P",
        "Q",
        "Rachel",
        "Solomon",
        "Thomas",
        "U",
        "V",
        "W",
        "X",
        "Yahweh",
        "Zebulun",

    };

    int gridSize = sizeof(gameGrid) / sizeof(gameGrid[0]); // gets number of elements in array

    int currentRow = 1;
    char guess[100];

    // using gridSize doesn't work because it's a runtime constant :( but it works on other compilers?
    char *grid[sizeof(gameGrid) / sizeof(gameGrid[0])] = {};

    // duplicate grid, we'll use the copy
    for (size_t i = 0; i < gridSize; i++) {

        grid[i] = gameGrid[i];

    };

    // get number of characters in first row;
    int rowLength = strlen(grid[0]);

    // choose random word from words array
    int wordsSize = sizeof(words) / sizeof(words[0]);
    char *randomWord = words[rand() % gridSize];
    int wordLength = strlen(randomWord);

    // random number from 0 to rowLength (20 in this case because it is)
    int randomPosition = clamp((rand() % rowLength) - wordLength, 0, rowLength);

    
    clock_t start = clock();

    while (currentRow < gridSize) {

        // "clears" the terminal
        // it just moves everything up so it looks like it's cleared
        printf("\033[H\033[J");

        // print column
        for (size_t i = 0; i < gridSize; i++) {

            if (i == currentRow) {
                // print word row
                for (size_t j = 0; j < randomPosition; j++) {
                    printf(".");
                };
                printf("%s", randomWord);
                for (size_t j = 0; j < (rowLength - wordLength - randomPosition); j++) {
                    printf(".");

                };
                printf("\n");
            } 
            else {

                // print other rows
                for (size_t j = 0; j < rowLength; j++) {
                    printf(".");
                };
                printf("\n");
            }

        };

        // elapse n seconds
        sleep(DURATION);
        currentRow++;

        //char input = getch();
        //*guess += input + "\0";
        //printf("%s", guess);

    }

    printf("%d", wordsSize);

    return 0;
}