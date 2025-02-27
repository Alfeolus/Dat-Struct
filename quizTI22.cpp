#include <stdio.h>
#include <string.h> 
#include <stdlib.h> // malloc & free
#include <time.h>

struct tnode{
    char address[101];
    char id[101];
    char type[101];
    int priority;
    struct tnode* next;
}*queue;

int main(){
    srand(time(NULL));
    int choice = -1;
    do{
        do{

        }while(choice < 1 || choice > 4);
    }while(1);

    return 0;
}

tnode* createNode(char address[], char id[], char type[]){
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    strcpy(newNode->address, address);
    strcpy(newNode->id, id);
    strcpy(newNode->type, type);

    if(strcmp(type, "Instant") == 0) newNode-> priority = 0;
    else if(strcmp(type, "Standard") == 0) newNode-> priority = 1;
    else newNode-> priority = 2;

    newNode->next = NULL;
    return newNode;
}

void push(){
    //address id type

    char address[101],id[101], type[101];

    do{

    }while(strlen(address) < 8 || strlen(address)>23 || 
        strncmp(address,"Jl.", 3)!=0 );

    sprintf(id, "%c%c%c",'c','p','x');
    //atau bisa id[0] = c , id[1] = p
    for(int i = 3; i <6; i++){
        int alphaorNumeric = rand()%2;
        if(alphaorNumeric == 0){
            int random = rand() % 26;
            id[i] = random + 'A';
        }
        else{
            int random = rand() % 10;
            id[i] = random + '0';
        }
    }
    id[7] = 0;

    do{

    }while(strcmp(type, "Economy") != 0  &&
            strcmp(type, "Standard") != 0  &&
            strcmp(type, "Instant") != 0 );

    tnode* newNode = createNode(address,id, type);

    priorityQueue(newNode);
}

void priorityQueue(tnode* newNode){
    //KONDISI 1 : KOSONG
    if(queue == NULL) {
        queue = newNode;
        return;
    }
    //KONDISI 2 : PRIORITTY = 2
    if(newNode->priority == 2){
        tnode* temp = queue;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
    //KONDISI 3 : DI TENGAH
    else{
        tnode* temp = queue;
        while(temp->next->priority <= newNode->priority && temp != NULL){
            temp = temp->next;
        }
        if(temp != NULL){
            newNode-> next = temp->next;
            temp->next = newNode;
        }
        else{
            temp->next = newNode;
        }
        
    }
}

void send(){
    //pop head
    if(queue == NULL) {
        printf("No data\n");
        return;
    }

    tnode* temp = queue;
    queue = queue->next;
    free(temp);
}

void view(){
    if(queue == NULL) {
        printf("No data\n");
        return;
    }
    tnode* temp = queue;
    while(temp != NULL){
        printf("%s - %s - %s\n", temp->address, temp->id, temp->type);
        temp = temp->next;
    }
}

void exit(){
    tnode* temp = queue;
    while(temp != NULL){
        printf("%s  (%s) successfully sent to %s\n", temp->id, temp->type, temp->address);
        temp = temp->next;
    }
}