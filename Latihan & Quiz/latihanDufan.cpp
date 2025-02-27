#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char name[50];
    char priority;
    struct node *next;
}*h, *t, *c;

void addAntrian(char pName[], char pPriority){
    c = (struct node*) malloc(sizeof(struct node));
    strcpy(c->name, pName);
    c->priority = pPriority;
    c->next = NULL;

    if(!h){
        h = t = c;
    }else if(h->priority > pPriority){
        c->next = h;
        h = c;
    }else{
        struct node *temp = h;
        while(temp->next && temp->next->priority <= pPriority){
            temp = temp->next;
        }
        c->next = temp->next;
        temp->next = c;
        if(!c->next) t = c;
    }
}

void callAntrian(){
    if(!h) return;
    struct node *temp = h;
    h = h->next;
    free(temp);
}

void removeAntrian(char pName[]){
    if(!h) return;
    struct node *temp = h, *prev = NULL;
    while(temp && strcmp(temp->name, pName) != 0){
        prev = temp;
        temp = temp->next;
    }
    if(!temp) return;
    if(!prev){
        h = h->next;
    }else{
        prev->next = temp->next;
        if(!prev->next) t = prev;
    }
    free(temp);
}

void print(){
    struct node *temp = h;
    int i = 1;
    while(temp){
        printf("%d. %s %c\n", i, temp->name, temp->priority);
        temp = temp->next;
        i++;
    }
}

int main(){
    char pilihan[50];
    int jumlah;
    scanf("%s %d", pilihan, &jumlah);
    for(int i = 0; i < jumlah; i++){
        if(strcmp(pilihan, "REGISTER") == 0){
            char nama[50];
            char prioritas;
            scanf("%s %[^\n]", nama, prioritas);
            addAntrian(nama, prioritas);
        }else if(strcmp(pilihan, "CALL") == 0){
            callAntrian();
        }else if(strcmp(pilihan, "REMOVE") == 0){
            int removeCount;
            scanf("%d", &removeCount);
            for(int j = 0; j < removeCount; j++){
                char nama[50];
                scanf("%s", nama);
                removeAntrian(nama);
            }
        }
    }
    print();
    return 0;
}
