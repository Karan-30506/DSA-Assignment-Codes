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

typedef struct Stack{
    Node* top;
}Stack;

Node* init_Node(int value, Node* nextptr){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = nextptr;
    return node;
}

void push(Stack *s, int value){
    s->top = init_Node(value, s->top);
}

int pop(Stack* s){
    int item;
    if(s->top == NULL){
        printf("UnderFlow\nStack is Empty\n");
        return INT_MIN;
    }
    Node* temp = s->top;
    item = temp->data;
    s->top = temp->next;
    free(temp);
    return item;
}

bool isEmpty(Stack s){
    if(s.top == NULL)
        return true;
    return false;
}

void displayStack(Stack s){
    printf("----------------\n");
    printf("Current Stack:- \n");
    if(s.top == NULL){
        printf("Stack is Empty\n");
        printf("----------------\n");
        return;
    }
    Node* temp = s.top;
    printf("%d   <-- TOP\n", temp->data);
    temp= temp->next;
    while(temp){
        printf("%d\n", temp->data);
        temp = temp->next;
    }
    printf("----------------\n");
}

int main() {
    Stack s;
    s.top = NULL; // initializes an empty stack

    int user_choice = 0;
    int value, item;

    printf("Select the Operation:- \n");
    printf("1) Push Operation\n");
    printf("2) Pop Operation\n");
    printf("3) Check if the Stack is Empty\n");
    printf("4) Exit the Program\n");

    while(printf("\nEnter Your Choice: ") && (scanf("%d", &user_choice)) == 1){
        switch(user_choice){
            case 1:
                printf("\nEnter the Value you want to Insert: ");
                scanf("%d", &value);

                push(&s, value);
                displayStack(s);
                break;
            case 2:
                item = pop(&s);
                if(item == INT_MIN)
                    break;
                printf("\nDeleted Item: %d\n", item);
                displayStack(s);
                break;
            case 3:
                if(!isEmpty(s)){
                    printf("\nStack is not Empty\n");
                }
                else{
                    printf("\nStack is Empty\n");
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