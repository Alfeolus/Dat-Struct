#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char address[101];
    char id[101];
    char type[101];
    int priority;
    node *next;
}*h,*t;

int main(){
	srand(time(NULL)); 
	int choice = -1; 
	do{
		do{
			system("cls"); 
			printf("Copi Xpress\n"); 
			printf("1. Insert new package\n"); 
			printf("2. Send a package\n"); 
			printf("3. View all packages\n"); 
			printf("4. Exit\n"); 
			printf(">> "); 
			scanf("%d", &choice); getchar(); 
		} while(choice < 1 || choice > 4); 
		
		switch(choice){
			case 1: 
				insert(); 
				break; 
			case 2: 
				send(); 
				break; 
			case 3: 
				view(); 
				break; 
			case 4: 
				exitMenu(); 
				return 0; 
		}
	} while(1); 
	return 0; 
}

node* createNode(char *address, char *id, char *type, int priority){
    node* newNode = (node*)malloc(sizeof(node));
    strcpy(newNode->address,address);
    strcpy(newNode->id, id);
    if(strcmp(newNode->type, "Express") == 0) newNode->priority = 0;
    else if(strcmp(newNode->type, "Express") == 0) newNode->priority = 1;
    else newNode->priority = 2;
}



