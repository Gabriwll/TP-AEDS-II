#include <stdio.h>
#include <stdlib.h>

//#include "../InvertedIndex/invertedIndex.h"
#include "linkedList.h"

void initializeList(List** list){
    *list = (List*)malloc(sizeof(List));

    (*list)->sizeOfList = 0;
    (*list)->begin = NULL;
    (*list)->end = NULL;
}

void addCell(List* list, Item item){
    Cell* newCell = (Cell*)malloc(sizeof(Cell));
    newCell->item = item;
    newCell->next = NULL;

    if(list->begin == NULL){
        list->begin = newCell;
        list->end = newCell;
    }else{
        list->end->next = newCell;
        list->end = newCell;
    }

    list->sizeOfList++;
}

int removeCell(List* list, Item item){
    Cell* currentCell = list->begin;
    Cell* previousCell = NULL;

    while(currentCell != NULL && currentCell->item != item){
        //FIXME: Desenvolvido para uso com o tipo Item int
        //Adaptar para usar o item de tipo Word
        //if(currentCell->item.word == item.word) break; // Assuming Item has a member 'word'
        previousCell = currentCell;
        currentCell = currentCell->next;
    }

    if(currentCell == NULL) return 1; // Item not found

    if(previousCell == NULL){
        list->begin = currentCell->next;
    }else{
        previousCell->next = currentCell->next;
    }

    if(currentCell == list->end){
        list->end = previousCell; // Update end if we removed the last cell
    }

    free(currentCell);
    list->sizeOfList--;
}

void freeList(List* list){
    Cell* currentCell = list->begin;
    Cell* nextCell;

    while(currentCell != NULL){
        nextCell = currentCell->next;
        free(currentCell);
        currentCell = nextCell;
    }

    free(list);
}

void printList(List list){
    Cell* currentCell = list.begin;

    printf("Lista:\nTamanho: %d\n", list.sizeOfList);
    for(int i = 0; i < list.sizeOfList; i++){
        printf("\tCelula %d: %d\n", (i+1), currentCell->item);
        currentCell = currentCell->next;
    }
}

int main(){
    List* list;
    Item item = 0;

    initializeList(&list);

    for(int i = 0; i < 5; i++){
        addCell(list, item);
        item += 2;
    }

    removeCell(list, 4);

    printList(*list);

    freeList(list);

    return 0;
}