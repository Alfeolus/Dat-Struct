#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define maxsize 100

struct vehicle{
    char name[101];
    char type[50];
    int duration;

    struct vehicle *next;
}*mobil[maxsize];

void insert();
void view();
void update();

int validName(char *name){
    int l = strlen(name);
    int space = 0;

    for(int i = 0 ; i < l; i++){
        if(name[i] == ' '){
            space++;
        }
    }
    if(space == 1) return 1;
    else return 0;
}

bool validUnique(char *name){
    int idx = 0;
    int len = strlen(name);

    for(int i = 0; i < len; i++){
        if(name[i] == ' ') idx = i;
    }
    char kata1[50];
    for(int i = 0; i< idx; i++){
        kata1[i]= name[i];
    }
		kata1[idx] = '\0';
    char kata2[50];
    for(int i = idx+1; i <= len; i++){
        kata2[i] = name[i];
    }
		kata2[idx] = '\0';

    if(strcmp(kata1,kata2) != 0 ) return true;
    else return false;
}

struct vehicle *newNode(char *name, char *type, int duration){
    struct vehicle* curr = (vehicle*)malloc(sizeof(vehicle));
    strcpy(curr->name, name);
    strcpy(curr->type, type);
    curr->duration = duration;

    curr->next = NULL;
    return curr;
}

int gethash(char *name){
    int l = strlen(name);
    int key = 0;
    for(int i = 0; i < l; i++){
        key += name[i];
    }
    return key % maxsize;
}

void push(struct vehicle *c){
    int hash = gethash(c->name);
    if(mobil[hash] == NULL){
        mobil[hash] = c;
    }
    else{
        struct vehicle *temp = mobil[hash];
        while(temp->next){
            temp = temp->next;
        }
        temp->next = c;
    }
}

int main(){
    int input = -1;
    do{
        printf("Nelson Garage\n");
        printf("1. Insert Vehicle\n");
        printf("2. View Vehicles \n");
        printf("3. Update storage duration\n");
        printf("4. Exit menu\n");
        do{
        scanf("%d",&input); getchar();
        }while(input < 1 && input > 4);
        switch(input){
            case 1:
            insert();
            break;
            case 2:
            view();
            break;
            case 3:
            update();
            break;
            case 4:
            puts("Thank you");
            return 0;
        }
    }while(1);
}

void insert(){
    char name[100];
    char type[50];
    int duration;

    do{
        printf("Input vehicle name: ");
        scanf("%[^\n]",name); getchar();
    }while(!validName(name) || !validUnique(name));

    do{
        printf("Input vehicle type: ");
        scanf("%[^\n]",type); getchar();
    }while(strcmp(type, "SUV") != 0 && strcmp(type, "Sedan")!= 0 &&
        	strcmp(type, "Hatchback")!= 0 );

		do{
			printf("Input duration: ");
			scanf("%d",&duration); getchar();
		}while(duration < 1);

		push(newNode(name,type,duration));

		return;
}

void view(){
		int flag = 0;
		for(int i = 0; i < maxsize; i++){
			if(mobil[i]){
				flag = 1;
				struct vehicle *temp = mobil[i];
				while(temp){
					printf("Vehicle Name\t : %s\n", temp->name);
					printf("Vehicle Type\t : %s\n", temp->type);
					printf("Duration\t: %d\n", temp->duration);
					printf("\n");
					temp = temp->next;
				}
			}
		}
		if(flag == 0){
			printf("There is no data\n");
		}

}

int validTarget(char target[]){
		for(int i = 0; i < maxsize; i++){
			if(mobil[i]){
				struct vehicle *temp = mobil[i];
				while(temp){
					if(strcmp(temp->name, target) == 0){
						return 1;
					}
					temp = temp->next;
				}

			}
		}
		return 0;
}

void update(){
		int flag = 0;

		for(int i = 0; i < maxsize; i++){
			if(mobil[i]){
				flag =1;
				vehicle *temp = mobil[i];
				while(temp){
					
				}
			}
		}
}