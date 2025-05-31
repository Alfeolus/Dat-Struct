#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int value;
    int height;
    node* left;
    node* right;
}*Node = NULL;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int max(int a, int b){
    return a > b ? a : b;
}

int height(node* root){
    if(root == NULL) return 0;
    return root->height;
}

int balanceFactor(node* root){
    if(root == NULL) return 0;
    return height(root->left) - height(root->right);
}

node* leftRotate(node* x){
    node* y = x->right;
    node* z = y->left;

    y->left = x;
    x->right = z;

    x->height = max(height(x->left), height(y->left)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
}
