#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
int id;
int exam_pass;
int c_grade;
int achievements;
int value;
int height;
struct Student *left;
struct Student *right;
};

int findValue(int exam_pass, int c_grade){
    if(exam_pass == 0 && c_grade == 1) return 0;
    if(exam_pass == 0 && c_grade == 0) return 1;
    if(exam_pass == 1 && c_grade == 1) return 2;
    if(exam_pass == 1 && c_grade == 0) return 3;
    return -1;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(Student *node){
    if(node == NULL) return 0;
    return node->height;
}

Student* createNode(int id, int exam_pass, int c_grade, int achievements){
    Student* newNode = (Student*)malloc(sizeof(Student));
    newNode->id = id;
    newNode->exam_pass = exam_pass;
    newNode->c_grade = c_grade;
    newNode->achievements = achievements;
    newNode->value = findValue(exam_pass, c_grade);
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Student* rightRotate(Student* x){
    Student* y  = x->left;
    Student* z = y->right;


    y->right = x;
    x->left = z;

    x->height = max(height(x->left), height(x->right));
    y->height = max(height(y->left), height(y->right));
    return y;
}

Student* leftRotate(Student* x){
    Student* y = x->right;
    Student* z = y->left;

    y->left = x;
    x->right = z;

    x->height = max(height(x->left), height(x->right));
    y->height = max(height(y->left), height(y->right));
    return y;
}

int balanceFactor(Student* node){
    if(node == NULL)return 0;
    return height(node->left) - height(node->right);
}

Student* insertAVL(Student* root, Student* newNode){
    if(root == NULL) return newNode;
    else if(newNode->value < root->value) {
        root->left = insertAVL(root->left, newNode);
    } else if(newNode->value > root->value) {
        root->right = insertAVL(root->right, newNode);
    } else {
    root->right = insertAVL(root->right, newNode);
}

    root->height = max(height(root->left), height(root->right)) +1;
    int balance = balanceFactor(root);

    if(balance > 1){
        if(balanceFactor(root->left)>= 0){
            return rightRotate(root);
        }
        else{
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if(balance < -1){
        if(balanceFactor(root->right) <= 0){
            return leftRotate(root);
        }

        else{
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

Student* deleteAVL(Student* root, int id){
    if(root == NULL) return NULL;

    if(root->id == id){
        if(root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        else if(root->left == NULL || root->right == NULL){
            Student* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            Student* temp = root->left;
            while(temp->right){
                temp = temp->right;
            }

            root->id = temp->id;
            root->exam_pass = temp->exam_pass;
            root->c_grade = temp->c_grade;
            root->achievements = temp->achievements;
            root->value = temp->value;
            root->left = deleteAVL(root->left, temp->id);
        }
    } else {
        root->left = deleteAVL(root->left, id);
        root->right = deleteAVL(root->right, id);
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = balanceFactor(root);
    
    if(balance > 1){
        if(balanceFactor(root->left)>= 0){
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if(balance < -1){
        if(balanceFactor(root->right) <= 0){
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}


Student* insert(Student* root, int id, int exam_pass, int c_grade, int achievements){
    Student* newNode = createNode(id, exam_pass, c_grade, achievements);
    return insertAVL(root, newNode);

}


int traversal(Student* root, int count, int result[]) {
    if (root == NULL || count >= 3) return count;
    count = traversal(root->left, count, result);
    if (count < 3) {
        result[count] = root->id;
        count++;
    }
    count = traversal(root->left, count, result);
    return count;
}


// void postOrder(Student* node, int* count, int* result) {
//     if(node == NULL || *count >= 3) return;
    
// }

int main(){
    int n;
    scanf("%d", &n);
    Student* root = NULL;
    for(int i = 0; i < n; i++){
        char operation;
        scanf(" %c", &operation);
        if(operation == 'i'){
            int id, exam_pass, c_grade, achievements;
            scanf("%d %d %d %d", &id, &exam_pass, &c_grade, &achievements);
            root = insert(root, id, exam_pass, c_grade, achievements);
        }
        else if(operation == 'd'){
            int id;
            scanf("%d", &id);
            root = deleteAVL(root, id);
        }
    }
    int result[3];
    int count = traversal(root, 0, result);
    for (int i = 0; i < count; i++) {
    printf("%d ", result[i]);
}
printf("\n");
return 0;

}