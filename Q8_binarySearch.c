#include<stdio.h>
#include <stdlib.h>

// binary search tree
struct Tree{
    int data;
    struct Tree *left;
    struct Tree *right;
};

void inorder(struct Tree *root){
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Tree *root){
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Tree *root){
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

struct Tree *minValueNode(struct Tree *node){
    struct Tree *current = node;
    while (current != NULL && current->left != NULL)
        current = current->left;
    return current;
}

void insert(struct Tree **root, int value){
    if (*root == NULL){
        *root = (struct Tree *)malloc(sizeof(struct Tree));
        if (*root == NULL){
            printf("Memory allocation failed\n");
            exit(1);
        }
        (*root)->data = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }

    if (value < (*root)->data)
        insert(&((*root)->left), value);
    else if (value > (*root)->data)
        insert(&((*root)->right), value);
}

void deleteNode(struct Tree **root, int key){
    if (*root == NULL)
        return;

    if (key < (*root)->data)
        deleteNode(&((*root)->left), key);
    else if (key > (*root)->data)
        deleteNode(&((*root)->right), key);
    else{
        if ((*root)->left == NULL && (*root)->right == NULL){
            free(*root);
            *root = NULL;
        }
        else if ((*root)->left == NULL){
            struct Tree *temp = *root;
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL){
            struct Tree *temp = *root;
            *root = (*root)->left;
            free(temp);
        }
        else{
            struct Tree *temp = minValueNode((*root)->right);
            (*root)->data = temp->data;
            deleteNode(&((*root)->right), temp->data);
        }
    }
}

int main(){
    struct Tree *root = NULL;

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 12);
    insert(&root, 18);
    insert(&root, 1);
    insert(&root, 4);

    printf("Print Inorder traversal for given tree : ");
    inorder(root);
    printf("\nPrint preorder traversal for given tree : ");
    preorder(root);
    printf("\nPrint postorder traversal for given tree : ");
    postorder(root);

    deleteNode(&root, 5);
    printf("\nAfter deleting 5, Inorder traversal : ");
    inorder(root);
    printf("\n");
    return 0;
}