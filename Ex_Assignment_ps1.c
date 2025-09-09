#include <stdio.h>

typedef struct info {
    char fname[32];
    char mname[32];
    char lname[32];
}info;

void read_fullname(info *sp){
    scanf("%s %s %s", sp->fname, sp->mname, sp->lname);
}

void print_fullname(info *sp){
    printf("%s ", sp->fname);
    printf("%s ", sp->mname);
    printf("%s\n", sp->lname);
}

int main() {
    info a;
    read_fullname(&a);
    print_fullname(&a);         
    return 0;
}