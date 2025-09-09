#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// In this Implementation the Linked List is Initialized with Sample Data
// But my Code also works with an empty Linked List
// Initialise an Empty Linked List by changing head to NULL in main function

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* init_Node(int data, Node *nextptr){
    Node *node = (Node*) malloc(sizeof(Node));
    if(node == NULL){
        printf("Malloc Failed\n");
        exit(1);
    }
    node->data = data;
    node->next = nextptr;
    return node;
}

Node* convertArrtoLL(int *a, int lena){
    if(lena == 0){
        Node *head = NULL;
        return head;
    }
    Node *head = init_Node(a[0], NULL);
    Node *mover = head;

    for(int i = 1; i < lena; i++){
        Node *temp = init_Node(a[i], NULL);
        mover->next = temp;
        mover = temp;
    }
    return head;
}

void TraverseLL(Node *head){
    Node *temp = head;
    while(temp){
        printf(" %d -->", temp->data);
        temp = temp->next;
    }
    printf("(NULL)\n");
}

int LengthofLL(Node* head){
    int count = 0;
    Node *temp = head;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
}

Node* giveRandomNode(Node *head){
    if(LengthofLL(head) == 0){
        printf("Linked List is Empty so a random Node couldn't be selected\n");
        exit(1);
    }
    srand(time(NULL));
    int ran_num = rand() % LengthofLL(head) + 1;

    int count = 1;

    Node *temp = head;

    while(temp){
        if(count == ran_num)
            return temp;
        temp = temp->next;
        count++;
    }
}

Node* insertAtBeginning(Node *head, int value){
    return init_Node(value, head);
}

void insertAfterNode(Node* gnode, int value){
    Node* toInsert = init_Node(value, gnode->next);
    gnode->next = toInsert;
}

Node* deleteFromBeginning(Node* head){
    if(head == NULL){
        printf("Linked List is Empty\n");
        return head;
    }
    Node *newHead = head->next;
    free(head);
    return newHead;
}

void deleteAfterNode(Node *gnode){
    if(gnode->next == NULL){
        printf("Given Node is the Last Node\n");
        printf("Deletion Failed\n");
        return;
    }
    Node* toDelete = gnode->next;
    gnode->next = toDelete->next;
    free(toDelete);
}

int main() {
    int sample_data[] = {30, 24, 7, 31, 9, 16, 100};
    int len = sizeof(sample_data) / sizeof(sample_data[0]);

    // Sample data in Linked List
    Node* head = NULL;
    printf("Given Linked List:- ");
    TraverseLL(head);

    int value = 0;
    // the functions to insert and delete after a node take the address of a Node
    // so the giveRandomNode() functions simulates as if the user is giving the address of a random node 
    Node *ran_node = NULL;

    printf("\nChoose an Operation To Perform:-\n");
    printf("1) Traverse and print the Elements of the Linked List\n");
    printf("2) Insert an Element at the Beginning of the LL\n");
    printf("3) Insert an Element after a given Node in th LL\n");
    printf("4) Delete an Element in the Beginning of the LL\n");
    printf("5) Delete an Element after a given Node in the LL\n");
    printf("6) Print the Length of the Linked List\n");
    printf("7) Exit the Program\n");

    int user_choice = 0;
    while(printf("\nEnter Your Choice: ") && (scanf("%d", &user_choice) == 1)){
        switch(user_choice){
            case 1:
                printf("\nLinked List:- ");
                TraverseLL(head);
                break;
            case 2:
                value = 0;
                printf("\nEnter the Value to Insert: ");
                scanf("%d", &value);
                head = insertAtBeginning(head, value);
                printf("\nUpdated LL:- ");
                TraverseLL(head);
                break;
            case 3:
                printf("\nLinked List: ");
                TraverseLL(head);
                ran_node = giveRandomNode(head);
                printf("Given random Node with data = %d\n", ran_node->data);
                value = 0;
                printf("\nEnter the Value to Insert: ");
                scanf("%d", &value);
                insertAfterNode(ran_node, value);
                printf("\nUpdated LL:- ");
                TraverseLL(head);
                break;
            case 4:
                head = deleteFromBeginning(head);
                printf("\nUpdated LL:- ");
                TraverseLL(head);
                break;
            case 5:
                printf("\nLinked List: ");
                TraverseLL(head);
                ran_node = giveRandomNode(head);
                printf("Given random Node with data = %d\n", ran_node->data);
                deleteAfterNode(ran_node);
                printf("\nUpdated LL:- ");
                TraverseLL(head);
                break;
            case 6:
                printf("\nThe Length of the Linked List is: %d\n", LengthofLL(head));
                break;
            case 7:
                printf("\nProgram Terminated\n");
                exit(0);
            default:
                printf("\nInvalid Input\n");
                break;
        }
    }
    return 0;
}