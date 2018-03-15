//Copyright to 20145523 KimSangHeon
//Last updated date : 2018-03-15
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Print Result Function
void PrintArr (int* input, int N) {
    int i;
    for ( i = 0; i < N; i++) {
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
    // Wrong command line input
    if (argc != 3 ) exit(EXIT_FAILURE);
    clock_t startTime;
    int i, N, input, count;
    int* inputN, *inputTMP;
    double endTime;
    char* ptr;
    FILE *fp;

    N = strtol(argv[1], &ptr, 10);
    count = 0;
    if ( *ptr != '\0' ) exit(EXIT_FAILURE); // If argv[1] is not integer
    if ( N == 0) exit(EXIT_FAILURE); // If argv[1] is 0 
    inputN = (int*)malloc(sizeof(int) * N);
    inputTMP = (int*)malloc(sizeof(int) * N);

    //Read File
    fp = fopen(argv[2], "r");
    // If file doesn't exist
    if (fp == NULL) exit(EXIT_FAILURE);
    for ( i = 0; i < N; i++) {
        if ((fscanf(fp, "%d\n", &input)) == EOF){//if N>K
            N = i;
            break;
        }
        inputN[i] = input;
    }
    fclose(fp);
    memcpy(inputTMP, inputN, N * sizeof(int));

    // Starting Time Checking
    startTime = clock(); 
    InsertionSort(inputTMP, N);
    // If elapsed time is less then 0ms
    if ( (clock() - startTime) < 1000 ) {
        do {
            count++;
            // Copy origin data to inputTMP whenever loop started
            memcpy(inputTMP, inputN, N * sizeof(int)); 
            InsertionSort(inputTMP, N);
        } while ( clock() - startTime < 1000);
    }
    else count++;
    endTime = (double)(clock() - startTime) / (CLOCKS_PER_SEC / 1000);

    PrintArr(inputTMP, N);
    printf("Running time = %f ms\n", (double)(endTime / count) );

    free(inputN);
    free(inputTMP);
    return 0;
}