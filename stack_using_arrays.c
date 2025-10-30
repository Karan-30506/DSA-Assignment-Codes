#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

int stack[100];
int top = -1;

void push(int value){
    if(top == 99){
        printf("Overflow\nStack is Full\n");
        return;
    }

    stack[++top] = value;
}

int pop(){
    if(top == -1){
        printf("Underflow\nStack is Empty\n");
        return INT_MIN;
    }
    int item = stack[top--];
    return item;
}

bool isEmpty(){
    if(top == -1)
        return true;
    return false;
}

void displayStack(){
    printf("----------------\n");
    printf("Current Stack:- \n");
    if(top == -1){
        printf("Stack is Empty\n");
        printf("----------------\n");
        return;
    }
    int temp = top;
    printf("%d   <-- TOP\n", stack[temp--]);
    while(temp >= 0){
        printf("%d\n", stack[temp]);
        temp--;
    }
    printf("----------------\n");
}

int main() {
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

                push(value);
                displayStack();
                break;
            case 2:
                item = pop();
                if(item == INT_MIN)
                    break;
                printf("\nDeleted Item: %d\n", item);
                displayStack();
                break;
            case 3:
                if(!isEmpty()){
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