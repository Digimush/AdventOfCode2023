#ifndef C_ARRAYLIST_H
#define C_ARRAYLIST_H
struct ArrayList {
    size_t capacity;
    size_t length;
    int* elements;
} typedef ArrayList;

void ArrayList_Init(ArrayList* list);
void ArrayList_Add(ArrayList* list, int element);
void ArrayList_Free(ArrayList* list);
#endif //C_ARRAYLIST_H
