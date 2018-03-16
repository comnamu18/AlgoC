/*Copyright to 20145523 KimSangHeon
Last updated date : 2018-03-16*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Print Result Function
void PrintArr ( int* input, int N ) {
    int i;
    for ( i = 0; i < N; i++) {
        printf("%d\n", input[i]);
    }
}
//Merge Function
void Merge ( int* input, int* Left, int* Right, int N ) {
    int i, j, k, LeftN, RightN;
    i = 0;
    j = 0;
    k = 0;
    LeftN = N / 2;
    RightN = N - LeftN;
    //Compare Left block and Right block
    while ( i < LeftN && j < RightN) {
        if ( Left[i] > Right[j] ) {
            input[k++] = Left[i++];
        }
        else {
            input[k++] = Right[j++];
        }
    }
    //If still remaining instances are exist
    while (i < LeftN) input[k++] = Left[i++];
    while (j < RightN) input[k++] = Right[j++];
}
//Merge Sorting Function
void MergeSort ( int* input, int N ) {
    int mid;
    int *Left, *Right;

    if (N < 2) return; //If array has less then two components, stop spliting

    mid = N / 2;
    Left = (int*)malloc(mid*sizeof(int));
    Right = (int*)malloc((N-mid)*sizeof(int));
    //Split input Array into Two arrays
    memcpy(Left, input, mid * sizeof(int));
    memcpy(Right, input + mid, (N - mid) * sizeof(int));
    
    //Keep spliting till less then two components left
    MergeSort(Left, mid);
    MergeSort(Right, N - mid);
    //Merge splited arrays
    Merge(input, Left, Right, N);

    free(Left);
    free(Right);
}

int main ( int argc, char* argv[] ) {
    // ERROR : Wrong command line input
    if (argc != 3 ) exit(EXIT_FAILURE);
    clock_t startTime;
    int i, N, input, count;
    int* inputN, *inputORG;
    double endTime;
    char* ptr;
    FILE *fp;

    N = strtol(argv[1], &ptr, 10);
    count = 0;
    if ( *ptr != '\0' ) exit(EXIT_FAILURE); // ERROR : If argv[1] is not integer
    if ( N == 0 ) exit(EXIT_FAILURE); // ERROR : If argv[1] is 0 
    inputN = (int*)malloc(sizeof(int) * N);
    inputORG = (int*)malloc(sizeof(int) * N);

    fp = fopen(argv[2], "r");
    // ERROR : If file doesn't exist
    if ( fp == NULL ) exit(EXIT_FAILURE);
    for ( i = 0; i < N; i++ ) {
        if ((fscanf(fp, "%d\n", &input)) == EOF ){//If N>K
            N = i;
            break;
        }
        inputN[i] = input;
    }
    fclose(fp);
    //Save original data to another inputORG
    memcpy(inputORG, inputN, N * sizeof(int));

    startTime = clock(); 
    MergeSort(inputN, N);
    // ERROR : If elapsed time is less then 1000ms
    if ( (clock() - startTime) < 1000 ) {
        do {
            count++;
            // Copy origin data to inputN whenever loop started
            memcpy(inputN, inputORG, N * sizeof(int)); 
            MergeSort(inputN, N);
        } while ( clock() - startTime < 1000 );
    }
    else count++;
    endTime = (double)(clock() - startTime) / (CLOCKS_PER_SEC / 1000);

    PrintArr(inputN, N);
    printf("Running time = %f ms\n", (double)(endTime / count) );

    free(inputN);
    free(inputORG);
    return 0;
}