#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//pls add stdlib.h and string.h for future assignments


struct RecordType {
    int id;
    char name;
    int order;
    struct RecordType *next;
};

struct HashType {
    struct RecordType **hashtable;
    //double pointer for the insertrecord function
};

int hash(int x, int tableSize) {
    return x % tableSize;
}

int parseData(char *inputFileName, struct RecordType **ppData) {
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }
        fclose(inFile);
    }
    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz) {
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize) {
    // call the hash function to get the index
    int index = hash(record->id, tableSize);
    if (hashTable->hashtable[index] == NULL)
        hashTable->hashtable[index] = record;
        // if the RecordType at that index is NULL
        // set 'record' equal to the HashType pointer in the table at index
    else {
        struct RecordType *curr = hashTable->hashtable[index];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = record;
    }
    // else
        // traverse to the end of the linkedlist and add 'record' to the end of it
}

void displayRecordsInHash(struct HashType *hashTable, int tableSize) {
    // for each entry in the table
        // print the contents in that index
        // The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"
    for (int i = 0; i < tableSize; i++) {
        printf("Index %d -> ", i+1);
        if (hashTable->hashtable[i] == NULL)
            printf("NULL\n");
        else {
            struct RecordType *curr = hashTable->hashtable[i];
            while (curr != NULL) {
                printf("%d, %c, %d -> ", curr->id, curr->name, curr->order);
                curr = curr->next;
                //iterate through the hashtable 
            }
            printf("NULL\n");
            //printfs null when it reaches the end of the hash table
        }
    }
}

int main(void) {
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Initialize the hash table
    struct HashType *HashTable = malloc(sizeof(struct HashType));
    // create a variable hashTableSize and assign it a value
    int tableSize = 11;
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    HashTable->hashtable = calloc(tableSize, sizeof(struct RecordType*));
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    for (int i = 0; i < recordSz; i++) {
        insertRecord(HashTable, &pRecords[i], tableSize);
    }
    // call the display records function
    displayRecordsInHash(HashTable, tableSize);

    // free all the allocated memory
    for (int i = 0; i < tableSize; i++) {
        struct RecordType *curr = HashTable->hashtable[i];
        while (curr != NULL) {
            struct RecordType *temp = curr->next;
            //set the temp pointer to the next node, then free current one
            free(curr);
            curr = temp;
        } 
    }
    //free the rest of the allocated memory
    free(HashTable->hashtable);
    free(HashTable);
    free(pRecords);

    return 0;
}
