#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define max 100

struct borrow{
    char name[50];
    char libraryId[100];
    char borrowId[105];
    char title[100];
    int duration;
    borrow *next;
}*borrows[max];

bool validName(char *name){
    int len = strlen(name);
    return len >= 3 && len <= 30;
}

bool validLibraryId(char *libraryId){
    int count  = 0;
    if(libraryId[0] != 'L' || libraryId[1] != 'I' || libraryId[2] != 'B'){
        return false;
    }

    else{
        //LIB12345
        for(int i = 3 ; i < 8; i++){
            count++;
        }
    }
    return count == 5;
}

bool validTitle(char *title){
    int l = strlen(title);
    return l >= 3 && l <= 50;
}

bool validDuration(int duration){
    return duration >= 1 && duration <= 30;
}

char *generateId(char* title){
    char *id = (char*)malloc(sizeof(char)*7);
    id[0] = toupper(title[0]);
    id[1] = toupper(title[1]);

    for(int i = 2; i < 5; i++){
        id[i] = rand()%1000 + '0';
    }

    return id;
}
//LA345
int getHash(char *borrowId){
    int key = -1;
    char str[100];
    sprintf(str, "%c%c%c", borrowId[2], borrowId[3], borrowId[4]);
    int num = atoi(str);
    num *= num;

    sprintf(str, "%d%d%d", num,num,num);
    int len = strlen(str);

    if(len % 2 == 0){
        key = str[len/2-1]-'0' *10 + str[len/2] -'0';
    }
    else{
        key = str[len/2];
    }
    return key % max;
}

struct borrow *newBorrow(char* name, char* libraryId,
char* title, int duration){
    char *borrowId = generateId(title);
    struct borrow* curr = (borrow*)malloc(sizeof(borrow));
    strcpy(curr->name,name);
    strcpy(curr->libraryId,libraryId);
    strcpy(curr->title, title);
    strcpy(curr->borrowId, borrowId);
    curr->duration = duration;

    curr->next = NULL;
    return curr;
}

void pushTail(struct borrow *newData){
    int hash = getHash(newData->borrowId);
    if(borrows[hash] == NULL){
        borrows[hash] = newData;
    }
    else{
        struct borrow *temp = borrows[hash];
        while(temp->next){
            temp = temp->next;
        }
        temp->next = newData;
    }
}

void createBooking(){
    char name[50];
    char libraryId[20];
    char borrowId[20];
    char title[50];
    int duration;

    do{
        printf("Enter your full name : ");
        scanf("%[^\n]",name); getchar();
    }while(!validName(name));

    do{
        printf("Enter your library ID (format: LIB-XXXXX): ");
        scanf("%s",libraryId); getchar();
    }while(!validLibraryId(libraryId));

    do{
        printf("Enter the book title: ");
        scanf("%[^\n]",title); getchar();
    }while(!validTitle(title));

    do{
        printf("Enter borrowing duration[1-30 days]: ");
        scanf("%d",&duration); getchar();
    }while(!validDuration(duration));

    pushTail(newBorrow(name,libraryId,title,duration));
    printf("enter to continue..");
    getchar();
}

void viewBorrow(){
    // system("cls");
    bool found = false;
    
    for(int i = 0; i < max; i++){
        struct borrow *curr = borrows[i];
        while(curr){
            printf("Borrowing id: %s\n", curr->borrowId);
            printf("Borrower name: %s\n", curr->name);
            printf("Library id: %s\n",curr->libraryId);
            printf("Book title: %s\n",curr->title);
            printf("Duration: %d\n",curr->duration);
            curr= curr->next;
            found = true;
        }
    }
    if(!found) printf("No data\n");
    printf("enter to continue...");
    getchar();
}

void returnBook(){
    printf("tes");
}

int main(){
int input = -1;
    do{
        do{
            printf("==========================\n");
            printf("     BOOKHAVEN LIBRARY\n");
            printf("==========================\n");
            puts("1. Borrow a book");
            puts("2. View borrowed book");
            puts("3. Return book");
            puts("4. Exit");
            printf("==========================\n");
            printf("Enter your choice: ");
            scanf("%d",&input); getchar();
        }while(input < 1 || input > 4 );

        switch(input){
            case 1:
            createBooking();
            break;
            case 2:
            viewBorrow();
            break;
            case 3:
            returnBook();
            break;
            case 4:
            return 0;
            break;
        }
    }while(1);
}

