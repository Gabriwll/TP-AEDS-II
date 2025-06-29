#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadhash.h"


#define MAX_WORD 100

// Hash function (djb2)
unsigned int hashFunction(char* word) {
    unsigned long hash = 5381;
    int c;
    while ((c = *word++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

// Inicializa a hash table
void initHashTable(HashTable* ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

WordEntry* createWordEntry(char* word, int idDoc) {
    WordEntry* entry = (WordEntry*) malloc(sizeof(WordEntry));
    entry->word = strdup(word);
    initializeList(&entry->occurrences);

    Word w;
    strcpy(w.word, word);
    w.searchTerm.idDoc = idDoc;
    w.searchTerm.qtde = 1;

    addCell(entry->occurrences, w);
    entry->next = NULL;
    return entry;
}

void updateOccurrenceList(List* list, char* word, int idDoc) {
    Word w;
    strcpy(w.word, word);
    w.searchTerm.idDoc = idDoc;

    Cell* found = searchCellByWord(list, w);
    if (found != NULL) {
        found->item.searchTerm.qtde++;
    } else {
        w.searchTerm.qtde = 1;
        addCell(list, w);
    }
}

void insertOccurrence(HashTable* ht, char* word, int idDoc) {
    unsigned int index = hashFunction(word);
    WordEntry* current = ht->table[index];

    while (current) {
        if (strcmp(current->word, word) == 0) {
            updateOccurrenceList(current->occurrences, word, idDoc);
            return;
        }
        current = current->next;
    }

    WordEntry* newEntry = createWordEntry(word, idDoc);
    newEntry->next = ht->table[index];
    ht->table[index] = newEntry;
}

WordEntry* searchWord(HashTable* ht, char* word) {
    unsigned int index = hashFunction(word);
    WordEntry* current = ht->table[index];
    while (current) {
        if (strcmp(current->word, word) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        WordEntry* current = ht->table[i];
        while (current) {
            WordEntry* temp = current;
            current = current->next;
            freeList(temp->occurrences);
            free(temp->word);
            free(temp);
        }
    }
}

void printOccurrences(List* list) {
    Cell* current = list->begin;
    while (current) {
        printf("<%d, %d> ", current->item.searchTerm.qtde, current->item.searchTerm.idDoc);
        current = current->next;
    }
}

void printHashTable(HashTable* ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        WordEntry* current = ht->table[i];
        while (current) {
            printf("%s: ", current->word);
            printOccurrences(current->occurrences);
            printf("\n");
            current = current->next;
        }
    }
}
