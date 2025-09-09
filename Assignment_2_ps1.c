#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// To run the code give the command on terminal
// ./Assignment_2_ps1 ./input.txt   
// after compilation
// input.txt can be any file in the current directory

int main(int argc, char *argv[]) {
    int fd;
    char ch;
    fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        printf("Open Failed\n");
        exit(1);
    }
    while(read(fd, &ch, 1))
        putchar(ch);
    return 0;
}