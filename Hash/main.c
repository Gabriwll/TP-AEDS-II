#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tadhash.h"
#include "../LinkedList/linkedList.h"

void insertOccurrence(HashTable* ht, char* word, int idDoc);
void printHashTable(HashTable* ht);
void initHashTable(HashTable* ht);
void freeHashTable(HashTable* ht);

int main() {
    HashTable ht;
    initHashTable(&ht);
    printf ("salve\n");
    getchar();

    insertOccurrence(&ht, "casa", 1);
    insertOccurrence(&ht, "casa", 1);
    insertOccurrence(&ht, "casa", 2);
    insertOccurrence(&ht, "quer", 1);
    insertOccurrence(&ht, "quer", 1);
    insertOccurrence(&ht, "quer", 1);
    insertOccurrence(&ht, "quer", 2);
    insertOccurrence(&ht, "apartamento", 1);
    insertOccurrence(&ht, "todos", 2);
    insertOccurrence(&ht, "todos", 2);
    insertOccurrence(&ht, "ninguem", 1);
    insertOccurrence(&ht, "ninguem", 1);
    insertOccurrence(&ht, "ninguem", 2);
    insertOccurrence(&ht, "quem", 1);
    insertOccurrence(&ht, "quem", 2);
    insertOccurrence(&ht, "quem", 2);

    printf("\n==== Hash Table ====\n");
    printHashTable(&ht);

    getchar();
}
