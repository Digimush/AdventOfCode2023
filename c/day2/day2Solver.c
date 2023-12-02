#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "day2Solver.h"

#define N = 5

int red = 12;
int green = 13;
int blue = 14;

// Length of "Game " string
int linePrefixLength = 5;

char colors[] = "rgb";

// TODO: move away from hardcoded size
struct Game {
    int isPossible;
    int maxRed;
    int maxGreen;
    int maxBlue;
} typedef Game;

Game games[100];

void ParseLine(char* buff) {
    char* semicolon = strchr(buff, ':');
    int semicolonIndex = semicolon - buff;
    char gameIdString[4];
    char* copyFrom = buff+linePrefixLength;
    int howMuchToCopy = semicolonIndex - linePrefixLength;
    memcpy(gameIdString, copyFrom, howMuchToCopy);
    gameIdString[howMuchToCopy] = '\0';

    int gameId = atoi(gameIdString) - 1;

    char* draws = buff + semicolonIndex + 1;
    char drawDelimiter[] = ";";
    char cubeDelimiter[] = ",";
    char* nextDraw = NULL;
    char* nextCube = NULL;
    char* draw = strtok_s(draws, drawDelimiter, &nextDraw);
    while (draw != NULL) {
        char* cube = strtok_s(draw, cubeDelimiter, &nextCube);
        while (cube != NULL) {
            size_t colorIndex = strcspn(cube, colors);
            char colorAmountSting[4];
            memcpy(colorAmountSting, cube+1, colorIndex-2);
            colorAmountSting[colorIndex-2] = '\0';
            int colorAmount = atoi(colorAmountSting);

            switch(cube[colorIndex]) {
                case 'r':
                    games[gameId].maxRed = games[gameId].maxRed < colorAmount ? colorAmount : games[gameId].maxRed;
                    if(colorAmount > red)
                        games[gameId].isPossible = 0;
                    break;
                case 'g':
                    games[gameId].maxGreen = games[gameId].maxGreen < colorAmount ? colorAmount : games[gameId].maxGreen;
                    if(colorAmount > green)
                        games[gameId].isPossible = 0;
                    break;
                case 'b':
                    games[gameId].maxBlue = games[gameId].maxBlue < colorAmount ? colorAmount : games[gameId].maxBlue;
                    if(colorAmount > blue)
                        games[gameId].isPossible = 0;
                    break;
            }

            cube = strtok_s(NULL, cubeDelimiter, &nextCube);
        }
        draw = strtok_s(NULL, drawDelimiter, &nextDraw);
    }
}

void day2Solver() {
    // initialize games
    for (int i = 0; i < 100; i++) {
        games[i].isPossible = 1;
        games[i].maxRed = 1;
        games[i].maxGreen = 1;
        games[i].maxBlue = 1;
    }

    FILE *fptr = fopen("./day2/input/input.txt", "r");

    char buff[255];
    while (fgets(buff, sizeof(buff), fptr)) {
        ParseLine(buff);
    }

    int result = 0;
    int gamePowers = 0;
    for (int i = 0; i < 100; i++) {
        if(games[i].isPossible) {
            result += i+1;
        }
        gamePowers += games[i].maxRed * games[i].maxGreen * games[i].maxBlue;;
    }

    printf("\n[Day 2 | Part 1] Solution: %d\n", result);
    printf("[Day 2 | Part 2] Solution: %d\n", gamePowers);

    assert(result == 2913);
    assert(gamePowers == 55593);
}