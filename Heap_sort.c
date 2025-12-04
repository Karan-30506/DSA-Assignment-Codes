#include <stdio.h>

void heapify(int *a, int n, int i) {
    int largest = i;
    int leftid = 2*i + 1;
    int rightid = 2* i + 2;

    if(leftid < n && a[largest] < a[leftid])
        largest = leftid;

    if(rightid < n && a[largest] < a[rightid])
        largest = rightid;

    if(largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int *a, int n) {
    // build maxHeap
    for(int i = n-2 / 2; i >= 0; i--) {
        heapify(a, n, i);
    }

    for(int i = n-1; i >= 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main() {
    int a[] = {5, 4, 2, 3, 1};

    heapSort(a, 5);

    for(int i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
    
    return 0;
}