/*Copyright to 20145523 KimSangHeon
Last updated date : 2018-03-17*/
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
void Merge ( int* input, int low, int mid, int high ) {
    int i, j, k;
    int *tmp;

    tmp = (int*)malloc( (high - low + 1) * sizeof(int));
    i = low;
    j = mid + 1;
    k = 0;
    //Compare Left block and Right block
    while ( i <= mid && j <= high ) {
        if ( input[i] > input[j] ) {
            tmp[k++] = input[i++];
        }
        else {
            tmp[k++] = input[j++];
        }
    }
    //If still remaining instances are exist
    while (i <= mid) tmp[k++] = input[i++];
    while (j <= high) tmp[k++] = input[j++];
    
    for ( i = 0; i < k; i++) {
        input[low + i] = tmp[i];
    }

    free(tmp);
}
//Merge Sorting Function
void MergeSort ( int* input, int low, int high ) {
    int mid;
    if(high > low) {
        mid = (low + high) / 2;
        // Keep spliting
        MergeSort(input, low, mid);
        MergeSort(input, mid + 1, high);
        // 
        Merge(input, low, mid, high);
    }
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
    MergeSort(inputN, 0, N - 1);
    // ERROR : If elapsed time is less then 1000ms
    if ( (clock() - startTime) < 1000 ) {
        do {
            count++;
            // Copy origin data to inputN whenever loop started
            memcpy(inputN, inputORG, N * sizeof(int)); 
            MergeSort(inputN, 0, N - 1);
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