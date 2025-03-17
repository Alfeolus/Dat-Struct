#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    int height;
    node *left;
    node *right;
};

node *createNode(int val){
    node *c = (node*)malloc(sizeof(node));
    c->val = val;
    c->height = 1;
    c->left = c->right = NULL;
    return c;
}

int height(node *root){
    if(root == NULL){
        return 0;
    }else{
        return root->height;
    }
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int getBalance(node *root){
    if(root == NULL){
        return 0;
    }else{
        return height(root->left) - height(root->right);
    }
}

node *leftRotate(node *x){
    node *y = x->right;
    node *T2 = y->left;

    x->right = T2;
    y->left = x;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

node *rightRotate(node *y){
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return x;
}

node *insert(node *root, int val){
    if(root == NULL){
        return createNode(val);
    }else if(val < root->val){
        root->left = insert(root->left, val);
    }else if(val > root->val){
        root->right = insert(root->right, val);
    }else{
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if(balance < -1 && val > root->right->val){
        // left rotation
        return leftRotate(root);
    }

    if(balance > 1 && val < root->left->val){
        // right rotation
        return rightRotate(root);
    }

    if(balance < -1 && val < root->right->val){
        // right left rotation
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    if(balance > 1 && val > root->left->val){
        // left right rotation
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
}

void inorder(node *root){
    if (root != NULL){
        inorder(root->left);
        printf("%d\n", root->val);
        inorder(root->right);
    }
    return;
}
int main(){
    node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, 20);

    inorder(root);

    return 0;
}