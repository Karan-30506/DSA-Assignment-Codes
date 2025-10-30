#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* init_TreeNode(int value){
    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));
    if(!node){
        printf("Malloc Failed\n");
        exit(1);
    }
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Node Left Right
void preorderTraversal(TreeNode* node){
    if(!node)
        return;

    printf("%d ", node->data);

    preorderTraversal(node->left);

    preorderTraversal(node->right);    
}

// Left Node Right
void inorderTraversal(TreeNode* node){
    if(!node)
        return;

    inorderTraversal(node->left);

    printf("%d ", node->data);

    inorderTraversal(node->right);
}

// Left Right Node
void postorderTraversal(TreeNode* node){
    if(!node)
        return;
    
    postorderTraversal(node->left);

    postorderTraversal(node->right);

    printf("%d ", node->data);
}

int main() {
    // Tree 1
    TreeNode* root1 = init_TreeNode(1);
    root1->left = init_TreeNode(2);
    root1->right = init_TreeNode(3);
    root1->left->left = init_TreeNode(4);
    root1->left->right = init_TreeNode(5);
    root1->right->left = init_TreeNode(6);
    root1->right->right = init_TreeNode(7);

    // Tree 2
    TreeNode* root2 = init_TreeNode(34);
    root2->left = init_TreeNode(24);
    root2->right = init_TreeNode(30);
    root2->left->left = init_TreeNode(8);
    root2->left->right = init_TreeNode(9);
    root2->left->right->left = init_TreeNode(16);
    root2->left->right->right = init_TreeNode(14);
    root2->right->left = init_TreeNode(11);
    root2->right->right = init_TreeNode(56);
    root2->right->right->left = init_TreeNode(7);
    root2->right->right->right = init_TreeNode(22);
    
    printf("\nPreorder Recursive Traversal: ");
    preorderTraversal(root1);
    printf("\n\n");

    printf("Inorder Recursive Traversal: ");
    inorderTraversal(root1);
    printf("\n\n");

    printf("Postorder Recursive Traversal: ");
    postorderTraversal(root1);
    printf("\n\n");

    return 0;
}