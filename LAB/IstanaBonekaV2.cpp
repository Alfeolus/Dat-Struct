#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    char name[25];
    char ticket[15];
    struct Node *prev, *next;
} *head, *tail;

void enqueue(char *name, char *ticket){
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->ticket, ticket);
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (!head) {
        head = tail = newNode;
        return;
    }
    
    Node *temp = head;
    
    if(strcmp(ticket, "FAST_TRACK") == 0){	
	    while(temp->next && strcmp(temp->next->ticket, "REGULER") != 0){
	        temp = temp->next;
	    }
	    newNode->next = temp->next;
	    temp->next = newNode;
	    newNode->prev = temp;
	    temp = newNode->next;
	    temp->prev = newNode;
	}else{
		while(temp->next){
	        temp = temp->next;
	    }
    	temp->next = newNode;
    	newNode->prev = temp;
	}
	   
    

//    if(!temp){
//        queue.tail->next = newNode;                                              
//        newNode->prev = queue.tail;
//        queue.tail = newNode;
//    }else{
//        newNode->next = temp;
//        newNode->prev = temp->prev;
//        if(temp->prev) temp->prev->next = newNode;
//        else queue.head = newNode;
//        temp->prev = newNode;
//    }
}

void dequeue(){
    int count = 0;
    Node *temp = head;
    while(temp && count < 4){
        printf("%s ", temp->name);
        Node *toDelete = temp;
        temp = temp->next;
        free(toDelete);
        count++;
    }
    printf("Get into the boat\n");
    head = temp;
    if(head) head->prev = NULL;
    else tail = NULL; 
    
    int remaining = 0;
    temp = head;
    while(temp){
        remaining++;
        temp = temp->next;
    }
    printf("%d queues remaining\n", remaining);
}

void removeVisitor(char *name){
    Node *temp = head;
    while(temp){
        if(strcmp(temp->name, name) == 0){
            if(temp->prev) temp->prev->next = temp->next;
            else head = temp->next;
            
            if(temp->next) temp->next->prev = temp->prev;
            else tail   = temp->prev;
            
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

void displayQueue(){
    Node *temp = head;
    int index = 1;
    printf("No Name Ticket\n");
    while(temp){
        printf("%d  %s %s\n", index++, temp->name, temp->ticket);
        temp = temp->next;
    }
    if(!head){
        printf("There is no queue remaining\n");
    }
}


int main(){
    char command[15];
    int n;
    
    while(1){
        scanf("%s", command);
        if(strcmp(command, "REGISTER") == 0){
            scanf("%d", &n);
            for(int i = 0; i < n; i++){
                char name[25], ticket[20];
                scanf("%s %s", name, ticket);
                enqueue(name, ticket);
            }
            displayQueue();
        }else if(strcmp(command, "CALL") == 0){
            dequeue();
        }else if(strcmp(command, "REMOVE") == 0){
            scanf("%d", &n);
            for(int i = 0; i < n; i++){
                char name[25];
                scanf("%s", name);
                removeVisitor(name);
            }
            displayQueue();
        }else if(strcmp(command, "EXIT") == 0){
            break;
        }
    }
    return 0;
}