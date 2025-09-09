#include <stdio.h>
#include <stdbool.h>

// removes duplicates from the array without changing the order of the elements
int removeDuplicates(double *arr, int lena){
    int newlen = 0;
    bool found = false;

    for(int i = 0; i < lena; i++){
        found = false;
        for(int j = 0; j < newlen; j++){
            if(arr[i] == arr[j]){
                found = true;
                break;
            }
        }
        if(!found){
            arr[newlen] = arr[i];
            newlen++;
        }
    }
    return newlen;
}

// prints the array
void printArray(double *arr, int lena){
    for(int i = 0; i < lena; i++){
        printf("%.2lf ", arr[i]);
    }
    printf("\n");
}

int main() {
    double arr[64];
    int lena = 0, newlen = 0;

    while(scanf("%lf", &arr[lena]) == 1)
        lena++;

    printf("Original Array -> ");
    printArray(arr, lena);

    newlen = removeDuplicates(arr, lena);
    printf("After Removing Duplicates -> ");
    printArray(arr, newlen);

    return 0;
}