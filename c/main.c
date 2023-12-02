#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int FindFirstNumber(char* string) {
    int i = 0;
    while(1) {
        char c = string[i];

        if (c == '\0' || c == '\n' || c == '\r') {
            break;
        }

        if (c >= 48 && c <= 57) {
            // printf("Found a number string[%d]=%c. It's ASCII value is %d\n", i, c, c);
            //printf("FN: %c", c);
            return atoi(&c);
        }
        else {
            char* substring = malloc(i+2);
            strncpy(substring, string, i+1);
            substring[i+1] = '\0';
            int wordnumber = FindWordNumber(substring);
            if(wordnumber != -1) {
                //printf("FWN substring: %s | %d", substring, wordnumber);
                return wordnumber;
            }
            free(substring);
        }

        i++;
    }


    return 0;
}

int FindLastNumber(char* string) {
    int i = strlen(string)-1;
    while(i >= 0) {
        char c = string[i];

        if (c >= 48 && c <= 57) {
            // printf("Found a number string[%d]=%c. It's ASCII value is %d\n", i, c, c);
            //printf("\nLN: %c", c);
            return atoi(&c);
        }
        else {
            char* substring = malloc(strlen(string) - i + 1);
            strncpy(substring, string+i, strlen(string) - i + 1);
            //substring[i+1] = '\0';
            int wordnumber = FindWordNumber(substring);
            if(wordnumber != -1) {
                //printf("\nLWN substring: %s | %d", substring, wordnumber);
                return wordnumber;
            }
            free(substring);
        }

        i--;
    }


    return 0;
}

int main() {
    printf("Advent of code 2023 Solver\n");

    int numberOfSolutions = 1;

    // iterate from 0 to numberOfSolutions - 1
    // fetch data.txt for corresponding day
    // solve and print the results
    FILE* fptr = fopen("./day1/input.txt", "r");

    char buff[200];
    int result = 0;
    // printf("1");
    while(fgets(buff, sizeof(buff), fptr)) {
        //printf("\n%s", buff);
        result += (FindFirstNumber(buff) * 10) + FindLastNumber(buff);

        //printf("%s[%d]\n",buff,(FindFirstNumber(buff) * 10) + FindLastNumber(buff));
        // printf("%s [%d, %d]\n", buff, FindFirstNumber(buff)*10+FindLastNumber(buff), result);
    }
    printf("\nSolution: %d\n\n", result);


    FILE* fptr1 = fopen("./day1/testinput1.txt", "r");

    result = 0;
    // printf("1");
    while(fgets(buff, sizeof(buff), fptr1)) {
        //printf("\n%s", buff);
        result += (FindFirstNumber(buff) * 10) + FindLastNumber(buff);

        //printf("%s[%d, %d, %d]\n",buff,FindFirstNumber(buff), FindLastNumber(buff), (FindFirstNumber(buff) * 10) + FindLastNumber(buff));
        // printf("%s [%d, %d]\n", buff, FindFirstNumber(buff)*10+FindLastNumber(buff), result);
    }
    printf("\nSolution: %d\n", result);

    FILE* fptr2 = fopen("./day1/testinput2.txt", "r");

    result = 0;
    // printf("1");
    while(fgets(buff, sizeof(buff), fptr2)) {
        //printf("\n%s", buff);

        result += (FindFirstNumber(buff) * 10) + FindLastNumber(buff);

        //printf("%s[%d]\n",buff,(FindFirstNumber(buff) * 10) + FindLastNumber(buff));
        // printf("%s [%d, %d]\n", buff, FindFirstNumber(buff)*10+FindLastNumber(buff), result);
    }
    printf("\nSolution: %d", result);


    return 0;
}
