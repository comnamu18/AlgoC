//Copyright to 20145523 KimSangHeon
//2018-03-03
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char* argv[]) {
    if (argc != 2 ) return 0; // Wrong input
    clock_t starTime;
    int N;
    char* input;
    FILE *fp;

    starTime = clock(); // Starting Time Checking
    N = atoi(argv[0]);
    input = (char*)malloc(sizeof(char) * N);

    //Read File
    fp = fopen(argv[1], "r");
    if (fscanf(fp, "%d", input) == EOF) return 0; //IF File is Empty
    fclose(fp);

    MergeSort()

    //Print Total program time by milliseconds
    printf("Running time = %f ms\n", ((float)(clock() - starTime)) / (CLOCKS_PER_SEC / 1000) );
}
