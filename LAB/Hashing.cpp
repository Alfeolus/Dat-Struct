#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_table 10

struct node{
    char nama[50];
    node *next;
}*head[max_table];

node* createNewNode(char *nama){
    node *newNode = (node*)malloc(sizeof(node));
    strcpy(newNode->nama, nama);
    newNode->next = NULL;
    return newNode;
}
int hash(char *nama){
    int key = 0;
    for(int i = 0 ; i < strlen(nama); i++){
        key += nama[i];
    }
    return key % max_table;
}

void push( char *nama){
    node *newNode = createNewNode(nama);
    //calculate hash key
    int pos = hash(nama);
    //push
    //headnya kosong
    if(head[pos] == NULL){
        head[pos] = newNode;
    }
    // ketika headnya ada(pushTail)
    else{
        node *temp = head[pos];
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }

}

void print(){
    for(int i = 0; i < max_table; i++){
        node *temp = head[i];
        printf("index %d:",i);
        while(temp != NULL){
            printf("%s -> ", temp->nama);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void pop(char *nama){
    int pos = hash(nama);
    //gaada head[pos]nya
    if(head[pos] == NULL){
        printf("GAADA BOS di hash table\n");
        return;
    }
    else{
        if(strcmp(head[pos]->nama, nama) == 0){
            node *temp = head[pos];
            head[pos] = temp->next;
            free(temp);
        }
        else{
            node *temp = head[pos];
            while(temp->next != NULL && strcmp(temp->next->nama, nama) != 0){
                temp = temp->next;
            } 
            if(temp->next == NULL){
                printf("GAADA BOS\n");
                return;
            }
            node *toPop = temp->next;
            temp->next = toPop->next;
            free(toPop);
        }
    }
}



int main(){
    push("Andi");
    push("Budi");
    push("Caca");
    push("Dedi");
    push("Euis");
    print();
    puts("");
    pop("Budi");
    print();
    return 0;
}
