#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

// Continuously reads the input until EOF
void read_text(char *str, int size){
    char ch, *cp = str;
    while((ch = getchar()) != EOF && str - cp < size - 1)
        *str++ = ch;

    *str = '\0';
}

int main(int argc, char *argv[]) {
    char str[SIZE];
    int fd, n;
    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
    if(fd == -1){
        printf("Open Failed\n");
        exit(1);
    }

    read_text(str, SIZE);

    write(fd, str, strlen(str));
    close(fd);

    return 0;
}