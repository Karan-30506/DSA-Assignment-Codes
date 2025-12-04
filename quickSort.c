#include <stdio.h>

int partition(int* a, int low, int high) {
    int pivot = a[low];
    int i = low;
    int j = high;

    while(i < j) {
        while(i <= high - 1 && a[i] <= pivot) 
            i++;

        while(j >= low + 1 && a[j] > pivot)
            j--;

        if(i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    int temp = a[low];
    a[low] = a[j];
    a[j] = temp;
    return j;
}

void quickSort(int* a, int low, int high) {
    if(low < high) {
        int pId = partition(a, low, high);
        quickSort(a, low, pId - 1);
        quickSort(a, pId + 1, high);
    }
}

int main() {
    int a[] = {5, 4, 2, 3, 1};

    quickSort(a, 0, 4);

    for(int i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
    
    return 0;
}