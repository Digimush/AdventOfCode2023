#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "day4Solver.h"

int numbers[100];
int scratchcards[211];

char* RemoveStart(char* string) {
    return strchr(string, ':') + 1;
}

void InitScratchcards() {
    for (int i = 0; i < 211; i++) {
        scratchcards[i] = 1;
    }
}

void ParseCard(char* line, int lineIndex) {
    char* data = RemoveStart(line);
    char delimiter[] = " ";
    char* token = strtok(data, delimiter);
    int matchingNumbers = 0;
    while(token != NULL) {
        if (*token != '|') {
            int value = atoi(token);
            numbers[value]++;
            if(numbers[value] > 1) {
                matchingNumbers++;
            }
        }
        token = strtok(NULL, delimiter);
    }
    // calculating copies
    for(int i = 0; i < matchingNumbers; i++) {
        scratchcards[lineIndex + (i + 1)] += 1 * scratchcards[lineIndex];
    }
}

void resetNumbers() {
    for (int i = 0; i < 100; i++) {
        numbers[i] = 0;
    }
}

int calculateResult() {
    int result = 0;

    for (int i = 0; i < 100; i++) {
       if(numbers[i] > 1) {
            if (!result) {
                result++;
            }
            else {
                result *= 2;
            }
       }
    }

    return result;
}

int calculateCopies() {
    int result = 0;
    for (int i = 0; i < 211; i++) {
        result += scratchcards[i];
    }
    return result;
}

void day4Solver() {
    int result1 = 0;
    int result2 = 0;

    resetNumbers();
    InitScratchcards();

    FILE *fptr = fopen("./day4/input/input.txt", "r");

    char buff[255];
    int lineIndex = 0;
    while (fgets(buff, sizeof(buff), fptr)) {
        ParseCard(buff, lineIndex);

        result1 += calculateResult();

        resetNumbers();
        lineIndex++;
    }

    printf("\n[Day 4 | Part 1] Solution: %d\n", result1);
    assert(result1 == 20667);

    result2 = calculateCopies();
    printf("[Day 4 | Part 2] Solution: %d\n", result2);
    assert(result2 == 5833065);
}