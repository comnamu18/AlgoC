//Copyright to 20145523 KimSangHeon
//Last updated date : 2018-03-05
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Print Result Function
void PrintArr (int* input, int N) {
    for ( int i = 0; i < N; i++) {
        printf("%d\n", input[i]);
    }
}
//Insertion Sorting Function
void InsertionSort (int* input, int N) {
    int i, j, max;
    for ( i = 1; i < N; i++) {
        max = input[(j = i)];
        //try to insert MAX value
        while ( --j >= 0 && input[j] < max ) {
            input[j + 1] = input[j];
        }
        input[j + 1] = max;
    }
}

int main (int argc, char* argv[]) {
    if (argc != 3 ) exit(EXIT_FAILURE); // Wrong input
    clock_t startTime, endTime;
    int i, N, input;
    int* inputN;
    FILE *fp;

    N = atoi(argv[1]);
    if ( N == 0) exit(EXIT_FAILURE); // If argv[1] is not integer or 0
    inputN = (int*)malloc(sizeof(int) * N);

    //Read File
    fp = fopen(argv[2], "r");
    if (fp == NULL) exit(EXIT_FAILURE); // If file doesn't exist
    for ( i = 0; i < N; i++) {
        if ((fscanf(fp, "%d\n", &input)) == EOF){//if N>K
            N = i;
            break;
        }
        inputN[i] = input;
    }
    fclose(fp);// Free fp

    startTime = clock(); // Starting Time Checking
    InsertionSort(inputN, N);
    endTime = clock() - startTime;
    
    PrintArr(inputN, N);
    //Print sorting time by milliseconds
    printf("Running time = %d ms\n", ((int)(endTime)) );

    free(inputN);// Free inputN
    return 0;
}