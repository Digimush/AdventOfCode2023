#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day1Solver.h"

char* wordnumbers[] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
};

int FindWordNumber(char* string) {
    for(int i = 0; i < 10; i++) {
        if(strstr(string, wordnumbers[i]) != NULL) {
            return i;
        }
    }
    return -1;
}

int FindFirstNumberP1(char* string) {
    int i = 0;
    while(1) {
        char c = string[i];

        if (c == '\0' || c == '\n' || c == '\r') {
            break;
        }

        if (c >= 48 && c <= 57) {
            // if i remove next 3 lines, it returns 77 instead of 7 this sting:
            // sevencxbpxvznqmjqgglfccqkvjqmjbpthreenineeightnhszbvnff7
            char* tmp = &c;
            int tmp2 = atoi(&c);
            int tmp3 = atoi(tmp);
            return atoi(&c);
        }
        i++;
    }

    return 0;
}

int FindLastNumberP1(char* string) {
    int i = strlen(string)-1;
    while(i >= 0) {
        char c = string[i];

        if (c >= 48 && c <= 57) {
            // if i remove next 3 lines, it returns 77 instead of 7 this sting:
            // sevencxbpxvznqmjqgglfccqkvjqmjbpthreenineeightnhszbvnff7
            char* tmp = &c;
            int tmp2 = atoi(&c);
            int tmp3 = atoi(tmp);
            return atoi(&c);
        }
        i--;
    }

    return 0;
}

int FindFirstNumberP2(char* string) {
    int i = 0;
    while(1) {
        char c = string[i];

        if (c == '\0' || c == '\n' || c == '\r') {
            break;
        }

        if (c >= 48 && c <= 57) {
            return atoi(&c);
        }
        else {
            char* substring = malloc(i+2);
            strncpy(substring, string, i+1);
            substring[i+1] = '\0';
            int wordnumber = FindWordNumber(substring);
            if(wordnumber != -1) {
                return wordnumber;
            }
            free(substring);
        }
        i++;
    }

    return 0;
}

int FindLastNumberP2(char* string) {
    int i = strlen(string)-1;
    while(i >= 0) {
        char c = string[i];

        if (c >= 48 && c <= 57) {
            return atoi(&c);
        }
        else {
            char* substring = malloc(strlen(string) - i + 1);
            strncpy(substring, string+i, strlen(string) - i + 1);
            int wordnumber = FindWordNumber(substring);
            if(wordnumber != -1) {
                return wordnumber;
            }
            free(substring);
        }
        i--;
    }

    return 0;
}

void day1Solver() {
    FILE* fptr = fopen("./day1/input/input.txt", "r");

    char buff[200];
    int result = 0;
    while(fgets(buff, sizeof(buff), fptr)) {
        int firstNumber = FindFirstNumberP1(buff);
        int lastNumber = FindLastNumberP1(buff);
        result += (firstNumber* 10) + lastNumber;
        //printf("\n%s [%d,%d]", buff, firstNumber, lastNumber);
    }
    printf("\n[Day 1 | Part 1] Solution: %d\n", result);

    fseek(fptr, 0, SEEK_SET);
    result = 0;
    while(fgets(buff, sizeof(buff), fptr)) {
        int firstNumber = FindFirstNumberP2(buff);
        int lastNumber = FindLastNumberP2(buff);
        result += (firstNumber * 10) + lastNumber;
    }
    printf("[Day 1 | Part 2] Solution: %d\n", result);
}