#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadhash.h"

#define MAX_WORD 100

// Simple hash function (djb2 algorithm)
unsigned int hashFunction(char* word) {
    unsigned long hash = 5381;
    int c;
    while ((c = *word++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASH_SIZE;
}

// Initializes the hash table
void initHashTable(HashTable* ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// Creates a new occurrence node
OcurrenceList* createOccurrence(int idDoc) {
    OcurrenceList* occ = (OcurrenceList*) malloc(sizeof(OcurrenceList));
    occ->idDoc = idDoc;
    occ->qtde = 1;
    occ->next = NULL;
    return occ;
}

// Creates a new word entry
WordEntry* createWordEntry(char* word, int idDoc) {
    WordEntry* entry = (WordEntry*) malloc(sizeof(WordEntry));
    entry->word = strdup(word); // duplicates the word
    entry->occurrences = createOccurrence(idDoc);
    entry->next = NULL;
    return entry;
}

// Inserts a word occurrence into the hash table
void insertOccurrence(HashTable* ht, char* word, int idDoc) {
    unsigned int index = hashFunction(word);
    WordEntry* current = ht->table[index];

    // Search for the word in the list at the hash index
    while (current) {
        if (strcmp(current->word, word) == 0) {
            // Word found, update occurrence list
            OcurrenceList* occ = current->occurrences;
            while (occ) {
                if (occ->idDoc == idDoc) {
                    occ->qtde++;
                    return;
                }
                if (occ->next == NULL) break;
                occ = occ->next;
            }
            // Document not found, add new occurrence
            occ->next = createOccurrence(idDoc);
            return;
        }
        current = current->next;
    }

    // Word not found, create new entry
    WordEntry* newEntry = createWordEntry(word, idDoc);
    newEntry->next = ht->table[index];
    ht->table[index] = newEntry;
}

// Searches for a word in the hash table
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

// Frees the occurrence list
void freeOccurrences(OcurrenceList* occ) {
    while (occ) {
        OcurrenceList* temp = occ;
        occ = occ->next;
        free(temp);
    }
}

// Frees the entire hash table
void freeHashTable(HashTable* ht) {
    for (int i = 0; i < HASH_SIZE; i++) {
        WordEntry* current = ht->table[i];
        while (current) {
            WordEntry* temp = current;
            current = current->next;
            freeOccurrences(temp->occurrences);
            free(temp->word);
            free(temp);
        }
    }
}

// Prints the list of occurrences for a word
void printOccurrences(OcurrenceList* occ) {
    while (occ) {
        printf("<%d, %d> ", occ->qtde, occ->idDoc);
        occ = occ->next;
    }
}

// Prints the entire hash table (unordered, by slot)
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