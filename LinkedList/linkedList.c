#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../InvertedIndex/invertedIndex.h"
#include "linkedList.h"

void initializeList(List** list){
    *list = (List*)malloc(sizeof(List));

    (*list)->sizeOfList = 0;
    (*list)->begin = NULL;
    (*list)->end = NULL;
}

Cell* addCell(List* list, Item item){
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
    return newCell;
}

int removeCell(List* list, Item item){
    Cell* currentCell = list->begin;
    Cell* previousCell = NULL;

    while(currentCell != NULL && currentCell->item.searchTerm.idDoc == item.searchTerm.idDoc && 
                                 strcmp(currentCell->item.word, item.word) == 0){
                                 //TODO: check if this is the right way to compare items
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

Cell* searchCellByWord(List* list, Item item){
    Cell* currentCell = list->begin;

    while(currentCell != NULL){
        if(currentCell->item.searchTerm.idDoc == item.searchTerm.idDoc &&
           strcmp(currentCell->item.word, item.word) == 0) return currentCell;

        currentCell = currentCell->next;
    }

    return NULL;
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

/*Ambiente de testes destinado a esse TAD
* FIXME: adaptar esse ambiente de testes para o tipo Word
* Uma alternativa seria manter esse ambiente em um branch secundário, a fim de uso na entrevista
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
*/