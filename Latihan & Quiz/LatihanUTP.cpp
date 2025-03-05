#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define size 100

struct booking{
    char name[101];
    char number[20];
    int age;
    char type[101];
    int duration;
    char id[101];
    booking *next;
}*book[size];

bool validName(char *name){
    int len = strlen(name);
    return len>=3 && len <= 30;
}

bool validNumber(char *number){
    if(number[0] != '+' || number[1] != '6' || number[2] != '2'){
        return false;
    }
    int space = 0;
    int len = strlen(number);
    for(int i = 3; i <len; i++){
        if(number[i]== ' '){
            space++;
        }
    }
    return space >=1 && (len-space-3) == 11; 
}

bool validAge(int age){
    return age >= 18;
}

bool validType(char *type){
    return strcmp(type,"Deluxe") == 0 ||
           strcmp(type, "Regular") == 0 ||
           strcmp(type, "Suite") == 0;
}

bool validDuration(int duration){
    return duration >= 1 && duration <= 30;
}

char *generateId(char *type){
    char* id = (char*)malloc(sizeof(char)*7);
    
    id[0] = toupper(type[0]);
    id[1] = toupper(type[1]);

    for(int i = 2; i < 5; i++){
        id[i] = rand()%10 + '0';
    }
}

int getHash(char *id){
    //DE187
    int key = -1;
    for(int i = 2; i < 5; i++){
        key += id[i];
    }
    key -= 1;
    key %= size;

    return key;
}

struct booking *newBooking(char *name, char *number, int age, 
char *type, int duration){
    char *id = generateId(type);
    struct booking *curr = (booking*)malloc(sizeof(booking));
    strcpy(curr->name, name);
    strcpy(curr->number, number);
    curr->age = age;
    strcpy(curr->type, type);
    curr->duration = duration;
    strcpy(curr->id, id);

    curr->next = NULL;
    return curr->next;
}

void pushTail(struct booking *newData){
    int hash = getHash(newData->id);
    if(book[hash]== NULL){
        book[hash] = newData;
    }
    else{
        struct booking *temp = book[hash];
        while(temp->next !=NULL){
            temp = temp->next;
        }
        temp->next = newData;
    }
}

void createBooking(){
    char name[101];
    char number;
    int age;
    int duration;
    
}