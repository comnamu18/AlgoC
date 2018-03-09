//Copyright to 20145523 KimSangHeon
//Last updated date : 2018-03-09
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Print Result Function
void PrintArr (int* input, int N) {
    int i;
    for ( i = 0; i < N; i++) {
        printf("%d\n", input[i]);
    }
}
//Merge Function
void Merge (int* input, int* Left, int* Right, int N){
    int i, j, k, LeftN, RightN;
    i = 0;
    j = 0;
    k = 0;
    LeftN = N / 2;
    RightN = N - LeftN;
    while ( i < LeftN && j < RightN) {
        if ( Left[i] > Right[j] ) {
            input[k++] = Left[i++];
        }
        else {
            input[k++] = Right[j++];
        }
    }
    //If still remaining things are exist
    while (i < LeftN) input[k++] = Left[i++];
    while (j < RightN) input[k++] = Right[j++];
}
//Merge Sorting Function
void MergeSort (int* input, int N) {
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
    free(Right); //Free memory
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
        if ((fscanf(fp, "%d\n", &input)) == EOF){// If N > K
            N = i;
            break;
        }
        inputN[i] = input;
    }
    fclose(fp);// Free fp

    startTime = clock(); // Starting Time Checking  
    MergeSort(inputN, N);
    endTime = clock() - startTime;

    PrintArr(inputN, N);
    //Print sorting time by milliseconds
    printf("Running time = %d ms\n", (int)((float)(endTime) / (CLOCKS_PER_SEC / 1000)) );

    free(inputN);// Free inputN
    return 0;
}