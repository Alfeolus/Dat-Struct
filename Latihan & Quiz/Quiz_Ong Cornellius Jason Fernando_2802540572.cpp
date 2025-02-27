#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

struct tnode {
    char id[101];
    int impact;
    int likelihood;
    int priority;
    struct tnode* next;
};

struct tnode* hashTable[HASH_SIZE];

struct tnode* createNode(char* id, int impact, int likelihood) {
    struct tnode* newNode = (struct tnode*)malloc(sizeof(struct tnode));
    newNode->impact = impact;
    newNode->likelihood = likelihood;
    strcpy(newNode->id, id);
    
    if (impact == 1 && likelihood == 1) newNode->priority = 3;
    else if (impact == 1 && likelihood == 0) newNode->priority = 2;
    else if (impact == 0 && likelihood == 1) newNode->priority = 1;
    else newNode->priority = 0;

    newNode->next = NULL;
    return newNode;
}

int hash(char* id) {
    int hashValue = 0;
    for (int i = 0; id[i] != '\0'; i++) {
        hashValue += id[i];
    }
    return hashValue % HASH_SIZE;
}

void enqueue() {
    char id[101];
    int impact, likelihood;

    scanf("%s %d %d", id, &impact, &likelihood);

    struct tnode* newNode = createNode(id, impact, likelihood);
    int hashIndex = hash(id);

    if (!hashTable[hashIndex]) {
        hashTable[hashIndex] = newNode;
    } else if (hashTable[hashIndex]->priority < newNode->priority) {
        newNode->next = hashTable[hashIndex];
        hashTable[hashIndex] = newNode;
    } else {
        struct tnode* temp = hashTable[hashIndex];
        while (temp->next != NULL && temp->next->priority >= newNode->priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void dequeue() {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i]) {
            struct tnode* temp = hashTable[i];
            hashTable[i] = hashTable[i]->next;
            free(temp);
            return;
        }
    }
    printf("No data\n");
}

void view() {
    int dataada = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i]) {
            dataada = 1;
            struct tnode* temp = hashTable[i];
            while (temp != NULL) {
                printf("ID: %s - ", temp->id);
                if (temp->priority == 3) printf("Critical\n");
                else if (temp->priority == 2) printf("High\n");
                else if (temp->priority == 1) printf("Medium\n");
                else printf("Low\n");
                temp = temp->next;
            }
        }
    }
    if (!dataada) {
        printf("No data\n");
    }
}

void viewHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Index %d: ", i);
        struct tnode* temp = hashTable[i];
        while (temp != NULL) {
            printf("ID: %s", temp->id, temp->priority);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        enqueue();
    }
    view();
    printf("\n");
    dequeue();
    dequeue();
    view();
    printf("\n");
    printf("Processing vulnerabilities...\n");
    printf("\n");
    viewHashTable();
    return 0;
}
