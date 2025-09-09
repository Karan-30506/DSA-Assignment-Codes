#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getArray(const char *filename, int *a){
    int lena = 0;
    FILE *ptr;

    ptr = fopen(filename, "r");
    if(ptr == NULL){
        printf("Open Failed\n");
        exit(1);
    }

    while(fscanf(ptr, "%d", &a[lena]) == 1)
        lena++;

    fclose(ptr);
    return lena;
}

int main(int argc, char *argv[]) {
    int a[3000], lena = 0;
    lena = getArray(argv[1], a);

    for(int i = 0; i < lena; i++){
        printf("%d ", a[i]);
    }
    

    return 0;
}