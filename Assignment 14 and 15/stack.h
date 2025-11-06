#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct Stack{
    StackNode* top;
}Stack;

StackNode* init_StackNode(int value, StackNode* nextptr){
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = value;
    node->next = nextptr;
    return node;
}

void pushStack(Stack *s, int value){
    s->top = init_StackNode(value, s->top);
}

void popStack(Stack* s){
    if(s->top == NULL){
        return ;
    }
    StackNode* temp = s->top;
    s->top = temp->next;
    free(temp);
    return ;
}

int topStack(Stack s) {
    return s.top->data;
}

bool isEmptyStack(Stack s){
    if(s.top == NULL)
        return true;
    return false;
}

#endif