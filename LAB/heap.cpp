#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_SIZE 100

int heap[MAX_HEAP_SIZE];
int heapSize = 0;

int left(int n){
    return 2 * n + 1;
}

int right(int n){
    return 2 * n + 2;
}

int parent(int n){
    return (n - 1) / 2;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int val){
    if(heapSize == MAX_HEAP_SIZE){
        printf("Heap already full\n");
        return;
    }
    int i = heapSize++;
    heap[i] = val;

    while (i != 0 && heap[parent(i)] > heap[i]){
        swap(&heap[parent(i)], &heap[i]);
        i = parent(i);
    }
}

void printHeapAsArray(){
    for(int i = 0; i < heapSize; i++){
        printf("%d -> ", heap[i]);
    }
    printf("\n");
}

int popHeap(){
    if(heapSize == 0){
        printf("Heap is empty\n");
        return -1;
    }
    
    int toPop = heap[0];
    
    heap[0] = heap[--heapSize];
    
    int i = 0;
    while (left(i) < heapSize) {
        int t = left(i);
        if (right(i) < heapSize && heap[right(i)] < heap[left(i)]) {
            t = right(i);
        }
        if (heap[t] < heap[i]) {
            swap(&heap[t], &heap[i]);
            i = t;
        }
        else{
            break;
        }
       
    }
    
    return toPop;
}

void printHeapAsTree(int i, int depth){
    if(i>= heapSize) return;
    
    printHeapAsTree(right(i), depth + 1);
    for(int j = 0; j < depth; j++) {
        printf("    ");
    }
    printf("%d\n", heap[i]);
    printHeapAsTree(left(i), depth + 1);
}

int main(){
    // heap
    insert(9);
    printHeapAsArray();
    insert(19);
    printHeapAsArray();
    insert(36);
    printHeapAsArray();
    insert(8);
    printHeapAsArray();
    insert(10);
    printHeapAsArray();
    insert(12);
    printHeapAsArray();
    insert(5);
    printHeapAsArray();

    puts("====================");
    printHeapAsTree(0, 0);
    puts("====================");

    printf("pop: %d\n", popHeap());

    return 0;
}