#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	int height;
	struct Node *left;
	struct Node *right;
} Node;

static int max(int a, int b) {
	return a > b ? a : b;
}

static int height(const Node *node) {
	return node == NULL ? 0 : node->height;
}

static int balanceFactor(const Node *node) {
	return node == NULL ? 0 : height(node->left) - height(node->right);
}

static Node *createNode(int key) {
	Node *node = (Node *)malloc(sizeof(*node));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	node->key = key;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

static Node *rotateRight(Node *root) {
	Node *newRoot = root->left;
	Node *subtree = newRoot->right;
	newRoot->right = root;
	root->left = subtree;
	root->height = 1 + max(height(root->left), height(root->right));
	newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
	return newRoot;
}

static Node *rotateLeft(Node *root) {
	Node *newRoot = root->right;
	Node *subtree = newRoot->left;
	newRoot->left = root;
	root->right = subtree;
	root->height = 1 + max(height(root->left), height(root->right));
	newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));
	return newRoot;
}

static Node *insertNode(Node *root, int key) {
	if (root == NULL)
		return createNode(key);

	if (key < root->key)
		root->left = insertNode(root->left, key);
	else if (key > root->key)
		root->right = insertNode(root->right, key);
	else
		return root; 

	root->height = 1 + max(height(root->left), height(root->right));
	int balance = balanceFactor(root);

	if (balance > 1 && key < root->left->key)
		return rotateRight(root);
	if (balance < -1 && key > root->right->key)
		return rotateLeft(root); 
	if (balance > 1 && key > root->left->key) { 
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if (balance < -1 && key < root->right->key) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

static Node *minimumNode(Node *root) {
	while (root->left != NULL)
		root = root->left;
	return root;
}

static Node *deleteNode(Node *root, int key) {
	if (root == NULL)
		return NULL;

	if (key < root->key) {
		root->left = deleteNode(root->left, key);
	} else if (key > root->key) {
		root->right = deleteNode(root->right, key);
	} else {
		if (root->left == NULL || root->right == NULL) {
			Node *child = root->left != NULL ? root->left : root->right;
			free(root);
			return child;
		}
		Node *successor = minimumNode(root->right);
		root->key = successor->key;
		root->right = deleteNode(root->right, successor->key);
	}

	root->height = 1 + max(height(root->left), height(root->right));
	int balance = balanceFactor(root);

	if (balance > 1 && balanceFactor(root->left) >= 0)
		return rotateRight(root); 
	if (balance > 1 && balanceFactor(root->left) < 0) { 
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	if (balance < -1 && balanceFactor(root->right) <= 0)
		return rotateLeft(root); 
	if (balance < -1 && balanceFactor(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

static void preorder(const Node *root) {
	if (root != NULL) {
		printf("%d ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

static void inorder(const Node *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

static void postorder(const Node *root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->key);
	}
}

static void freeTree(Node *root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

int main(void) {
	Node *root = NULL;
	int values[] = {-1,10, 20, 30, 40, 50, 25};
	int valueCount = (int)(sizeof(values) / sizeof(values[0]));
	for (int i = 0; i < valueCount; i++)
		root = insertNode(root, values[i]);

	printf("Preorder: ");
	preorder(root);
	printf("\nInorder: ");
	inorder(root);
	printf("\nPostorder: ");
	postorder(root);
	printf("\n");

	freeTree(root);
	return 0;
}
