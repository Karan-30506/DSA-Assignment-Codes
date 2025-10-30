#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    char data;
    struct Node* next;
} Node;

typedef struct Stack{
    Node* top;
} Stack;

Node* init_Node(char value, Node* nextptr){
    Node* node = (Node*) malloc(sizeof(Node));
    if(node == NULL){
        printf("Malloc Failed\n");
        exit(1);
    }
    node->data = value;
    node->next = nextptr;
    return node;
}

void readInfixExp(char *infix){
    char *cp = infix;
    char ch;
    while((ch = getchar()) != EOF && ch != '\n' && infix - cp < 63){
        *infix++ = ch;
    }
    *infix = '\0';
}

int priority(char ch){
    switch(ch){
        case '^':
            return 3;
        case '*': case '/':
            return 2;
        case '+': case '-':
            return 1;
        default:
            return -1; 
    }
}

void push(Stack *s, char value){
    s->top = init_Node(value, s->top);
}

char pop(Stack* s){
    char item;
    if(s->top == NULL){
        printf("UnderFlow\nStack is Empty\n");
        return '\0';
    }
    Node* temp = s->top;
    item = temp->data;
    s->top = temp->next;
    free(temp);
    return item;
}

char top(Stack* s){
    char item;
    if(s->top == NULL){
        printf("UnderFlow\nStack is Empty\n");
        return '\0'; 
    }
    item = s->top->data;
    return item;
}

bool isEmpty(Stack s){
    if(s.top == NULL)
        return true;
    return false;
}

void Infix_to_Postfix(char* infix_exp, char* postfix_exp){
    Stack s;
    s.top = NULL;

    char *infix = infix_exp;
    char *postfix = postfix_exp;

    while(*infix){
        if(*infix == ' '){
            infix++;
            continue;
        }
        if((*infix >= 'a' && *infix <= 'z') || (*infix >= 'A' &&  *infix <= 'Z')){
            *postfix++ = *infix;
            *postfix++ = ' ';
        }
        else if((*infix >= '0' && *infix <= '9') || (*infix == '-' && (infix[1] >= '0' && infix[1] <= '9'))){
            while((*infix >= '0' && *infix <= '9') || *infix == '-'){
                *postfix = *infix;
                postfix++;
                infix++;
            }
            *postfix++ = ' ';
            continue;
        }
        else if(*infix == '('){
            push(&s, *infix);
        }
        else if(*infix == ')'){
            char poped;
            while((poped = pop(&s)) != '('){
                *postfix++ = poped;
                *postfix++ = ' ';
            }
        }
        else{
            while(!isEmpty(s) && priority(*infix) <= priority(top(&s))){
                char poped = pop(&s);
                *postfix++ = poped;
                *postfix++ = ' ';
            }
            push(&s, *infix);
        }
        infix++;
    }
    
    while(!isEmpty(s)){
        char poped = pop(&s);
        *postfix++ = poped;
        *postfix++ = ' ';
    }
    *postfix = '\0';
}

int main() {
    char infix_exp[64];
    char postfix_exp[64];
    
    printf("Enter the Infix Expression: ");
    readInfixExp(infix_exp);

    printf("\nGiven Infix Expression: %s\n", infix_exp);
    Infix_to_Postfix(infix_exp, postfix_exp);

    printf("\nPostfix Expression: %s\n", postfix_exp);
        
    return 0;
}