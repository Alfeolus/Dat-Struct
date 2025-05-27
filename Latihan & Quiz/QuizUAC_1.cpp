#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    int exam_pass;
    int have_c_grade;
    int international_achievements;
};

int calc_value(int exam_pass, int have_c_grade) {
    if (exam_pass == 0 && have_c_grade == 1) return 0;
    if (exam_pass == 0 && have_c_grade == 0) return 1;
    if (exam_pass == 1 && have_c_grade == 1) return 2;
    if (exam_pass == 1 && have_c_grade == 0) return 3;
    return -1;
}

struct AVLNode {
    Student data;
    int value;
    int height;
    AVLNode *left, *right;
};

int max(int a, int b) { return a > b ? a : b; }
int height(AVLNode *node) { return node ? node->height : 0; }

AVLNode* create_node(Student s) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = s;
    node->value = calc_value(s.exam_pass, s.have_c_grade);
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

AVLNode* right_rotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* left_rotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int get_balance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Compare for AVL: higher value, then higher international achievements, then higher ID
int compare_students(Student a, Student b) {
    int va = calc_value(a.exam_pass, a.have_c_grade);
    int vb = calc_value(b.exam_pass, b.have_c_grade);
    if (va != vb) return va - vb;
    if (a.international_achievements != b.international_achievements)
        return a.international_achievements - b.international_achievements;
    return a.id - b.id;
}

// Insert by priority
AVLNode* insert(AVLNode* node, Student s) {
    if (!node) return create_node(s);

    if (s.id == node->data.id) return node; // No duplicate IDs

    int cmp = compare_students(s, node->data);
    if (cmp > 0)
        node->right = insert(node->right, s);
    else
        node->left = insert(node->left, s);

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = get_balance(node);

    // Balancing
    if (balance > 1 && compare_students(s, node->left->data) < 0)
        return right_rotate(node);
    if (balance < -1 && compare_students(s, node->right->data) > 0)
        return left_rotate(node);
    if (balance > 1 && compare_students(s, node->left->data) > 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance < -1 && compare_students(s, node->right->data) < 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

// Find minimum node (for deletion)
AVLNode* min_value_node(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// Delete by ID
AVLNode* delete_node(AVLNode* root, int id) {
    if (!root) return root;
    if (id < root->data.id)
        root->left = delete_node(root->left, id);
    else if (id > root->data.id)
        root->right = delete_node(root->right, id);
    else {
        // Node found
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            AVLNode* temp = min_value_node(root->right);
            root->data = temp->data;
            root->value = temp->value;
            root->right = delete_node(root->right, temp->data.id);
        }
    }
    if (!root) return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = get_balance(root);

    // Balancing
    if (balance > 1 && get_balance(root->left) >= 0)
        return right_rotate(root);
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0)
        return left_rotate(root);
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    return root;
}

// Collect top 3 students (reverse in-order traversal)
void collect_top3(AVLNode* root, int* count, int* result) {
    if (!root || *count >= 3) return;
    collect_top3(root->right, count, result);
    if (*count < 3) {
        result[*count] = root->data.id;
        (*count)++;
    }
    collect_top3(root->right, count, result);
}

int main() {
    int n;
    scanf("%d", &n);
    AVLNode* root = NULL;
    for (int i = 0; i < n; ++i) {
        char op;
        scanf(" %c", &op);
        if (op == 'i') {
            Student s;
            scanf("%d %d %d %d", &s.id, &s.exam_pass, &s.have_c_grade, &s.international_achievements);
            root = insert(root, s);
        } else if (op == 'd') {
            int id;
            scanf("%d", &id);
            root = delete_node(root, id);
        }
    }
    int count = 0, result[3] = {0};
    collect_top3(root, &count, result);
    for (int i = 0; i < count; ++i) {
        if (i > 0) printf(" ");
        printf("%d", result[i]);
    }
    printf("\n");
    return 0;
}