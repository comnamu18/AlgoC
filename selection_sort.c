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
//Selection Sorting Function
void SelectionSort (int* input, int N) {
    int i, j, maxI, tmp;
    for ( i = 0; i < N - 1 ; i++) {
        maxI = i;
        for ( j = i + 1; j < N; j++) {
            if ( input[j] > input[maxI]) {//Find max num
                maxI = j;
            }
        }
        tmp = input[maxI];
        input[maxI] = input[i];
        input[i] = tmp;
    }
}

int main (int argc, char* argv[]) {
    if (argc != 3 ) exit(EXIT_FAILURE); // Wrong input
    clock_t startTime, endTime;
    int i, N, input;
    int* inputN;
    FILE *fp;

    N = atoi(argv[1]);
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
    SelectionSort(inputN, N);
    endTime = clock() - startTime;

    PrintArr(inputN, N);
    //Print sorting time by milliseconds
    printf("Running time = %f ms\n", ((float)(endTime)) / (CLOCKS_PER_SEC / 1000) );

    free(inputN);// Free inputN
    return 0;
}