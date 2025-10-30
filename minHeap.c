#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int index) {
    return (index - 1) / 2;
}

int leftChild(int index) {
    return 2 * index + 1;
}

int rightChild(int index) {
    return 2 * index + 2;
}

void printHeap(int minHeap[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", minHeap[i]);
    }
    printf("\n");
}

void Heapify(int minHeap[], int size, int index) {
    int smallest = index;
    int leftId = leftChild(index);
    int rightId = rightChild(index);

    if(leftId < size && minHeap[leftId] < minHeap[smallest]) 
        smallest = leftId;

    if(rightId < size && minHeap[rightId] < minHeap[smallest])
        smallest = rightId;

    if(smallest != index) {
        swap(&minHeap[smallest], &minHeap[index]);
        Heapify(minHeap, size, smallest);
    }
}

void buildMinHeap(int a[], int size) {
    for(int i = (size - 2) / 2; i >= 0; i--) {
        Heapify(a, size, i);
    }
}

void insert(int minHeap[], int *size, int value) {
    if(*size >= MAX) {
        printf("Overflow\n");
        exit(1);
    }
    int insertId = *size;
    minHeap[insertId] = value;
    (*size)++;

    int parentId = parent(insertId);

    while(insertId != 0 && minHeap[parentId] > minHeap[insertId]) {
        swap(&minHeap[parentId], &minHeap[insertId]);
        insertId = parentId;
        parentId = parent(insertId);
    }
}

void delete(int minHeap[], int *size) {
    if(*size == 0) {
        printf("Underflow\n");
        exit(1);
    }
    swap(&minHeap[0], &minHeap[*size - 1]);
    (*size)--;
    
    Heapify(minHeap, *size, 0);    
}

int main() {
    int minHeap[MAX] = {30, 24, 56, 10, 12};
    int size = 5;

    // Sample Min Heap
    buildMinHeap(minHeap, size);

    int user_choice = 0, value = 0;

    printf("\nGiven Min Heap: ");
    printHeap(minHeap, size);

    printf("\nSelect an Operation: \n");
    printf("1) Insert an Element in the Heap\n");
    printf("2) Delete root Element from the Heap\n");
    printf("3) Exit the Program\n");

    while(printf("\nEnter Your Choice: ") && (scanf("%d", &user_choice) == 1)) {
        switch (user_choice) {
            case 1: 
                printf("\nEnter the Element you want to Insert: ");
                scanf("%d", &value);
                insert(minHeap, &size, value);
                printf("\nUpdated Min Heap: ");
                printHeap(minHeap, size);
                break;
            case 2:
                if(size <= 0){
                    printf("\nUnderflow");
                    break;
                }
                printf("\nDeleted Element: %d\n", minHeap[0]);
                delete(minHeap, &size);
                printf("\nUpdated Min Heap: ");
                printHeap(minHeap, size);
                break;
            case 3:
                printf("\nProgram Terminated...\n");
                return 0;
            default:
                printf("\nInvalid Input");
                break;
        }
    }
    
    return 0;
}