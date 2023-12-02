#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "day2Solver.h"

#define N = 5

int red = 12;
int green = 13;
int blue = 14;

// Length of "Game " string
int linePrefixLength = 5;

char colors[] = "rgb";

// TODO: move away from hardcoded size
int games[100];

void ParseLine(char* buff) {
    int gameStatus = 1;
    char* semicolon = strchr(buff, ':');
    int semicolonIndex = semicolon - buff;
    printf("Semicolon index: %d\n", semicolonIndex);
    char gameIdString[4];
    char* copyFrom = buff+linePrefixLength;
    int howMuchToCopy = semicolonIndex - linePrefixLength;
    //strncpy(gameIdString, copyFrom, howMuchToCopy);
    //printf("%c", copyFrom[0]);
    memcpy(gameIdString, copyFrom, howMuchToCopy);
    gameIdString[howMuchToCopy] = '\0';
    printf("GameIdString: %s\n", gameIdString);

    int gameId = atoi(gameIdString) - 1;

    char* draws = buff + semicolonIndex + 1;
    printf("Draws: %s\n", draws);
    char drawDelimiter[] = ";";
    char cubeDelimiter[] = ",";
    char* nextDraw = NULL;
    char* nextCube = NULL;
    char* draw = strtok_s(draws, drawDelimiter, &nextDraw);
    while (draw != NULL && games[gameId]) {
        printf("\tDraw: %s\n", draw);
        char* cube = strtok_s(draw, cubeDelimiter, &nextCube);
        while (cube != NULL) {
            printf("\t\t%s\n", cube);
            size_t colorIndex = strcspn(cube, colors);
            printf("\t\t\tColor: [%d]%c\n",colorIndex, cube[colorIndex]);
            char colorAmountSting[4];
            memcpy(colorAmountSting, cube+1, colorIndex-2);
            colorAmountSting[colorIndex-2] = '\0';
            int colorAmount = atoi(colorAmountSting);
            printf("\t\t\tAmount: %s[%d]\n", colorAmountSting, colorAmount);

            switch(cube[colorIndex]) {
                case 'r':
                    if(colorAmount > red)
                        games[gameId] = 0;
                    break;
                case 'g':
                    if(colorAmount > green)
                        games[gameId] = 0;
                    break;
                case 'b':
                    if(colorAmount > blue)
                        games[gameId] = 0;
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
        games[i] = 1;
    }

    FILE *fptr = fopen("./day2/input/input.txt", "r");

    char buff[255];
    while (fgets(buff, sizeof(buff), fptr)) {
        printf("\n--\n%s", buff);
        ParseLine(buff);
    }

    int result = 0;
    for (int i = 0; i < 100; i++) {
        printf("Game[%d] = %d\n", i, games[i]);
        if(games[i])
            result += i+1;
    }

    printf("\n[Day 2 | Part 1] Solution: %d\n", result);

//        fseek(fptr, 0, SEEK_SET);
//        while(fgets(buff, sizeof(buff), fptr)) {
//        }
//        printf("[Day 2 | Part 2] Solution: %d\n", result);

}