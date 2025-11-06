#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue{
    QueueNode* front;
    QueueNode* rear;
} Queue;

QueueNode* init_QueueNode(int value, QueueNode* nextptr){
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = value;
    node->next = nextptr;
    return node;
}

void push(Queue* q, int value){
    if(q->front == NULL && q->rear == NULL){
        QueueNode* temp = init_QueueNode(value, NULL);
        q->front = temp;
        q->rear = temp;
        return;
    }
    QueueNode* temp = init_QueueNode(value, NULL);
    q->rear->next = temp;
    q->rear = temp;
}

void pop(Queue* q){
    if(q->front == NULL && q->rear == NULL){
        return ;
    }
    if(q->front == q->rear){
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
        return ;
    }

    QueueNode* temp = q->front;
    q->front = q->front->next;
    free(temp);
}

int front(Queue q) {
    return q.front->data;
}

bool isEmpty(Queue q){
    if(q.front == NULL && q.rear == NULL)
        return true;
    return false;
}

#endif