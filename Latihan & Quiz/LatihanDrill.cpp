#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define max 100

struct Node {
    char name[100];
    int priority;
    struct Node *next;
} *hash[max], *h = NULL, *t = NULL;

int gethash(char *name) {
    int l = strlen(name);
    int hash = 0;

    for (int i = 0; i < l; i++) {
        hash += name[i];
    }

    return hash % max; // Fix: Correct modulo operation for valid hashing
}

struct Node *newNode(char *name, int priority) {
    struct Node *curr = (struct Node *)malloc(sizeof(struct Node));
    if (!curr) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(curr->name, name);
    curr->priority = priority;
    curr->next = NULL;
    return curr;
}

void push(struct Node *c) {
    if (!h) {
        h = t = c;
    } else if (c->priority < h->priority) { // Insert at head
        c->next = h;
        h = c;
    } else if (c->priority > t->priority) { // Insert at tail
        t->next = c;
        t = c;
    } else { // Insert in the middle
        struct Node *temp = h;
        while (temp->next && temp->next->priority <= c->priority) {
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
    }
}

void add() {
    char name[100];
    int priority;

    printf("Enter Name and Priority: ");
    scanf("%s %d", name, &priority);
    getchar(); // To consume newline

    push(newNode(name,priority));
}

void pushHash(struct Node *data) {
    int key = gethash(data->name);

    if (!hash[key]) {
        hash[key] = data;
    } else {
        struct Node *temp = hash[key];
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = data;
    }
}

void execute() {
    if (!h) {
        printf("Queue is empty!\n");
        return;
    }

    struct Node *temp = h;
    h = h->next;
    temp->next = NULL; // Remove linkage

    pushHash(temp);
}

void print() {
    int flag = 0;
    for (int i = 0; i < max; i++) {
        struct Node *temp = hash[i];
        if (temp) {
            flag = 1;
            printf("Index: %d\n", i);
            while (temp) {
                printf("    Name: %s, Priority: %d\n", temp->name, temp->priority);
                temp = temp->next;
            }
        }
    }
    if (!flag) {
        printf("Hash table is empty.\n");
    }
}

int main() {
    int input = -1;
    do {
        printf("\n1. Add\n");
        printf("2. Execute\n");
        printf("3. Print hash table\n");
        printf("4. Exit\n");
        printf(">> ");

        scanf("%d", &input);
        getchar(); // Consume newline

        switch (input) {
            case 1:
                add();
                break;
            case 2:
                execute();
                break;
            case 3:
                print();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please select 1-4.\n");
        }
    } while (1);

    return 0;
}

