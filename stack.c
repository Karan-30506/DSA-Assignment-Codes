#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct stack{
    Node* top;
}stack;

Node* initNode(int value, Node* nextptr){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = nextptr;
    return node;
}

void displayStack(stack* s){
    Node *temp = s->top;
    while(temp){
        printf(" %d -->", temp->data);
        temp = temp->next;
    }
    printf("(NULL)\n");
}

void push(stack *s, int value){
    Node* temp = initNode(value, NULL);
    temp->next = s->top;
    s->top = temp;
}

int pop(stack *s){
    int item = 0;
    if(s->top == NULL){
        printf("underflow\n");
        exit(1);
    }
    Node* temp = s->top;
    s->top = s->top->next;
    item = temp->data;
    free(temp);
    return item;
}

bool empty(stack *s){
    if(s->top == NULL)
        return true;
    return false;
}

int main() {
    stack s;
    s.top = NULL;

    printf("%d\n", empty(&s));
    
    push(&s, 30);
    push(&s, 11);
    push(&s, 24);
    displayStack(&s);
    
    printf("%d\n", pop(&s));
    displayStack(&s);
    printf("%d\n", empty(&s));
    return 0;
}