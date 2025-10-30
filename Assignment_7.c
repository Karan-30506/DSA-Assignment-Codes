#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int coef;
    int power;
    struct Node* next;
} Node;

Node* init_Node(int coef, int power, Node* nextptr){
    Node *node = (Node*) malloc(sizeof(Node));
    if(node == NULL){
        printf("Malloc Failed\n");
        exit(1);
    }
    node->coef = coef;
    node->power = power;
    node->next = nextptr;
    return node;
}

Node* insertPolynomial(int degree){
    int coef, power;

    printf("Enter the Elements of the Polynomial in the form:\nCoef  Power\n");
    scanf("%d %d", &coef, &power);

    Node* poly = init_Node(coef, power, NULL);
    Node* mover = poly;

    for(int i = 1; i <= degree; i++){
        scanf("%d %d", &coef, &power);
        Node* temp = init_Node(coef, power, NULL);
        mover->next = temp;
        mover = temp;
    }
    mover->next = NULL;

    return poly;
}

void sortPolynomial(Node *head, int degree){

    Node* temp1 = head;
    Node* temp2 = head;

    for(int i = 0; i < degree; i++){
        temp1 = head;
        temp2 = temp1->next;

        while(temp2){
            if(temp1->power < temp2->power){
                int temp = temp1->power;
                temp1->power = temp2->power;
                temp2->power = temp;

                temp = temp1->coef;
                temp1->coef = temp2->coef;
                temp2->coef = temp;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
}

void displayPolynomial(Node* poly){
    Node* temp = poly;

    while(temp->next){
        if(temp == poly && temp->coef != 0){
            printf("%dx^%d ", temp->coef, temp->power);
        }
        else{
            if(temp->coef > 0)
                printf("+ %dx^%d ", temp->coef, temp->power);
            else if(temp->coef < 0)
                printf("- %dx^%d ", abs(temp->coef), temp->power);
        }
        temp = temp->next;
    }
    // power = 0
    if(temp->coef > 0)
        printf("+ %d = 0\n", temp->coef);
    else if(temp->coef < 0)
        printf("- %d = 0\n", abs(temp->coef));
    else
        printf("= 0\n");
}

Node* addPolynomials(Node* poly1, Node* poly2){
    Node* p1 = poly1;
    Node* p2 = poly2;

    Node* resHead = NULL;
    Node* mover = resHead;

    while(p1 && p2){
        Node* temp = NULL;

        if(p1->power == p2->power){
            int sum = p1->coef + p2->coef;
            if(sum != 0){
                temp = init_Node(sum, p1->power, NULL);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->power < p2->power){
            temp = init_Node(p2->coef, p2->power, NULL);
            p2 = p2->next;
        }
        else{
            temp = init_Node(p1->coef, p1->power, NULL);
            p1 = p1->next;
        }

        if(temp != NULL){
            if(resHead == NULL){
                resHead = temp;
                mover = resHead;
            }
            else{
                mover->next = temp;
                mover = temp;
            }
        }
    }

    while(p1){
        Node* temp = init_Node(p1->coef, p1->power, NULL);
        if(resHead == NULL){
            resHead = temp;
            mover = resHead;
        }
        else{
            mover->next = temp;
            mover = temp;
        }
        p1 = p1->next;
    }

    while(p2){
        Node* temp = init_Node(p2->coef, p2->power, NULL);
        if(resHead == NULL){
            resHead = temp;
            mover = resHead;
        }
        else{
            mover->next = temp;
            mover = temp;
        }
        p2 = p2->next;
    }

    return resHead;
}

Node* subPolynomials(Node* poly1, Node* poly2){
    Node* p1 = poly1;
    Node* p2 = poly2;

    Node* resHead = NULL;
    Node* mover = resHead;

    while(p1 && p2){
        Node* temp = NULL;

        if(p1->power == p2->power){
            int sub = p1->coef - p2->coef;
            if(sub != 0){
                temp = init_Node(sub, p1->power, NULL);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->power < p2->power){
            temp = init_Node(-1 * p2->coef, p2->power, NULL);
            p2 = p2->next;
        }
        else{
            temp = init_Node(p1->coef, p1->power, NULL);
            p1 = p1->next;
        }

        if(temp != NULL){
            if(resHead == NULL){
                resHead = temp;
                mover = resHead;
            }
            else{
                mover->next = temp;
                mover = temp;
            }
        }
    }

    while(p1){
        Node* temp = init_Node(p1->coef, p1->power, NULL);
        if(resHead == NULL){
            resHead = temp;
            mover = resHead;
        }
        else{
            mover->next = temp;
            mover = temp;
        }
        p1 = p1->next;
    }

    while(p2){
        Node* temp = init_Node(-1 * p2->coef, p2->power, NULL);
        if(resHead == NULL){
            resHead = temp;
            mover = resHead;
        }
        else{
            mover->next = temp;
            mover = temp;
        }
        p2 = p2->next;
    }

    return resHead;
}

void performPolyOperations(){
    int degree = 0, user_choice = 0;
    Node* result = NULL;

    printf("Enter the degree of the first Polynomial: ");
    scanf("%d", &degree);
    if(degree < 0){
        printf("Invalid degree\n");
        exit(1);
    }
    Node* poly1 = insertPolynomial(degree);
    sortPolynomial(poly1, degree);

    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Enter the degree of the second Polynomial: ");
    scanf("%d", &degree);
    if(degree < 0){
        printf("Invalid degree\n");
        exit(1);
    }
    Node* poly2 = insertPolynomial(degree);
    sortPolynomial(poly2, degree);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    printf("\nChoose an Operation To Perform:-\n");
    printf("1) Addition of the two polynomials\n");
    printf("2) Subtraction of the two polynomials\n");
    printf("3) Multiplication of the two polynomials\n");
    printf("4) Exit the Program\n");

    while(printf("\nEnter Your Choice: ") && (scanf("%d", &user_choice) == 1)){
        switch(user_choice){
            case 1:
                result = addPolynomials(poly1, poly2);
                printf("\nResult: ");
                displayPolynomial(result);
                break;
            case 2:
                result = subPolynomials(poly1, poly2);
                printf("Result: ");
                displayPolynomial(result);
                break;
            case 3:
                // result = multPolynomials(poly1, poly2);
                printf("Result: ");
                displayPolynomial(result);
                break;
            case 4:
                printf("Program Terminated...\n");
                return;
            default:
                printf("Invalid Input\n");
                break;
        }
    }
    return;
}

int main() {

    performPolyOperations();

    return 0;
}