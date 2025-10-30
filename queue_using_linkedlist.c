#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* front;
    Node* rear;
} Queue;

Node* init_Node(int value, Node* nextptr){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = nextptr;
    return node;
}

void add(Queue* q, int value){
    if(q->front == NULL && q->rear == NULL){
        Node* temp = init_Node(value, NULL);
        q->front = temp;
        q->rear = temp;
        return;
    }
    Node* temp = init_Node(value, NULL);
    q->rear->next = temp;
    q->rear = temp;
}

int Remove(Queue* q){
    if(q->front == NULL && q->rear == NULL){
        printf("UnderFlow\nQueue is Empty\n");
        return INT_MIN;
    }
    if(q->front == q->rear){
        int item = q->front->data;
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
        return item;
    }

    Node* temp = q->front;
    int item = temp->data;
    q->front = q->front->next;
    free(temp);
    return item;
}

bool isEmpty(Queue q){
    if(q.front == NULL && q.rear == NULL)
        return true;
    return false;
}

void displayQueue(Queue q){
    printf("----------------\n");
    printf("Current Queue:- \n");
    if(q.front == NULL && q.rear == NULL){
        printf("Queue is Empty\n");
        printf("----------------\n");
        return;
    }
    printf("\n(Front) <-- ");
    Node* temp = q.front;
    while(temp){
        printf("%d --> ", temp->data);
        temp = temp->next;
    }
    printf("(Rear)\n");
    printf("----------------\n");
}

int main() {
    Queue q;
    q.front = NULL;
    q.rear = NULL; // initializes an empty queue

    int user_choice = 0, value, item;

    printf("Select an Operation\n");
    printf("1) Add an Element to the Queue\n");
    printf("2) Remove an Element to the Queue\n");
    printf("3) Check if the Queue is Empty\n");
    printf("4) Exit the Program\n");

    while(printf("\nEnter Your Choice: ") && (scanf("%d", &user_choice)) == 1){
        switch(user_choice){
            case 1:
                printf("\nEnter the Value to Insert: ");
                scanf("%d", &value);

                add(&q, value);
                displayQueue(q);
                break;
            case 2: 
                item = Remove(&q);
                if(item == INT_MIN){
                    break;
                }
                printf("\nDeleted Item: %d\n", item);
                displayQueue(q);
                break;
            case 3:
                if(!isEmpty(q)){
                    printf("\nQueue is Not Empty\n");
                }
                else{
                    printf("\nQueue is Empty\n");
                }
                break;
            case 4:
                printf("\nProgram Terminated\n");
                exit(0);
            default:
                printf("\nInvalid Input\n");
                break;
        }
    }
    return 0;
}