#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct Stack{
    Node* top;
} Stack;

Node* init_Node(int value, Node* nextptr){
    Node* node = (Node*) malloc(sizeof(Node));
    if(node == NULL){
        printf("Malloc Failed\n");
        exit(1);
    }
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
        return '\0';
    }
    Node* temp = s->top;
    item = temp->data;
    s->top = temp->next;
    free(temp);
    return item;
}

int top(Stack* s){
    int item;
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

int sizeOfStack(Stack s){
    int count = 0;
    if(s.top == NULL)
        return count;
    Node* temp = s.top;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
}

void readPostfixExp(char *postfix){
    char *cp = postfix;
    char ch;

    while((ch = getchar()) != EOF && ch != '\n' && postfix - cp < 63){
        *postfix = ch;
        postfix++;
    }
    *postfix = '\0';
}

bool isNumeric(char *str){
    if(*str == '-' && strlen(str) == 1){
        return false;
    }
    bool isnum = true;
    while(*str){
        if((*str < '0' || *str > '9') && (*str != '-'))
            isnum = false;
        str++;
    }
    return isnum;
}

bool isOperation(char *str){
    if(strcmp(str, "+") == 0)
        return true;
    if(strcmp(str, "-") == 0)
        return true; 
    if(strcmp(str, "*") == 0)
        return true;
    if(strcmp(str, "/") == 0)
        return true;
    if(strcmp(str, "^") == 0)
        return true; 
    return false;   
}

int power(int base, int exp){
    int result = 1;
    while(exp > 0){
        if(exp % 2){
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

void evaluatePostfix(Stack* result, char* postfix){
    char *token;
    int answer, opr1, opr2;
    
    token = strtok(postfix, " ");

    while(token != NULL){
        if(isNumeric(token)){
            push(result, atoi(token));
        }
        else if(isOperation(token)){
            if(sizeOfStack(*result) < 2){
                printf("Number of Operands are Less than Operations\n");
                exit(1);
            }
            if(strcmp(token, "+") == 0){
                opr2 = pop(result);
                opr1 = pop(result);
                push(result, opr1 + opr2);
            }
            else if(strcmp(token, "-") == 0){
                opr2 = pop(result);
                opr1 = pop(result);
                push(result, opr1 - opr2);
            }
            else if(strcmp(token, "*") == 0){
                opr2 = pop(result);
                opr1 = pop(result);
                push(result, opr1 * opr2);
            }
            else if(strcmp(token, "/") == 0){
                opr2 = pop(result);
                opr1 = pop(result);
                push(result, opr1 / opr2);
            }
            else if(strcmp(token, "^") == 0){
                opr2 = pop(result);
                opr1 = pop(result);
                push(result, power(opr1, opr2));
            }
        }
        else{
            printf("Invalid Token found in Postfix Expression\nEvaluation Failed\n");
            exit(1);
        }
        token = strtok(NULL, " ");
    }
}

int main() {
    Stack result;
    result.top = NULL;
    char postfix_exp[64];

    printf("Enter the Postfix Expression (Space Separated): ");
    readPostfixExp(postfix_exp);

    printf("\nGiven Postfix Expression: %s\n", postfix_exp);
    evaluatePostfix(&result, postfix_exp);

    printf("\nResult: %d\n", top(&result));

    return 0;
}