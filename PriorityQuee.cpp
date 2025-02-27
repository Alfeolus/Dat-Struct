#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Data{
	char name[20];
	int age, prio;
	struct Data *next;
}*h, *t, *c;

void enqueue(char pName[], int pAge, int pPrio){
	c = (struct Data*) malloc(sizeof (struct Data));
	strcpy(c->name, pName);
	c->age = pAge;
	c->prio = pPrio;
	
	c->next = NULL;
	
	if(!h){
		h=t=c;
	}else if(h->prio > pPrio){
		c->next = h;
		h = c;
	}else{
		struct Data *temp;
		temp = h;
		while(temp->next && temp->next->prio <= pPrio){
			temp = temp->next;
		}
		c->next =  temp->next;
		temp->next = c;
	}
}

//void dequeue(){
//	if(t == NULL) return;
//	
//	struct Data *temp = h;
//	while(strcmp(temp->next->name, t->name)){
//		temp = temp->next;
//	}
//	t = temp;
//	struct Data *curr;
//	curr = temp->next;
//	temp->next=NULL;
//	free(curr);	
//}

void dequeue(){
	if(h == NULL) return;
	struct Data *temp = h;
	
	h = h->next;
	free(temp);
}

void print(){
	struct Data *temp;
	temp = h;
	int i = 1;
	while(temp != NULL){
		
		printf("%d. Nama: %s, Umur: %d, Status: %d\n", i, temp->name,
		temp->age, temp->prio);
		i++;
		temp = temp->next;
	}
	puts("");
}

int main(){
	enqueue("Rizki", 33, 3);
	enqueue("Richard", 26, 3);
	enqueue("Andi", 16, 1);
	enqueue("Nur", 74, 2);
	enqueue("Coki", 66, 3);
	
	print();
	dequeue();
	print();
	dequeue();
	print();
	dequeue();
	print();

	return 0;
}

