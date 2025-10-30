#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int queue[100];
int front = -1;
int rear = -1;
int currSize = 0;
int maxSize = 100;

void add(int value){
    if(currSize == maxSize){
        printf("OverFlow\nQueue is FULL\n");
        return;
    }
    else if(currSize == 0){
        front = 0;
        rear = 0;
    }
    else{
        rear = (rear + 1) % maxSize;
    }
    queue[rear] = value;
    currSize++;
}

int Remove(){
    int item;
    if(currSize == 0){
        printf("UnderFlow\nQueue is Empty\n");
        return INT_MIN;
    }
    item = queue[front];
    if(currSize == 1){
        front = -1;
        rear = -1;
    }
    else{
        front = (front + 1) % maxSize;
    }
    currSize--;
    return item;
}

bool isEmpty(){
    if(currSize == 0)
        return true;
    return false;
}

void displayQueue(){
    printf("----------------\n");
    printf("Current Queue:- \n");
    if(currSize == 0){
        printf("Queue is Empty\n");
        printf("----------------\n");
        return;
    }
    int temp = rear;
    for(int i = 0; i < currSize; i++){
        if(temp == -1)
            temp = 99;
        if(temp == front && temp == rear){
            printf("%d  <-- Front & Rear\n", queue[temp]);
        } else if(temp == front){
            printf("%d  <-- Front\n", queue[temp]);
        } else if(temp == rear){
            printf("%d  <-- Rear\n", queue[temp]);
        } else {
            printf("%d\n", queue[temp]);
        }
        temp = (temp - 1) % maxSize;
    }
    printf("----------------\n");
}

int main() {
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

                add(value);
                displayQueue();
                break;
            case 2: 
                item = Remove();
                if(item == INT_MIN){
                    break;
                }
                printf("\nDeleted Item: %d\n", item);
                displayQueue();
                break;
            case 3:
                if(!isEmpty()){
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