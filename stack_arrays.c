#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int stack[100];
int top = -1;

void push(int value){
    top++;
    stack[top] = value;
}

void display(){
    if(top == -1){
        printf("Stack Empty\n");
        return;
    }

    for(int i = top; i >= 0; i--)
        printf("%d ", stack[i]);

    printf("\n");
}

int main() {
    display();

    push(30);
    push(3);
    push(20);
    
    display();

    return 0;
}