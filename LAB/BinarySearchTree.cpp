#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
	int id;
	char name[101];
	struct Student *left;
	struct Student *right;
};

//Student *searchStd(Student *curr, int id){
//	if(curr == NULL) return NULL;
//	else if(curr->id == id) return curr;	
//	else if(id < curr->id) return searchStd(curr->left, id);
//	else if(id > curr->id) return searchStd(curr->right, id);
//}

Student *createStudent(int id, char *name){
	Student *newStudent = (Student *)malloc(sizeof(Student));
	newStudent->id = id;
	strcpy(newStudent->name, name);
	newStudent->left = NULL;
	newStudent->right = NULL;
	return newStudent;
}

Student *insert(Student *root, int id, char *name){
//	Case 1: kalo tree belom kebuat, kita bikin root nodenya saja
	if(root == NULL){
		return createStudent(id, name);
	}
//	Case 2 : ID yang kita mau inser > current node punya ID
	else if(id > root->id){
		root->right = insert(root->right, id, name);
	}
//	Case 3 : ID yang kita mau insert < current node punya ID
	else if(id < root->id){
		root->left = insert(root->left, id, name);
	}
//	Case 4 : Kalo valuenya udah ada (duplicate), kita return nodenya saja
	return root;
}

void inorder(Student *root){
	if(root == NULL) return;
	inorder(root->left);
	printf("Student ID : %d, Name: %s\n", root->id, root->name);
	inorder(root->right);
}

void preorder(Student *root){
    if(root == NULL) return;
    printf("Student ID : %d, Name: %s\n", root->id, root->name);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Student *root){
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("Student ID : %d, Name: %s\n", root->id, root->name);
}

Student *search(Student *root, int id){
	// Case 1 : Kalo Search ga ketemu
	if(root == NULL){
		puts("Not Found!");
		return NULL;
	}
	
	// Case 2 : Kalo Search KETEMU
	if(root->id == id){
		puts("Found!");
		return root;
	}
	
	// Case 3 : kalo id yang mau di search itu lbh gede dr current id
	if(id > root->id){
		return search(root->right, id);
	}
	// Case 4 : kalo id yang mau di search itu lbh kecil dr current id
	else{
		return search(root->left, id);
	}
}

Student *update(Student *root, int id, char *newName){
	// Case 1 : Kalo Search ga ketemu
	if(root == NULL){
		puts("Not Found!");
		return NULL;
	}
	
	// Case 2 : Kalo Search KETEMU
	if(root->id == id){
		puts("Found!");
		strcpy(root->name, newName);
		return root;
	}
	
	// Case 3 : kalo id yang mau di search itu lbh gede dr current id
	if(id > root->id){
		return update(root->right, id, newName);
	}
	// Case 4 : kalo id yang mau di search itu lbh kecil dr current id
	else{
		return update(root->left, id, newName);
	}
}

Student *findSuccessor(Student *root){
	while(root->left){
		root = root->left;
	}
	return root;
}

Student *deleteStd(Student *root, int id){
	if(root == NULL){
		puts("Not Found!");
		return NULL;
	}	
	else if(id < root->id) root->left = deleteStd(root->left, id);
	else if(id > root->id) root->right = deleteStd(root->right, id);
	else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			return NULL;
		}	
		else if(root->right && root->left == NULL){
			Student *temp = root->right;
			free(root);
			return temp;
		}
		else if(root->left && root->right == NULL){
			Student *temp = root->left;
			free(root);
			return temp;
		}
		else{
			Student *successor = findSuccessor(root->right);
			root->id = successor->id;
			strcpy(root->name, successor->name);
			root->right = deleteStd(root->right, successor->id);
			
			return root;
		}
	}
	
	return root;
}

Student *deleteAll(Student *root){
	while(root){
		root = deleteStd(root, root->id);
	}

	return root;
}

int main(){
	
	Student *root = NULL;
	
	// Insertion
	puts("Inserting: ");
	root = insert(root, 100, "Louis");
    root = insert(root, 101, "Brandon");
    root = insert(root, 90, "Angeline");
    root = insert(root, 103, "Bryant");
    root = insert(root, 77, "Calvin");
    root = insert(root, 95, "Giselle");
    root = insert(root, 94, "Nathan");
    root = insert(root, 88, "Nw");
	puts("Insert Sucessfull!");
	
	// Traversal
	puts("\nInorder Traversal:");
	inorder(root);
	
	// Searching
	puts("\nSearching");
	Student *searchedStudent = search(root, 95);
	if(searchedStudent != NULL){
		printf("Found Student with id %d and name %s\n", searchedStudent->id, searchedStudent->name);
	}
	
	// Updating
	puts("\nUpdating");
	Student *updatedStudent = update(root, 3, "tommy");
	if(updatedStudent != NULL){
		printf("Updated Student with id %d, new Name is %s\n", updatedStudent->id, updatedStudent->name);
	}
	
	// Traversal
	puts("\nInorder Traversal:");
	inorder(root);
	
	puts("\nAfter delete:");
	
	root = deleteStd(root, 100);
	root = deleteStd(root, 95);
	
	inorder(root);

	root = deleteAll(root);
	puts("After delete all:");
	inorder(root);
	
	return 0;
}