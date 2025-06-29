#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../InvertedIndex/invertedIndex.h"

typedef struct Word Word;

typedef Word Item;
//typedef int Item;

typedef struct Cell{
    Word item;
    struct Cell* next;
}Cell;

typedef struct List{
    int sizeOfList;
    Cell* begin;
    Cell* end;
}List;

void initializeList(List** list);
void initializeCell(Cell** cell);
Cell* addCell(List* list, Item item);
int removeCell(List* list, Item item);
Cell* searchCellByWord(List* list, Item item);
void freeList(List* list);
void printList(List list);

#endif