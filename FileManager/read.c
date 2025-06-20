#include <stdio.h>
#include <string.h>

#include "read.h"
#include "../InvertedIndex/invertedIndex.h"
#include "../LinkedList/linkedlist.h"

void readFile(int idDoc /* LinkedList list */){
    FILE* file;
    List* list;
    char fileName[25] = setFileName(idDoc);
    
    initializeList(&list);

    file = fopen(fileName, "r");
    if(file == NULL){
        printf("Failed to open file:\n%s\n", fileName);
    }

    while(!feof(file)){
        readWord(file, list, idDoc);
    }

    fclose(file);
}

void readWord(FILE* file, List* list, int idDoc){
    Cell buffer;
    Cell* foundCell;

    fscanf(file, "%s", buffer.item.word);
    foundCell = searchCellByWord(list, buffer.item);

    if(foundCell == NULL){ //Palavra não encontrada na lista, adiciona nova célula na lista e inicializa Parâmetros importantes
        foundCell = addCell(list, buffer.item);
        foundCell->item.searchTerm.idDoc = idDoc;
        foundCell->item.searchTerm.qtde = 1;

    }else{ //Palavra já encontrada na lista, incrementa o contador de ocorrências
        foundCell->item.searchTerm.qtde++;
    }
}

int getdocQuant(){
    FILE* file;
    int docQuant;

    file = fopen("../Files/In/entrada.txt", "r");
    if(file == NULL){
        printf("Failed to open file:\n../Files/In/entrada.txt\n");
    }

    fscanf(file, "%d", &docQuant);
    fclose(file);

    return docQuant;
}

char* setFileName(int idDoc){
    char fileName[25];

    strcpy(fileName, "../Files/In/arquivo");

    strcat(fileName, idDoc);
    strcat(fileName, ".txt");

    return fileName;
}

//Ambiente de testes destinado a esse TAD
/*FIXME: remover esse ambiente de testes assim que o funcionamento total desse TAD seja comprovado
* Uma alternativa seria manter esse ambiente em um branch secundário, a fim de uso na entrevista
*/
int main(){

}