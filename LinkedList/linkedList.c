/***************************************************
 * Universidade Federal de Viçosa - Campus Florestal
 * Disciplina: Algoritmos e Estruturas de Dados II
 * Período: 2025/1
 * Trabalho Prático I - Índice Invertido com PATRICIA e HASH
 
 * Integrantes:
 * -Helom Felipe Marques Alves - 5892
 * -Maria Eduarda Oliveira - 5365
 * -Gabriel Luiz Magalhães Amorim - 5560 
 * -Raíssa Tayná Xavier dos Santos - 5790 

 ***************************************************/
#include "linkedList.h"

void initializeList(List** list){
    *list = (List*)malloc(sizeof(List));

    (*list)->sizeOfList = 0;
    (*list)->begin = NULL;
    (*list)->end = NULL;
}

void initializeCell(Cell** cell){
    *cell = (Cell*)malloc(sizeof(Cell));
    (*cell)->next = NULL;
}

Cell* addCell(List* list, Item item){
    Cell* newCell;
    
    initializeCell(&newCell);
    newCell->item = item;
    
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
        if(!strcmp(currentCell->item.word, item.word)) return currentCell;

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
        printf("\tCelula %d:\n", (i+1));
        printf("\t\tPalavra: %s\n\n", currentCell->item.word);
        printf("\t\tID do Documento: %d\n", currentCell->item.searchTerm.idDoc);
        printf("\t\tQuantidade: %d\n\n\n", currentCell->item.searchTerm.qtde);
        currentCell = currentCell->next;
    }
}

//Ambiente de testes destinado a esse TAD
// FIXME: adaptar esse ambiente de testes para o tipo Word
// Uma alternativa seria manter esse ambiente em um branch secundário, a fim de uso na entrevista
/*
int main(){
    List* list;
    Item item;
    
    item.searchTerm.idDoc = 1;
    item.searchTerm.qtde = 1;
    
    initializeList(&list);
    
    for(int i = 0; i < 5; i++){
        strcpy(item.word, "teste");
        strcat(item.word, (char[]){'1' + i, '\0'});

        addCell(list, item);

        printf("Adicionando celula %d:\n", (i + 1));
        printf("\t\tPalavra: %s\n\n", item.word);
        printf("\t\tID do Documento: %d\n", item.searchTerm.idDoc);
        printf("\t\tQuantidade: %d\n\n\n", item.searchTerm.qtde);

        item.searchTerm.qtde++;
    }

    //removeCell(list, item);

    printList(*list);

    freeList(list);

    return 0;
}
*/