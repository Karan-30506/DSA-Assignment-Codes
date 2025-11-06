#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// The given code considers a 0-indexed undirected graph

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int n;
    struct Node** adjList;
    int *vertexValues;
} Graph;

Node* initNode(int vertex) {
    Node* newNode = (Node *) malloc(sizeof(Node));
    if(!newNode) {
        printf("Malloc Failed!\n");
        exit(1);
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* initGraph(int vertices) {
    Graph* g = (Graph*) malloc(sizeof(Graph));
    if(!g) {
        printf("Malloc Failed!\n");
        exit(2);
    }
    g->n = vertices;
    g->adjList = (Node**) malloc(sizeof(Node*) * vertices);
    g->vertexValues = (int*) calloc(vertices, sizeof(int));
    if(!g->adjList || !g->vertexValues) {
        printf("Malloc Failed!\n");
        exit(2);
    }
    for(int i = 0; i < g->n; i++) {
        g->adjList[i] = NULL;
        g->vertexValues[i] = i + 1;
    }
    return g;
}

int getValueIndex(Graph g, int value) {
    for(int i = 0; i < g.n; i++) {
        if(g.vertexValues[i] == value)
            return i;
    }
    return -1;
}

bool findVertexIndex(Graph g, int vertex) {
    return (vertex >= 0) && (vertex < g.n);
}

bool findVertex(Graph g, int value) {
    return getValueIndex(g, value) != -1;
}

bool findEdge(Graph g, int srcValue, int destValue) {
    int src = getValueIndex(g, srcValue);
    int dest = getValueIndex(g, destValue);
    if(src == -1 || dest == -1) {
        return false;
    }
        Node* temp = g.adjList[src];
        while(temp) {
            if(g.vertexValues[temp->vertex] == destValue)
                return true;
            temp = temp->next;
        }
    return false;
}

void changeVertexValue(Graph **g, int vertex, int value) {
    if(!findVertexIndex(**g, vertex)) {
        printf("Invalid Node\n");
        return;
    }
    (*g)->vertexValues[vertex] = value;
}

void insertEdge(Graph* g, int srcValue, int destValue) {
    int src = getValueIndex(*g, srcValue);
    int dest = getValueIndex(*g, destValue);
    if(src == -1 || dest == -1) {
        printf("Invalid Node\n");
        return;
    }
    else if(findEdge(*g, srcValue, destValue) || findEdge(*g, destValue, srcValue)) {
        printf("Edge already exists\n");
        return;
    }
    Node* newHead = initNode(dest);
    newHead->next = g->adjList[src];
    g->adjList[src] = newHead;

    newHead = initNode(src);
    newHead->next = g->adjList[dest];
    g->adjList[dest] = newHead;
}

void deleteEdge(Graph* g, int srcValue, int destValue) {
    int src = getValueIndex(*g, srcValue);
    int dest = getValueIndex(*g, destValue);
    if(src == -1 || dest == -1) {
        printf("Invalid Node\n");
        return;
    }
    else if(!findEdge(*g, srcValue, destValue) && !findEdge(*g, destValue, srcValue)) {
        printf("Edge doesn't exist\n");
        return;
    }
    Node* temp = g->adjList[src];
    Node* prev = NULL;
    while(temp && temp->vertex != dest) {
        prev = temp;
        temp = temp->next;
    }

    if(!prev) {
        g->adjList[src] = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    free(temp);


    temp = g->adjList[dest];
    prev = NULL;
    while(temp && temp->vertex != src) {
        prev = temp;
        temp = temp->next;
    }
    if(!prev) {
        g->adjList[dest] = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    free(temp);
}

void insertNode(Graph **g, int value) {
    if(findVertex(**g, value)) {
        printf("Node already exists\n");
        return;
    }
    int newVertex = (*g)->n;
    (*g)->n++;

    (*g)->adjList = realloc((*g)->adjList, sizeof(Node*) * (*g)->n);
    (*g)->adjList[newVertex] = NULL;
    (*g)->vertexValues = realloc((*g)->vertexValues, sizeof(int) * (*g)->n);
    (*g)->vertexValues[newVertex] = value;
    printf("Node %d was Added with value %d\n", newVertex, value);
}

void deleteNode(Graph **g, int value) {
    int vertex = getValueIndex(**g, value);
    if(vertex == -1) {
        printf("Invalid Node\n");
        return;
    }
    int n = (*g)->n;
    for(int i = 0; i < n; i++) {
        if(i != vertex) {
            deleteEdge(*g, (*g)->vertexValues[i], (*g)->vertexValues[vertex]);
        }
    }

    Node* temp = (*g)->adjList[vertex];
    while(temp) {
        Node* toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }

    for(int i = vertex; i < n - 1; i++) {
        (*g)->adjList[i] = (*g)->adjList[i + 1];
        (*g)->vertexValues[i] = (*g)->vertexValues[i + 1];
    }

    (*g)->n--;
    n = (*g)->n;
    (*g)->adjList = realloc((*g)->adjList, sizeof(Node*) * n);
    (*g)->vertexValues = realloc((*g)->vertexValues, sizeof(int) * n);

    for(int i = 0; i < n; i++) {
        Node* temp = (*g)->adjList[i];
        while(temp) {
            if(temp->vertex > vertex){
                temp->vertex--;
            }
            temp = temp->next;
        }
    }
}

void printGraph(Graph g) {
    for(int i = 0; i < g.n; i++) {
        printf("%d: ", g.vertexValues[i]);
        Node* temp = g.adjList[i];
        while(temp) {
            printf("%d --> ", g.vertexValues[temp->vertex]);
            temp = temp->next;
        }
        printf("(NULL)\n");
    }
}

int main() {
    Graph* g = initGraph(5);    
    changeVertexValue(&g, 0, 30);
    changeVertexValue(&g, 1, 24);
    changeVertexValue(&g, 2, 17);
    changeVertexValue(&g, 3, 45);
    changeVertexValue(&g, 4, 56);
    insertEdge(g, 30, 24);
    insertEdge(g, 30, 56);
    insertEdge(g, 45, 56);
    insertEdge(g, 45, 24);
    insertEdge(g, 17, 24);
    insertEdge(g, 17, 45);    

    printf("\nGiven Graph\n");
    printGraph(*g);

    printf("\nSelect Operations to Perform\n");
    printf("1) Insert a Node\n");
    printf("2) Insert an Edge\n");
    printf("3) Delete a Node\n");
    printf("4) Delete an Edge\n");
    printf("5) Find a Node\n");
    printf("6) Find an Edge\n");
    printf("7) Print the Adjacency List\n");
    printf("8) Exit the Program\n");

    int userChoice = 0, value = 0;
    int src = 0, dest = 0;

    while(printf("\nEnter Your Choice: ") && (scanf("%d", &userChoice) == 1)) {
        switch (userChoice) {
            case 1:
                printf("\nEnter the Value you want to insert: ");
                scanf("%d", &value);
                insertNode(&g, value);
                printf("\nUpdated Adjacency List\n");
                printGraph(*g);
                break;
            case 2:
                printf("\nEnter the Source and Destination: ");
                scanf("%d %d", &src, &dest);
                insertEdge(g, src, dest);
                printf("\nUpdated Adjacency List\n");
                printGraph(*g);
                break;
            case 3:
                printf("\nEnter the Value you want to Delete: ");
                scanf("%d", &value);
                deleteNode(&g, value);
                printf("\nUpdated Adjacency List\n");
                printGraph(*g);
                break;
            case 4:
                printf("\nEnter the Source and Destination: ");
                scanf("%d %d", &src, &dest);
                deleteEdge(g, src, dest);
                printf("\nUpdated Adjacency List\n");
                printGraph(*g);
                break;
            case 5:
                printf("\nEnter the value you want to find: ");
                scanf("%d", &value);
                if(findVertex(*g, value)) {
                    printf("\nGiven node found\n");
                }
                else {
                    printf("\nGiven node not found\n");

                }
                break;
            case 6:
                printf("\nEnter the Source and Destination: ");
                scanf("%d %d", &src, &dest);
                if(findEdge(*g, src, dest)) {
                    printf("\nGiven edge is present\n");
                }
                else {
                    printf("\nGiven edge is not present\n");
                }
                break;
            case 7:
                printGraph(*g);
                break;
            case 8:
                printf("\nProgram Terminated...\n");
                exit(0);
            default:
                printf("\nInvalid Input!\n");
                break;            
        }
    }
    return 0;
}