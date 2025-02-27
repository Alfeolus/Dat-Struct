#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <time.h> 

struct tnode{
	char adress[101]; 
	char id[101]; 
	char type[101]; 
	int priority; 
	tnode* next; 
} *h, *t; 

tnode* createNode(char* adress, char* id, char* type); 
void insert(); 
void send(); 
void view(); 
void exitMenu(); 

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

tnode* createNode(char* adress, char* id, char* type){
	tnode* newNode = (tnode*)malloc(sizeof(tnode)); 
	strcpy(newNode->adress, adress); 
	strcpy(newNode->id, id); 
	
	if(strcmp(type, "Instant") == 0) newNode->priority = 0; 
	else if(strcmp(type, "Standard") == 0) newNode->priority = 1; 
	else newNode->priority = 2; 
	
	strcpy(newNode->type, type); 
	newNode->next = NULL; 
	return newNode; 
} 

void insert(){
	system("cls"); 
	char adress[101], id[101], type[101]; 
	
	do{
		printf("Adress (must start with \"Jl.\", 5-20 characters [inclusive]): "); 
		scanf("%[^\n]", adress); getchar(); 
	} while(strlen(adress) < 8 || strlen(adress) > 23 || strncmp(adress, "Jl.", 3) != 0); 
	
	
	id[0] = 'C'; 
	id[1] = 'P'; 
	id[2] = 'X'; 
	for(int i=3; i<6; i++){
		int aOrI = rand() % 2; 
		if(aOrI == 0){
			int value = rand() % 26; 
			id[i] = value + 'A'; 
		}
		else{
			int value = rand() % 10; 
			id[i] = value + '0'; 
		}
	}
	
	do{
		printf("Package Type (Economy/Standard/Instant [case sensitive]): "); 
		scanf("%s", type); getchar(); 
	} while(strcmp(type, "Instant") != 0 && strcmp(type, "Standard") != 0 && strcmp(type, "Economy") != 0); 
	
	tnode* newNode = createNode(adress, id, type); 
	//kondisi 1 : kosong
	if(!h) h = t = newNode; 
    //Kondisi 2 : push tail
	else if(t->priority <= newNode->priority){
		t->next = newNode; 
		t = newNode; 
	}
    // kondisi 3 : push head
	else if(h->priority > newNode->priority){
		newNode->next = h; 
		h = newNode; 
	}
    // kondiisi 4 : di tengah (push mid)
	else{
		tnode* temp = h; 
		while(temp->next != NULL && temp->next->priority <= newNode->priority){
			temp = temp->next; 
		}
		newNode->next = temp->next; 
		temp->next = newNode; 
	}
	
	printf("Package inserted\n"); 
	getchar(); 
}

void send(){
	if(!h){
		printf("No data\n"); 
		getchar(); 
		return; 
	}
	
	tnode* temp = h; 
	printf("%s (%s) successfully sent to %s\n", temp->id, temp->type, temp->adress); 
	
	h = temp->next; 
	free(temp); 
	getchar(); 
}

void view(){
	if(!h){
		printf("No data\n"); 
		getchar(); 
		return; 
	}
	
	tnode* temp = h; 
	while(temp != NULL){
		printf("%s - %s - %s\n", temp->id, temp->type, temp->adress); 
		temp = temp->next; 
	}
	getchar(); 
}

void exitMenu(){
	if(!h){
		printf("No data\n"); 
		getchar(); 
		return; 
	}
	
	tnode* temp = h; 
	
	while(temp != NULL){
		printf("%s (%s) successfully sent to %s\n", temp->id, temp->type, temp->adress); 
		temp = temp->next; 
	}
	printf("Exit program\n"); 
	getchar(); 
}