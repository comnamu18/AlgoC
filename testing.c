#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
int  main(int argc, char* argv[])
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen(argv[1], "r");
    if (fp == NULL)  exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
            printf("Retrieved line of length %zu :\n", read);
            printf("%s", line);
    }
    free(line);  /* getline에서 할당된 힙 메모리 해제 */

    exit(EXIT_SUCCESS);
}