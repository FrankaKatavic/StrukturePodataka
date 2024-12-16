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

}

Position insert(Position root, int value) {
	if (root = NULL)
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
		printf("%d",root->val);
		inorder(root->right);
	}
	return EXIT_SUCCESS;
}

int preorder(Position root) {
	if (root) {
		printf("%d", root->val);
		preorder(root->left);
		preorder(root->right);
	}
	return EXIT_SUCCESS;
}

int postorder(Position root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d", root->val);
	}
	return EXIT_SUCCESS;
}
