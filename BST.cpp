#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
}node;

node* createNode(int value){
    node *c = (node*)malloc(sizeof(node));
    c->value = value;
    c->left = NULL;
    c->right = NULL;
    return c;
}

node *buildBST(node* root, int value){
    if(!root){
        return createNode(value);
    }
    if(value < root->value){
        root->left = buildBST(root->left, value);
    }
    else if(value > root->value){
        root->right = buildBST(root->right, value);
    }
    return root;
}

int search(node* root, int value){
    if(root == NULL){
        return -1;
    }

    if(root->value == value){
        return root->value;
    }
    else if(value <root->value){
        return search(root->left, value);
    }
    else if(value > root->value){
        return search(root->right, value);
    }

    
}

void Inorder(node* root){
    if(root == NULL){
        return;
    }
    Inorder(root->left);
    printf("%d ", root->value);
    Inorder(root->right);
}

node* delnode(node* root, int value){
    if(root == NULL){
        return root;
    }
    if(value < root->value){
        root->left = delnode(root->left, value);
    }
    else if(value > root->value){
       root->right = delnode(root->right, value);
    }
    else{
        if(root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }
        else if(root->left == NULL){
            node* temp = root->right;
            root->value = temp->value;
            root->right = NULL;
            free(temp);
        }
        else if(root->right == NULL){
            node* temp = root->right;
            root->value = temp->value;
            root->left = NULL;
            free(temp);
        }
        else{
            node* temp = root->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            root->value = temp->value;
            root->left = delnode(root->left, temp->value);
        }
}
    return root;
}

int main(){
    node* root = NULL;
    root = buildBST(root, 6);
    root = buildBST(root, 10);
    root = buildBST(root, 3);
    // printf("%d\n", root->value);

    int val = search(root, 10);
    // printf("%d\n", val);
    Inorder(root);
    delnode(root, 10);
    printf("\n");
    Inorder(root);
    return 0;
}