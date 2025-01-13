#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
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

	if (value < root->val)
		root->left = insert(root->left, value);
	if (value > root->val)
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

int preorder(Position root) {
	if (root) {
		printf(" %d", root->val);
		preorder(root->left);
		preorder(root->right);
	}
	return EXIT_SUCCESS;
}

int postorder(Position root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf(" %d", root->val);
	}
	return EXIT_SUCCESS;
}

void levelOrder(Position root) {
    if (root == NULL)
        return;

    Position queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Position current = queue[front++];
        printf(" %d ", current->val);

        if (current->left)
            queue[rear++] = current->left;
        if (current->right)
            queue[rear++] = current->right;
    }
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

int main() {
    
    Position root = NULL;

    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 15);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 7);
    root = insert(root, 9);

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Level Order: ");
    levelOrder(root);
    printf("\n");

    root = delete(root, 2); // Moraš ažurirati root nakon brisanja

    printf("Level Order after deletion: ");
    levelOrder(root);
    printf("\n");

    return 0;
}
