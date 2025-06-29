#ifndef tadhash_h
#define tadhash_h

#include "../LinkedList/linkedList.h"

#define HASH_SIZE 1000

typedef struct WordEntry {
    char* word;
    List* occurrences;
    struct WordEntry* next;
} WordEntry;

typedef struct {
    WordEntry* table[HASH_SIZE];
} HashTable;

#endif // tadhash_h
