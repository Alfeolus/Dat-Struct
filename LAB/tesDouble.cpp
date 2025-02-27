#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char nama[50];
    int umur;
    struct node *next;
    struct node *prev;
}*head,*tail;

struct node* createNode(char nama[], int umur){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->nama, nama);
    newNode->umur = umur;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void pushHead(char nama[], int umur){
    struct node *newNode = createNode(nama, umur);
    if(!head){
        head = tail = newNode;
    }
    else{
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }


}

void pushTail(char nama[], int umur){
    struct node *newNode = createNode(nama, umur);
    if(!head){
        head = tail = newNode;
    }
    else{
        
    }
}

