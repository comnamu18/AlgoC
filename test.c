#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char *ptr;
    int a = strtol(argv[1], &ptr, 10);

    if (*ptr == '\0') printf("%d", a);
    else printf("wow");
}   