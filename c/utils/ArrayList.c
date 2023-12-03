//
// Created by akhristenko on 03.12.2023.
//

#include <malloc.h>
#include "ArrayList.h"

void ArrayList_Init(ArrayList* list) {
    list->capacity = 2;
    list->length = 0;
    list->elements = malloc(sizeof(int) * list->capacity);
}

void ArrayList_Add(ArrayList* list, int element) {
    if(list->length == list->capacity) {
        list->capacity *= 2;
        list->elements = realloc(list->elements, list->capacity * sizeof(int));
    }
    list->elements[list->length] = element;
    list->length++;
}

void ArrayList_Free(ArrayList* list) {
    free(list->elements);
    list->elements = NULL;
    list->capacity = 0;
    list->length = 0;
}
