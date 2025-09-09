#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// In this Implementation the Linked List is Initialized with Sample Data
// But my Code also works with an empty Linked List
// Initialise an Empty Linked List by changing head to NULL in main() function :)

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* init_Node(int value, Node* nextptr){
    Node *node = (Node*) malloc(sizeof(Node));
    if(node == NULL){
        printf("Malloc Failed\n");
        exit(1);
    }
    node->data = value;
    node->next = nextptr;
    return node;
}

Node* convertArrtoCirLL(int *a, int len){
    if(len == 0){
        Node *head = NULL;
        return head;
    }
    Node* head = init_Node(a[0], NULL);
    Node* mover = head;

    for(int i = 1; i < len; i++){
        Node* temp = init_Node(a[i], NULL);
        mover->next = temp;
        mover = temp;
    }

    // to make the List circular
    mover->next = head;

    return head;
}

void TraverseCirLL(Node* head){
    Node* temp = head;
    if(head == NULL){
        printf("(NULL)\n");
        return;
    }

    do{
        printf(" %d -->", temp->data);
        temp = temp->next;
    }while(temp != head);

    printf("(Head)\n");
}

int LengthofCirLL(Node* head){
    if(head == NULL){
        return 0;
    }
    Node* temp = head;
    int count = 0;
    do{
        count++;
        temp = temp->next;
    }while(temp != head);
    return count;
}

Node* giveRandomNode(Node* head){
    if(LengthofCirLL(head) == 0){
        printf("List is Empty\n");
        printf("A Random Node couldn't be selected\n");
        exit(1);
    }
    srand(time(NULL));
    int rand_num = rand() % LengthofCirLL(head) + 1;
    int count = 0;
    Node* temp = head;
    do{
        count++;
        if(count == rand_num){
            return temp;
        }
        temp = temp->next;
    }while(temp != head);
}

Node* insertAtBeginning(Node* head, int value){
    if(head == NULL){
        Node* newHead = init_Node(value, NULL);
        newHead->next = newHead;
        return newHead;
    }
    Node* newHead = init_Node(value, NULL);
    Node* temp = head;

    while(temp->next != head){
        temp = temp->next;
    }
    temp->next = newHead;
    newHead->next = head;
    return newHead;
}

void insertAfterNode(Node *gnode, int value){
    Node* toInsert = init_Node(value, gnode->next);
    gnode->next = toInsert;
}

Node* deleteFromBeginning(Node* head){
    if(head == NULL){
        printf("List is Empty\n");
        return head;
    }
    if(head->next == head){
        Node* toDelete = head;
        free(toDelete);
        return NULL;
    }
    Node* toDelete = head;
    Node* newHead = head->next;
    Node* temp = head;

    while(temp->next != head){
        temp = temp->next;
    }
    temp->next = newHead;
    free(toDelete);
    return newHead;
}

Node* deleteAfterNode(Node* head, Node* gnode){
    if(head->next == head){
        printf("List contains only one Node\n");
        return head;
    }
    if(gnode->next == head){
        Node* toDelete = gnode->next;
        Node* newHead = toDelete->next;
        gnode->next = newHead;
        free(toDelete);
        return newHead;
    }
    Node* toDelete = gnode->next;
    gnode->next = toDelete->next;
    free(toDelete);
    return head;
}

int main() {
    int sample_data[] = {30, 24, 7, 31, 9, 16, 100, 45, 67, 89, 23, 56};
    int len = sizeof(sample_data) / sizeof(sample_data[0]);

    // Sample data in Linked List
    Node* head = convertArrtoCirLL(sample_data, len);
    printf("Linked List: ");
    TraverseCirLL(head);

    int value = 0;
    // the functions to insert and delete after a node take the address of a Node
    // so the giveRandomNode() functions simulates as if the user is giving the address of a random node 
    Node* ran_node = NULL;

    printf("\nChoose an Operation To Perform:-\n");
    printf("1) Traverse and print the Elements of the Linked List\n");
    printf("2) Insert an Element at the Beginning of the LL\n");
    printf("3) Insert an Element after a given Node in the LL\n");
    printf("4) Delete an Element in the Beginning of the LL\n");
    printf("5) Delete an Element after a given Node in the LL\n");
    printf("6) Print the Length of the Linked List\n");
    printf("7) Exit the Program\n");

    int user_choice = 0;
    while(printf("\nEnter Your Choice: ") && scanf("%d", &user_choice) == 1){
        switch(user_choice){
            case 1:
                printf("\nLinked List:- ");
                TraverseCirLL(head);
                break;
            case 2:
                value = 0;
                printf("\nEnter the Value to Insert: ");
                scanf("%d", &value);
                head = insertAtBeginning(head, value);
                printf("\nUpdated LL:- ");
                TraverseCirLL(head);
                break;
            case 3:
                printf("\nLinked List: ");
                TraverseCirLL(head);
                ran_node = giveRandomNode(head);
                printf("Given random Node with data = %d\n", ran_node->data);
                value = 0;
                printf("\nEnter the Value to Insert: ");
                scanf("%d", &value);
                insertAfterNode(ran_node, value);
                printf("\nUpdated LL:- ");
                TraverseCirLL(head);
                break;
            case 4:
                head = deleteFromBeginning(head);
                printf("\nUpdated LL:- ");
                TraverseCirLL(head);
                break;
            case 5:
                printf("\nLinked List: ");
                TraverseCirLL(head);
                ran_node = giveRandomNode(head);
                printf("Given random Node with data = %d\n", ran_node->data);
                head = deleteAfterNode(head, ran_node);
                printf("\nUpdated LL:- ");
                TraverseCirLL(head);
                break;
            case 6:
                printf("\nThe Length of the Linked List is: %d\n", LengthofCirLL(head));
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