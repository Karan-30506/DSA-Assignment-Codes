#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// reads the data from the given file and puts it into the array
int get_array(char *file_name, char data[][128]){
    int fd, rows = 0, n = 0;
    char str[1024];

    fd = open(file_name, O_RDONLY);
    if(fd == -1){
        printf("Open Failed\n");
        exit(1);
    }
    n = read(fd, str, 1023);
    str[n] = '\0';
    // printf("%s\n", str);

    char *token = strtok(str, "\n");
    while(token != NULL){
        strcpy(data[rows], token);
        token = strtok(NULL, "\n");
        rows++;
    }
    close(fd);
    return rows;
}

// Used to check if the entire string is numeric
bool is_numeric(char *str){
    if(*str == '\0')
        return false;
    while(*str){
        if(!isdigit(*str))
            return false;
        str++;
    }
    return true;
}

// Custom function to compare numeric strings and non-numeric strings
int stringCompare(char *str1, char *str2){
    bool str1_isnum = is_numeric(str1);
    bool str2_isnum = is_numeric(str2);

    if(str1_isnum && str2_isnum){
        int num1 = atoi(str1);
        int num2 = atoi(str2);
        if(num1 < num2)
            return -1;
        else if(num1 > num2)
            return 1;
        else
            return 0;
    }
    else{
        return strcmp(str1, str2);
    }
}

// used by the quickSort function to swap the given two strings
void swap(char *str1, char *str2){
    char temp[128] = "";
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
}

// used by quickSort function to insert the pivot element at the correct index
int partition(char data[][128], int low, int high){
    char pivot[128] = "";
    strcpy(pivot, data[low]);
    int i = low, j = high;

    while(i < j){

        while(stringCompare(data[i], pivot) <= 0 && i <= high - 1)
            i++;

        while(stringCompare(data[j], pivot) > 0 && j >= low + 1)
            j--;

        if(i < j)
            swap(data[i], data[j]);
    }
    swap(data[low], data[j]);
    return j;
}

// Sorts the array
void quickSort(char data[][128], int low, int high){
    if(low < high){
        int pID = partition(data, low, high);
        quickSort(data, low, pID - 1);
        quickSort(data, pID + 1, high);
    }
}

// Prints the data
void printData(char data[][128], int rows){
    for(int i = 0; i < rows; i++)
        printf("%s\n", data[i]);
}

// puts the sorted data back into the given file
// we can also put it into a different file by giving a second argument to main argv[2]
void put_array(char *file_name, char data[][128], int rows){
    int fd;
    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC);
    if(fd == -1){
        printf("Open Failed\n");
        exit(1);
    }
    int i = 0;
    while(i < rows){
        write(fd, data[i], strlen(data[i]));
        write(fd, "\n", 1);
        i++;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    char data[64][128];
    int rows = 0;

    rows = get_array(argv[1], data);

    quickSort(data, 0, rows - 1);

    printData(data, rows);

    // to put hte input into a different file change argv[1] to argv[2]
    put_array(argv[1], data, rows);
    return 0;
}