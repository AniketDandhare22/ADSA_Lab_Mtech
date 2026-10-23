#include<stdio.h>
#include <stdlib.h>

//binary Search tree (BST)
struct Tree{
    int data;
    struct Tree *left;
    struct Tree *right;
};

struct Tree *insert(struct Tree *root, struct Tree *node){
    if(root == NULL) return node;
    if(node->data < root->data)
        root->left = insert(root->left, node);
    else
        root->right = insert(root->right, node);
    return root;
}

struct Tree *deleteNode(struct Tree *root, int n){
    if(root == NULL) return NULL;

    if(n < root->data){
        root->left = deleteNode(root->left, n);
    } else if(n > root->data){
        root->right = deleteNode(root->right, n);
    } else {
        if(root->left == NULL){
            struct Tree *right = root->right;
            free(root);
            return right;
        }
        if(root->right == NULL){
            struct Tree *left = root->left;
            free(root);
            return left;
        }

        struct Tree *successor = root->right;
        while(successor->left != NULL)
            successor = successor->left;
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }
    return root;
}

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

void printTree(struct Tree *root, int parent, int isLeft, int isRoot){
    if (root == NULL) return;

    if (isRoot)
        printf("Root: %d\n", root->data);
    else
        printf("%d -> %s child: %d\n", parent,
               isLeft ? "left" : "right", root->data);

    printTree(root->left, root->data, 1, 0);
    printTree(root->right, root->data, 0, 0);
}

int main(){
    struct Tree *root = NULL;
    int arr[10]= {5,1,9,6,7,3,2,98,54,11};
    for(int i=0;i<10;i++){
        struct Tree *node = (struct Tree *)malloc(sizeof(struct Tree));
        node->data = arr[i];
        node->left = NULL;
        node->right = NULL;

        root = insert(root, node);
    }
    root = deleteNode(root,54);
    printf("Tree (sideways):\n");
    printTree(root, 0, 0, 1);
    printf("Print Inorder : ");
    inorder(root);
    printf("\nPrint preorder : ");
    preorder(root);
    printf("\nPrint postorder : ");
    postorder(root);
    printf("\n");
    return 0;
}