#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../LinkedList/linkedlist.h"

typedef struct List List;

List* readFile(int idDoc);
void readWord(FILE* file, List* list, int idDoc);
void cleanString(char *originalWord);
int getdocQuant();
char* setFileName(char fileName[], int idDoc);

#endif