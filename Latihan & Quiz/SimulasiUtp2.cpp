#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct borrow{
    char name[101];
    char libraryId[101];
    char borrowId[101];
    char title[100];
    int duration;

    borrow *next;
}*h, *t;

int main(){
int input = -1;
    do{
        do{
            printf("BookHaven\n");
            printf("1. Borrow A book\n");
            puts("2. View borrowed book");
            puts("3. Return book");
            puts("4. Exit");
        }while(input < 1 && input >4);
    }while(1);
}

bool validName(char *name){
    int len = strlen(name);
    return len >= 3 && len <= 30;
}

int validlibraryId(char* libraryId){
    // LIB-12345
    if(strncmp(libraryId, "LIB-",4)!= 0) return 0;
    int flag = 1;
    for(int i = 4; i < 9; i++){
        if(!isdigit(libraryId[i])) flag =0;
    }
    return flag;

}

bool validTitle(char *title){
    int l = strlen(title);
    return title >= 3 && title <= 50;
}

bool validDuration(int duration){
    return duration >=1 && duration <=30;
}

char *generateId(char* title){
    char *id = (char*)malloc(sizeof(char));
    id[0] = toupper(title[0]);
    id[1] = toupper(title[1]);

    for(int i = 2; i < 5; i++){
        id[i] = rand() % 1000 + 0;
    }
    return id;
}

int getHash(char *borrowId){
    
}
struct borrow *newBorrow()