#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//jumlah vertex = 5
#define max 5

void createMatrix(int matrix[][max], int vertices){
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            matrix[i][j] = 0; // awal2 0 karena gada jalur
        }
    }
}

void addEdgeMatrix(int matrix[][max], int src, int dst){
    matrix[src][dst] = 1; // kalo ada jalur ditandain 1
    matrix[dst][src] = 1; // karena undirected graph -> kalo A bisa ke B, B juga bisa ke A

}

void bfsMatrix(int matrix[][max], int vertices, int start){
    //Step 1: initialize visited array
    bool visited[max]; // array untuk menandai vertex yang sudah dikunjungi

    for(int i = 0; i < vertices; i++){
        visited[i] = false; // semua vertex belum dikunjungi
    }
    //Step 2: create a queue
    int queue[100]; 
    int front = 0; //depan queue
    int rear = 0; // belakang queuenya

    //Step 3: mark the starting vertex as visited and enqueue it
    visited[start] = true; // tandain udah dikunjungi
    queue[rear++] = start; // masukin ke queue

    // looping untuk BFS
    while(front < rear){ //selama masi ada node di dalam queue = ga bakal sama
        int currentVertex = queue[front++];
        printf("%d ", currentVertex); // print node yang diambil dari queue

        // explore vertex tersebut punya neighbors
        for(int i = 0; i < vertices; i++){
            if(matrix[currentVertex][i] == 1 && !visited[i]){ // kalo ada jalur ke vertex i dan belum dikunjungi
                queue[rear++] = i; // masukin ke queue
                visited[i] = true; // tandain udah dikunjungi
            }
        }
    }
    
}

void dfsMatrix(int matrix[][max], int vertices, int start){
    bool visited[vertices];
    for(int i = 0; i < vertices; i++){
        visited[i] = false; // di awal, belum ada vertex yang di visit
    }

    int stack[100], top = -1; // stack untuk DFS
    stack[++top] = start; // push starting vertex ke stack
    while(top >= 0){
        int currentVertex = stack[top--]; // pop vertex dari stack
        if(!visited[currentVertex]){
            printf("%d ", currentVertex); // print vertex yang di pop
            visited[currentVertex] = true; // tandain udah dikunjungi
        }

        // explore neighbors
        for(int i = vertices - 1; i >= 0; i--){
            if(matrix[currentVertex][i] == 1 && !visited[i]){
                stack[++top] = i; // push neighbor ke stack
            }
        }
    }
    printf("\n");
}

void printMatrix(int matrix[][max], int vertices){
    for(int i = 0; i < vertices; i++){
        for(int j = 0; j < vertices; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int vertices = max;
    int matrix[max][max];

    createMatrix(matrix, vertices);

    addEdgeMatrix(matrix, 0, 1);
    addEdgeMatrix(matrix, 0, 2);
    addEdgeMatrix(matrix, 1, 2);
    addEdgeMatrix(matrix, 1, 3);
    addEdgeMatrix(matrix, 2, 4);
    printMatrix(matrix, vertices);

    printf("BFS Traversal starting from vertex 0:\n");
    bfsMatrix(matrix, vertices, 0);

    printf("\nDFS Traversal starting from vertex 0:\n");
    dfsMatrix(matrix, vertices, 0);
    
}