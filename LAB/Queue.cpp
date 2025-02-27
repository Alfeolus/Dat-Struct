#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enqueue (push tail)
// dequeue (pop head)
// front (melihat data paling depan/ head)
// rear (melihat data paling belakang/ tail)

struct Node{
	int priority;
	char nama[50];
	struct Node* next;	
	struct Node* prev;
}*head, *tail;

struct Node* CreateNewNode(int priority, char nama[]){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->priority = priority;
	strcpy(newNode->nama, nama);
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
};

void pushTail(int priority, char nama[]){
	struct Node* newNode = CreateNewNode(priority, nama);
	if(!head){
		head = tail = newNode;
	}
	else{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
}

void getFront(){
    printf("Front: %d %s\n", head->priority, head->nama);
}

int main() {
    pushTail(1, "Andi");
    pushTail(2, "Budi");
    pushTail(3, "Caca");
    pophead();
    getFront();
//getRear();

}