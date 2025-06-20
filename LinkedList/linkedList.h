#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//typedef Word Item;
typedef int Item;

typedef struct Cell{
    Item item;
    struct Cell* next;
}Cell;

typedef struct List{
    int sizeOfList;
    Cell* begin;
    Cell* end;
}List;

void initializeList(List** list);
void addCell(List* list, Item item);
int removeCell(List* list, Item item);
void freeList(List* list);
void printList(List list);

#endif