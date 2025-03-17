#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct ticket{
    int type;
    char name[100], type_name[100];
    ticket *next;
    ticket *prev;
}*h, *t;

ticket *create_node(char nama[], char type[]){
    ticket *current = (ticket*) malloc (sizeof(ticket));
    current->type = strcmp(type, "FAST_TRACK") == 0 ? 1 : 2;
    strcpy(current->type_name, type);
    strcpy(current->name, nama);
    current->next = current->prev = NULL;

    return current;
}

void print_ticket(){
    if (!h){
        puts("No Entry"); return;
    }
    ticket* temp = h;
    for (int i = 1; temp != NULL ; i++){
        printf("%d. %-15s %s\n", i, temp->name, temp->type_name);
        temp = temp->next;
    }
}

void push(char nama[], char type[]){
    ticket *c = create_node(nama, type);
    if (!h) h = t = c;
    else if (c->type == 1){
        if (h->type == 2){
            c->next = h; h->prev = c;
            h = c;
        }else if (t->type == 1){
            t->next = c; c->prev = t;
            t = c;
        }else{
            ticket* temp = h;
            while (temp->next->type == 1) temp = temp->next;
            c->next = temp->next; c->prev = temp;
            temp->next->prev = c; temp->next = c;
        }
    }else{
        t->next = c; c->prev = t;
        t = c;
    }
}


void remove(char nama[]){
    if (!h){
        puts("No Entry"); return;
    }
    ticket* temp = h;
    if (strcmp(h->name, nama) == 0) {
        temp = h;
        h = h->next;
        h->prev = NULL;
    }else if (strcmp(t->name, nama) == 0){
        temp = t;
        t = t->prev;
        t->next = NULL;
    }
    else{
        while (strcmp(temp->name, nama) != 0 && temp->next != NULL) temp = temp->next;
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
    } 
    free(temp);
}

int call(){
    if (!h){
        puts("No Entry"); return 0;
    }
    for (int i = 1 ; i <= 4 ; i++){
        ticket* temp = h;
        printf("%s ", h->name);
        if (h->next == NULL) return i;
        h = h->next; h->prev = NULL;
        free(temp);
    }

    return 4;
}


int main(){
    char system[10], nama[10], type[15];
    int total, poeple = 0;
    while (1){
        scanf("%s", system);getchar();
        if (strcmp(system, "REGISTER") == 0){
            scanf("%d", &total);getchar();
            for (int i = 0 ; i < total ; i++){
                scanf("%s %s", nama, type);getchar();
                push(nama, type);
                poeple++;
            }
            print_ticket();
        }else if (strcmp(system, "REMOVE") == 0){
            scanf("%d", &total);getchar();
            for (int i = 0 ; i < total ; i++){
                scanf("%s", nama);getchar();
                remove(nama);
                poeple--;
            }
            print_ticket();
        }else if (strcmp(system, "CALL") == 0){
            poeple -= call();
            puts("got into the boat");
            printf("%d remaining\n", poeple);
        }
    }
}