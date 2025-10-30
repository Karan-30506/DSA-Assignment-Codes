#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

typedef struct StackNode{
    TreeNode* node;
    struct StackNode* next;
} StackNode;

typedef struct Stack{
    StackNode* top;
} Stack;

StackNode* init_StackNode(TreeNode* value, StackNode* nextptr){
    StackNode* node = (StackNode*) malloc(sizeof(StackNode));
    node->node = value;
    node->next = nextptr;
    return node;
}

void push(Stack *s, TreeNode* node){
    s->top = init_StackNode(node, s->top);
}

void pop(Stack* s){
    if(!s->top)
        return;
    
    StackNode* temp = s->top;
    s->top = s->top->next;
    free(temp);
}

TreeNode* top(Stack s){
    return s.top->node;
}

bool isEmpty(Stack s){
    return s.top == NULL;
}

int size(Stack s){
    if(!s.top)
        return 0;

    int count = 0;
    StackNode* temp = s.top;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
}

void preorderTraversal(TreeNode* root){
    if(!root)
        return;

    Stack nodes;
    nodes.top = NULL;
    TreeNode* temp = root;

    push(&nodes, temp);
    while(!isEmpty(nodes)){
        temp = top(nodes);
        pop(&nodes);

        printf("%d ", temp->data);

        if(temp->right)
            push(&nodes, temp->right);

        if(temp->left)
            push(&nodes, temp->left);
    }
}

void inorderTraversal(TreeNode* root){
    if(!root)
        return;

    Stack nodes;
    nodes.top = NULL;
    TreeNode* temp = root;

    while(true){
        if(temp){
            push(&nodes, temp);
            temp = temp->left;
        }
        else{
            if(isEmpty(nodes))
                break;
            temp = top(nodes);
            pop(&nodes);
            printf("%d ", temp->data);
            temp = temp->right;
        }
    }
}

void postorderTraversal(TreeNode* root){
    if(!root)
        return;

    Stack nodes, final;
    nodes.top = NULL, final.top = NULL;

    TreeNode* temp = root;
    push(&nodes, temp);

    while(!isEmpty(nodes)){
        temp = top(nodes);
        pop(&nodes);

        push(&final, temp);

        if(temp->left)
            push(&nodes, temp->left);
        
        if(temp->right)
            push(&nodes, temp->right);
    }

    while(!isEmpty(final)){
        printf("%d ", top(final)->data);
        pop(&final);
    }
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

    printf("\nPreorder Iterative Traversal: ");
    preorderTraversal(root1);
    printf("\n\n");

    printf("Inorder Iterative Traversal: ");
    inorderTraversal(root1);
    printf("\n\n");

    printf("Postorder Iterative Traversal: ");
    postorderTraversal(root1);
    printf("\n\n");

    return 0;
}