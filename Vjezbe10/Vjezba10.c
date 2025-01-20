
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h> 
#include <stdlib.h>

typedef struct _node* Position;

typedef struct _node {
    int val;
    Position left;
    Position right;
}Node;

Position CreateNode(int value) {
    Position newNode = (Position)malloc(sizeof(Node));
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;

}

Position insert(Position root, int value) {
    if (root == NULL)
        return CreateNode(value);

    if (value > root->val)
        root->left = insert(root->left, value);
    if (value < root->val)
        root->right = insert(root->right, value);

    return root;
}

int inorder(Position root) {
    if (root) {
        inorder(root->left);
        printf(" %d", root->val);
        inorder(root->right);
    }
    return EXIT_SUCCESS;
}

Position find(Position root, int value) {
    if (root == NULL || root->val == value)
        return root;

    if (value < root->val)
        return find(root->left, value);
    else
        return find(root->right, value);
}


Position findMin(Position root) {
    while (root && root->left)
        root = root->left;
    return root;
}

Position delete(Position root, int value) {
    if (root == NULL)
        return root;

    if (value < root->val)
        root->left = delete(root->left, value);
    else if (value > root->val)
        root->right = delete(root->right, value);
    else {
        if (root->left == NULL) {
            Position temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Position temp = root->left;
            free(root);
            return temp;
        }

        Position temp = findMin(root->right);
        root->val = temp->val;
        root->right = delete(root->right, temp->val);
    }
    return root;
}



int generateRandomNumbers(Position root, int count) {
    srand((unsigned int)time(NULL)); // Inicijalizacija generatoraA
    for (int i = 0; i < count; i++) {
        int randomNumber = (rand() % 81) + 10; // Opseg <10, 90>
        root = insert(root, randomNumber);
    }
    return EXIT_SUCCESS;
}

int replace(Position root) {
    if (root == NULL)
        return 0;

    int leftSum = replace(root->left);  // Suma levog podstabla
    int rightSum = replace(root->right); // Suma desnog podstabla

    int currentVal = root->val;  // Čuvamo trenutnu vrednost pre zamene
    root->val = leftSum + rightSum;  // Zamenjujemo trenutnu vrednost

    return currentVal + root->val;  // Vraćamo sumu za roditelja
}
void writeInorderToFile(Position root, FILE* file) {
    if (root) {
        writeInorderToFile(root->left, file);
        fprintf(file, "%d ", root->val);
        writeInorderToFile(root->right, file);
    }
}
int main() {

    Position root = NULL;

    root = insert(root, 2);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 8);
    root = insert(root, 11);
    root = insert(root, 1);
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 7);



    printf("Inorder: ");
    inorder(root);
    printf("\n");

    replace(root);

    Position root1 = NULL;
    generateRandomNumbers(root1, 10);

    FILE* file = fopen("output.txt", "w");
    if (file) {
        writeInorderToFile(root, file);
        fclose(file);
    }
    else {
        printf("Greska pri otvaranju datoteke!\n");
    }

    return 0;
}
