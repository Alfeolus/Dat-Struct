#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc & free

struct Node{
	int id;
	char nama[50];
	struct Node* next;	
	struct Node* prev;
}*head, *tail;

struct Node* CreateNewNode(int id, char nama[]){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->id = id;
	strcpy(newNode->nama, nama);
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
};

void pushHead(int id, char nama[]){
	struct Node* newNode = CreateNewNode(id, nama);
	if(!head){
		head = tail = newNode;
	}
	else{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}

void pushTail(int id, char nama[]){
	struct Node* newNode = CreateNewNode(id, nama);
	if(!head){
		head = tail = newNode;
	}
	else{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
}

void forwardPrint(){
	struct Node* current = head;
	while(current != NULL){
		printf("%d %s <-> ", current->id, current->nama);
		current = current->next;
	}
	printf("NULL\n");
}

void backwardPrint(){
	struct Node* current = tail;
	while(current != NULL){
		printf("%d %s <-> ", current->id, current->nama);
		current = current->prev;
	}
	printf("NULL\n");
}

void pushMid(int id, char nama[]) {
    //kondisi 1 : belum ada node
    if(!head){
        struct Node* newNode = CreateNewNode(id, nama);
        head = tail = newNode;
    }
    //kondisi 2 : jika id < head->id
    else if(id < head->id){
        pushHead(id, nama);
    }
    // kondisi 3 : jika id >= tail->id
    else if( id >= tail->id){
        pushTail(id, nama);
    }
    // kondisi 4 : insertnya di tengah
    else{
        struct Node* newNode = CreateNewNode(id, nama);
        struct Node* current = head;
        while(current != NULL && current->id <= newNode->id){
            current = current->next; //7  push 8 21                  
        } //1 3 4  5(c) 7 9  new node = 4
        //pointer newNode
        newNode->prev = current->prev;
        newNode->next = current;

        newNode->prev->next = newNode;
        current->prev = newNode;
    }
}

struct Node* popHead() {
    //kondisi 1 : jika tidak ada node
    if(head == NULL) {
        return NULL;
    }
    //kondisi 2 : jika hanya ada 1 node
    else if(head == tail) {
        struct Node* temp = head;
        head = tail = NULL;
        return temp;
    }
    // kondisi 3 : jika sudah ada lebih dari 1 node
    else{
        struct Node* temp = head;
        head = head->next;
        head->prev = NULL;
        temp->next = NULL;
        return temp;
        // 1 5 7 9 11
        // t h
    }
}

struct Node* popTail() {
    //kondisi 1 : jika tidak ada node
    if(tail == NULL) {
        return NULL;
    }
    //kondisi 2 : jika hanya ada 1 node
    else if(head == tail) {
        struct Node* temp = head;
        head = tail = NULL;
        return temp;
    }
    // kondisi 3 : jika sudah ada lebih dari 1 node
    else{
        struct Node* temp = tail;
        tail = tail->prev;
        tail->next = NULL;
        return temp;
    }
}

struct Node* popMid(int id){
    //kondisi 1 : jika tidak ada node
    if(head == NULL) {
        return NULL;
    }
    // kondisi 2 : id == head->id
    else if(head->id == id){
        return popHead();
    }
    // kondisi 3 : id == tail-> id
    if(tail->id == id){
        return popTail();
    }
    // kondisi 4: data yang mau dihapus ada ditengah
    else{
        struct Node* current = head;
        while(current->id != id && current != NULL){
            current = current->next;
        }
        if(current == NULL){
            return NULL;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        return current;
    }
}

int main(){
	pushMid(3, "Andi");
	pushMid(1, "Budi");
	pushMid(2, "kimi");

    printf("Before delete\n");
    forwardPrint();
    struct Node* temp = popMid(1);
    if(temp != NULL) {
        printf("Deleted: %d %s\n", temp->id, temp->nama);
        free(temp);
    }
    else{
        printf("No data\n");
    }
    printf("After delete\n");
	forwardPrint();
//	backwardPrint();
	return 0;
}