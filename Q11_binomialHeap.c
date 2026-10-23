#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int key;
	int degree;
	struct Node *parent;
	struct Node *child;
	struct Node *sibling;
} Node;

static Node *heap = NULL;

static Node *create_node(int key) {
	Node *node = malloc(sizeof(*node));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	node->key = key;
	node->degree = 0;
	node->parent = NULL;
	node->child = NULL;
	node->sibling = NULL;
	return node;
}

static Node *merge_root_lists(Node *first, Node *second) {
	Node dummy = {0, 0, NULL, NULL, NULL};
	Node *tail = &dummy;

	while (first != NULL && second != NULL) {
		if (first->degree <= second->degree) {
			tail->sibling = first;
			first = first->sibling;
		} else {
			tail->sibling = second;
			second = second->sibling;
		}
		tail = tail->sibling;
	}
	tail->sibling = first != NULL ? first : second;
	return dummy.sibling;
}

static void link_trees(Node *child, Node *parent) {
	child->parent = parent;
	child->sibling = parent->child;
	parent->child = child;
	parent->degree++;
}

static Node *union_heaps(Node *first, Node *second) {
	Node *roots = merge_root_lists(first, second);
	if (roots == NULL) return NULL;

	Node *previous = NULL;
	Node *current = roots;
	Node *next = current->sibling;
	while (next != NULL) {
		if (current->degree != next->degree ||
			(next->sibling != NULL && next->sibling->degree == current->degree)) {
			previous = current;
			current = next; 
		} else if (current->key <= next->key) {
			current->sibling = next->sibling;
			link_trees(next, current);
		} else {
			if (previous == NULL) roots = next;
			else previous->sibling = next;
			link_trees(current, next);
			current = next;
		}
		next = current->sibling;
	}
	return roots;
}

static void insert_key(int key) {
	heap = union_heaps(heap, create_node(key));
}

static int extract_min(void) {
	Node *minimum = heap;
	Node *minimum_previous = NULL;
	Node *previous = NULL;

	for (Node *current = heap; current != NULL; current = current->sibling) {
		if (current->key < minimum->key) {
			minimum = current;
			minimum_previous = previous;
		}
		previous = current;
	}

	if (minimum_previous == NULL) heap = minimum->sibling;
	else minimum_previous->sibling = minimum->sibling;

	Node *children = minimum->child;
	Node *reversed_children = NULL;
	while (children != NULL) {
		Node *next = children->sibling;
		children->parent = NULL;
		children->sibling = reversed_children;
		reversed_children = children;
		children = next;
	}

	int result = minimum->key;
	free(minimum);
	heap = union_heaps(heap, reversed_children);
	return result;
}

static void display_tree(Node *node, const char *prefix, int is_last) {
	printf("%s%s%d\n", prefix, is_last ? "`-- " : "|-- ", node->key);

	size_t prefix_length = strlen(prefix);
	char *child_prefix = malloc(prefix_length + 5);
	if (child_prefix == NULL) {
		fprintf(stderr, "Unable to display tree: memory allocation failed.\n");
		return;
	}
	memcpy(child_prefix, prefix, prefix_length);
	memcpy(child_prefix + prefix_length, is_last ? "    " : "|   ", 5);

	for (Node *child = node->child; child != NULL; child = child->sibling)
		display_tree(child, child_prefix, child->sibling == NULL);
	free(child_prefix);
}

static void display_heap(Node *node) {
	while (node != NULL) {
		display_tree(node, "", node->sibling == NULL);
		node = node->sibling;
	}
}

static void free_heap(Node *node) {
	while (node != NULL) {
		Node *next = node->sibling;
		free_heap(node->child);
		free(node);
		node = next;
	}
}

int main(void) {
	int choice;
	int key;

	for (;;) {
		printf("\n1. Insert\n2. Extract minimum\n3. Display\n4. Exit\nChoice: ");
		if (scanf("%d", &choice) != 1) break;

		switch (choice) {
			case 1:
				printf("Key: ");
				if (scanf("%d", &key) != 1) {
					free_heap(heap);
					return 0;
				}
				insert_key(key);
				break;
			case 2:
				if (heap == NULL) printf("Heap is empty.\n");
				else printf("Minimum extracted: %d\n", extract_min());
				break;
			case 3:
				if (heap == NULL) printf("Heap is empty.\n");
				else display_heap(heap);
				break;
			case 4:
				free_heap(heap);
				return 0;
			default:
				printf("Invalid choice.\n");
		}
	}

	free_heap(heap);
	return 0;
}
