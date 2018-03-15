//Copyright to 20145523 KimSangHeon
//Last updated date : 2018-03-05
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Print Result Function
void PrintArr (int* input, int N) {
    for ( int i = 0; i < N; i++) {
        printf("%d\n", input[i]);
    }
}
//Merge Function
void Merge (int* input, int Left, int Right, int N){
    int* tmp;
    int i, j, k;
    i = Left;
    j = Right + 1;
    k = 0;
    tmp = (int*)malloc(sizeof(int) * N);
    while ( i <= Right && j <= N) {
        if ( input[i] > input[j] ) {
            tmp[k++] = input[i++];
        }
        else {
            tmp[k++] = input[j++];
        }
    }
    //If still remaining things are exist
    while (i < Left) tmp[k++] = input[i++];
    while (j < Right) tmp[k++] = input[j++];
    while (--k >= 0) input[Left + k] = tmp[k];
}
//Merge Sorting Function
void MergeSort (int* input, int N) {
    int mid;
    int Left, Right;

    Left = N / 2;
    Right = N - Left;
    
    if (Left < Right) {
        
    }
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
    printf("Running time = %d ms\n", ((int)(endTime)) );

    free(inputN);// Free inputN
    return 0;
}