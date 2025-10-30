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

typedef struct QueueNode{
    TreeNode* node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue{
    QueueNode* front;
    QueueNode* rear;
} Queue;

QueueNode* init_QueueNode(TreeNode* value, QueueNode* nextptr){
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->node = value;
    node->next = nextptr;
    return node;
}

void push(Queue* q, TreeNode* node){
    if(q->front == NULL && q->rear == NULL){
        QueueNode* temp = init_QueueNode(node, NULL);
        q->front = temp;
        q->rear = temp;
        return;
    }
    QueueNode* temp = init_QueueNode(node, NULL);
    q->rear->next = temp;
    q->rear = temp;
}

void pop(Queue* q){
    if(q->front == NULL && q->rear == NULL){
        return;
    }
    if(q->front == q->rear){
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
        return;
    }

    QueueNode* temp = q->front;
    q->front = q->front->next;
    free(temp);
}

bool isEmpty(Queue q){
    if(q.front == NULL && q.rear == NULL)
        return true;
    return false;
}

TreeNode* front(Queue q){
    return q.front->node;
}

int size(Queue q){
    if(q.front == NULL && q.rear == NULL)
        return 0;

    int count = 0;
    QueueNode* temp = q.front;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
}

void bubbleSort(int *a, int lena){
    bool swap = false;
    for(int i = 0; i < lena - 1; i++){

        for(int j = 0; j < lena - i - 1; j++){
            if(a[j] > a[j+1]){
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                swap = true;
            }
        }
        if(!swap)
            break;
    }
}

TreeNode* insertNode(int *a, int left, int right){
    if(left > right)
        return NULL;

    int midID = (right - left) / 2 + left;

    TreeNode* node = init_TreeNode(a[midID]);
    node->left = insertNode(a, left, midID - 1);
    node->right = insertNode(a, midID + 1, right);

    return node;
}

TreeNode* convertArraytoBST(int* a, int lena){
    return insertNode(a, 0, lena - 1);
}

TreeNode* insertInBST(TreeNode* root, int key){
    if(!root)
        return init_TreeNode(key);
    TreeNode* temp = root;
    while(temp){
        if(key < temp->data){
            if(temp->left)
                temp = temp->left;
            else{
                temp->left = init_TreeNode(key);
                break;
            }
        }
        else{
            if(temp->right)
                temp = temp->right;
            else{
                temp->right = init_TreeNode(key);
                break;
            }
        }
    }
    return root;
}

TreeNode* findLastRight(TreeNode* node){
    if(!node->right)
        return node;
    return findLastRight(node->right);
}

TreeNode* helperDelete(TreeNode* node){
    if(!node->left)
        return node->right;
    if(!node->right)
        return node->left;

    TreeNode* rightChild = node->right;
    TreeNode* lastRight = findLastRight(node->left);
    lastRight->right = rightChild;
    return node->left;
}

TreeNode* deleteInBST(TreeNode* root, int key){
    if(!root)
        return NULL;

    if(root->data == key){
        return helperDelete(root); // returns new root of BST
    }

    TreeNode* temp = root;
    while(temp){
        if(key < temp->data){
            if(temp->left && temp->left->data == key){
                temp->left = helperDelete(temp->left);
                break;
            }
            else{
                temp = temp->left;
            }
        }
        else{
            if(temp->right && temp->right->data == key){
                temp->right = helperDelete(temp->right);
                break;
            }
            else{
                temp = temp->right;
            }
        }
    }
    return root;
}

bool isLeaf(TreeNode* node){
    return node->left == NULL && node->right == NULL;
}

void helperLeaf(TreeNode* root, int* leaf, int* leaflen, int *nonleaf, int* nonleaflen){
    if(!root)
        return;

    if(isLeaf(root)){
        leaf[*leaflen] = root->data;
        *leaflen += 1;
    }
    else{
        nonleaf[*nonleaflen] = root->data;
        *nonleaflen += 1;
    }
    helperLeaf(root->left, leaf, leaflen, nonleaf, nonleaflen);
    helperLeaf(root->right, leaf, leaflen, nonleaf, nonleaflen);
}

void printLeafNodes(int* leaf, int leaflen){
    printf("\nLeaf Nodes: ");
    for(int i = 0; i < leaflen; i++)
        printf("%d ", leaf[i]);
    printf("\n");
}

void printNonLeafNodes(int* nonleaf, int nonleaflen){
    printf("\nNon-Leaf Nodes: ");
    for(int i = 0; i < nonleaflen; i++)
        printf("%d ", nonleaf[i]);
    printf("\n");
}

void levelOrderTraversal(TreeNode* root){
    if(!root)
        return;

    TreeNode* temp = root;
    Queue nodes;
    nodes.front = NULL;
    nodes.rear = NULL;
    int lvl = 0;

    push(&nodes, temp);
    while(!isEmpty(nodes)){
        int lennodes = size(nodes);
        printf("Level %d: ", lvl);
        for(int i= 0; i < lennodes; i++){
            temp = front(nodes);
            pop(&nodes);
    
            if(temp->left)
                push(&nodes, temp->left);
            if(temp->right)
                push(&nodes, temp->right);

            printf("%d ", temp->data);
        }
        lvl++;
        printf("\n");        
    }
}

void preoderTraversal(TreeNode* root){
    if(!root)
        return;

    printf("%d ", root->data);

    preoderTraversal(root->left);

    preoderTraversal(root->right);
}

int main() {
    int leaf[64], nonleaf[64];
    int leaflen = 0, nonleaflen = 0;

    // Initialize a sample binary search tree from an array of integers
    TreeNode* root = NULL;
    int a[] = {7, 8, 4, 2, 30, 16, 13, 9, 41, 33, 59, 60, 52, 47, 50};
    int lena = sizeof(a) / sizeof(a[0]);

    bubbleSort(a, lena);

    root = convertArraytoBST(a, lena);

    printf("\nPreorder Treaversal of Given BST\n");
    preoderTraversal(root);
    printf("\n");

    int user_choice = 0, value = 0;

    printf("\nSelect the Operation: \n");
    printf("\n1) Insert an Item into BST\n");
    printf("2) Delete an Item from BST\n");
    printf("3) Print Leaf & Non-Leaf nodes of the BST\n");
    printf("4) Print Nodes aat each level of the BST\n");
    printf("5) Exit the Program\n");

    while(printf("\nEnter your Choice: ") && (scanf("%d", &user_choice) == 1)){
        switch(user_choice){
            case 1:
                printf("\nPreorder of BST: ");
                preoderTraversal(root);
                printf("\n\nEnter the value you want to Insert: ");
                scanf("%d", &value);
                root = insertInBST(root, value);
                printf("\nPreorder of Updated BST: ");
                preoderTraversal(root);
                printf("\n");
                break;
            case 2:
                printf("\nPreorder of BST: ");
                preoderTraversal(root);
                printf("\n\nEnter the value you want to Delete: ");
                scanf("%d", &value);
                root = deleteInBST(root, value);
                printf("\nPreorder of Updated BST: ");
                preoderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("\nPreorder of BST: ");
                preoderTraversal(root);
                printf("\n");
                helperLeaf(root, leaf, &leaflen, nonleaf, &nonleaflen);

                printLeafNodes(leaf, leaflen);
                printNonLeafNodes(nonleaf, nonleaflen);
                break;
            case 4:
                printf("\nLevel Order Traversal:\n");
                levelOrderTraversal(root);
                break;
            case 5:
                printf("Program Treminated...\n");
                exit(0);
            default:
                printf("Invalid Input\n");
                break;
        }
    }
    return 0;
}