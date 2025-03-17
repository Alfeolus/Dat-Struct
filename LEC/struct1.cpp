#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct game{
    char name[100];
    char rank[25];
    int hp;
    int magic;
    int gold;
};

game fix[100];

void insertMenu();
void viewMenu();
void deleteMenu();
void upgradeMenu();

int count  = 0;

int main(){
    int choice  =  -1;
        do{
            puts("1.Insert");
            puts("2.View");
            puts("3.Delete");
            puts("4.Upgrade");
            puts("5.Exit");
            printf(">> ");
            scanf("%d",&choice); getchar();
            switch(choice){
            case 1 :
                insertMenu();
                break;
            case 2 :
                viewMenu();
                break;
            case 3 :
                deleteMenu();
                break;
            case 4 :
                upgradeMenu();
                break;
            case 5 :
                return 0;
        }
        }while(choice > 0 && choice <= 5);
    }
 
            
        

void insertMenu() {
    game temp;
    
    printf("INPUT PLAYER NAME: ");
    scanf("%[^\n]",temp.name); getchar();

    do{
        printf("Input player rank: ");
        scanf("%s",temp.rank); getchar();
    }while(strcmp(temp.rank, "Bronze")!= 0 &&
            strcmp(temp.rank, "Silver")!= 0 &&
            strcmp(temp.rank, "Gold")!= 0 );

    printf("Input player HP: ");
    scanf("%d",&temp.hp); getchar();

    printf("Input player magic: ");
    scanf("%d",&temp.magic); getchar();

    printf("Input player Gold: ");
    scanf("%d",&temp.gold); getchar();

    fix[count] = temp;
    count++;
    puts("Product insert successfully");
}
void viewMenu() {
    if(count == 0){
        puts("There is no Product");
    }

    else{
        for(int i = 0; i < count; i++) {
            printf("%d %s - %s\n",i, fix[i].name, fix[i].rank);
        }
    }
}
void deleteMenu() {
    if(count == 0){
        puts("There is no Product");
    }

    else{
        for(int i = 0; i < count; i++) {
            printf("%d. %s - %s\n",i, fix[i].name, fix[i].rank);
        }
    }
    int choice;
    scanf("%d",&choice); getchar();
    choice += -1;
    for(int i = choice; i < count-1; i++) {
        fix[i]= fix[i+1];
    }
    count--;
}
void upgradeMenu() {
    if(count == 0){
        puts("There is no Product");
    }

    else{
        for(int i = 0; i < count; i++) {
            printf("%d %s - %s\n",i, fix[i].name, fix[i].rank);
        }
    }
    int choice;
    scanf("%d",&choice); getchar();
    choice += -1;
    fix[choice].hp += 150;
    fix[choice].magic += 150;
    fix[choice].gold -= 50;

    printf("%s\n",fix[choice].name);
    printf("%s\n",fix[choice].rank);
    printf("%d\n",fix[choice].hp);
    printf("%d\n",fix[choice].magic);
    printf("%d\n",fix[choice].gold);
}