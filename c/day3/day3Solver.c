#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "day3Solver.h"

struct PartNumber {
    int number;
    int isAdjacent;
    int lineIndex;
    int startIndex;
    int endIndex;
} typedef PartNumber;

struct PartNumbersArrayList {
    size_t capacity;
    size_t length;
    PartNumber* elements;
} typedef PartNumbersArrayList;

void PNArrayList_Init(PartNumbersArrayList* list) {
    list->capacity = 100;
    list->length = 0;
    list->elements = malloc(sizeof(PartNumber) * list->capacity);
}

void PNArrayList_Add(PartNumbersArrayList* list, PartNumber element) {
    if(list->length == list->capacity) {
        list->capacity *= 2;
        list->elements = realloc(list->elements, list->capacity * sizeof(PartNumber));
    }
    list->elements[list->length].lineIndex = element.lineIndex;
    list->elements[list->length].startIndex = element.startIndex;
    list->elements[list->length].endIndex = element.endIndex;
    list->elements[list->length].number = element.number;
    list->elements[list->length].isAdjacent = element.isAdjacent;
    list->length++;
}

void PNArrayList_Free(PartNumbersArrayList* list) {
    free(list->elements);
    list->elements = NULL;
    list->capacity = 0;
    list->length = 0;
}

struct Part {
    int lineIndex;
    int positionIndex;
    char type;
    int totalAdjacent;
} typedef Part;

struct PartsArrayList {
    size_t capacity;
    size_t length;
    Part* elements;
} typedef PartsArrayList;

void PArrayList_Init(PartsArrayList* list) {
    list->capacity = 100;
    list->length = 0;
    list->elements = malloc(sizeof(Part) * list->capacity);
}

void PArrayList_Add(PartsArrayList* list, Part element) {
    if(list->length == list->capacity) {
        list->capacity *= 2;
        list->elements = realloc(list->elements, list->capacity * sizeof(Part));
    }
    list->elements[list->length].positionIndex = element.positionIndex;
    list->elements[list->length].lineIndex = element.lineIndex;
    list->elements[list->length].type = element.type;
    list->elements[list->length].totalAdjacent = element.totalAdjacent;
    list->length++;
}

void PArrayList_Free(PartsArrayList* list) {
    free(list->elements);
    list->elements = NULL;
    list->capacity = 0;
    list->length = 0;
}

PartNumbersArrayList partNumbersList;
PartsArrayList partsList;

void ParseSchematic(char* string, int lineIndex) {
    int length = strlen(string);
    int curNumber = 0;
    int partNumberStartIndex = -1;
    int partNumberEndIndex = -1;
    for(int i = 0; i < length; i++) {
        if(string[i] >= 48 && string[i] <= 57) {
            if(partNumberStartIndex == -1) {
                partNumberStartIndex = i;
            }
            partNumberEndIndex = i;
            int num = (string[i] - '0');
            curNumber = (curNumber * 10) + num;
        } else {
            if(curNumber != 0) {
                PartNumber partNumber;
                partNumber.number = curNumber;
                partNumber.startIndex = partNumberStartIndex;
                partNumber.endIndex = partNumberEndIndex;
                partNumber.lineIndex = lineIndex;
                partNumber.isAdjacent = 0;
                PNArrayList_Add(&partNumbersList, partNumber);
                curNumber = 0;
                partNumberStartIndex = -1;
                partNumberEndIndex = -1;
            }

            if(string[i] != '.' && string[i] != '\n') {
                Part part;
                part.type = string[i];
                part.lineIndex = lineIndex;
                part.positionIndex = i;
                part.totalAdjacent = 0;
                PArrayList_Add(&partsList, part);
            }
        }
    }
}

void day3Solver() {
    FILE *fptr = fopen("./day3/input/input.txt", "r");

    PNArrayList_Init(&partNumbersList);
    PArrayList_Init(&partsList);

    char buff[255];
    int lineIndex = 0;
    while (fgets(buff, sizeof(buff), fptr)) {
        ParseSchematic(buff, lineIndex);
        lineIndex++;
    }

    int result = 0;
    int resultP2 = 0;
    int currentGearRatio = 0;
    for (int i = 0; i < partsList.length; i++) {
        for (int j = 0; j < partNumbersList.length; j++) {
            if (((partNumbersList.elements[j].startIndex >= partsList.elements[i].positionIndex - 1
                  && partNumbersList.elements[j].startIndex <= partsList.elements[i].positionIndex + 1)
                 || (partNumbersList.elements[j].endIndex >= partsList.elements[i].positionIndex - 1
                     && partNumbersList.elements[j].endIndex <= partsList.elements[i].positionIndex + 1))
                && partNumbersList.elements[j].lineIndex >= partsList.elements[i].lineIndex - 1
                && partNumbersList.elements[j].lineIndex <= partsList.elements[i].lineIndex + 1) {

                partNumbersList.elements[j].isAdjacent = 1;
                result += partNumbersList.elements[j].number;
                partsList.elements[i].totalAdjacent++;
                currentGearRatio = currentGearRatio == 0
                                   ? partNumbersList.elements[j].number
                                   : currentGearRatio * partNumbersList.elements[j].number;
            }
        }
        if (partsList.elements[i].totalAdjacent != 2) {
            currentGearRatio = 0;
        }
        resultP2 += currentGearRatio;
        currentGearRatio = 0;
    }

    printf("\n[Day 3 | Part 1] Solution: %d\n", result);
    PNArrayList_Free(&partNumbersList);
    PArrayList_Free(&partsList);

    assert(result == 522726);

    printf("[Day 3 | Part 2] Solution: %d\n", resultP2);
    assert(resultP2 == 81721933);
}