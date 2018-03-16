//Copyright to 20145523 KimSangHeon
//Last updated date : 2018-03-16
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
void Merge (int* inputORG, int* inputSOR, int left, int mid, int right) {
    int i, j, k;
    i = left;
    j = mid + 1;
    k = left;

    while ( i <= mid && j <= right ) {
        if ( inputORG[i] >= inputORG[j] ) {
            inputORG[k++] = inputORG[i++];
        }
        else {
            inputORG[k++] = inputORG[j++];
        }
    }

    while ( i <= mid ) inputORG[k++] = inputORG[i++];
    while ( j <= right ) inputORG[k++] = inputORG[j++];
}
//Merge Sorting Function
void MergeSort (int* inputORG, int* inputSOR, int left, int right) {
    int mid;
    if ( left < right ) {
        mid = (left + right) / 2;
        MergeSort(inputORG, inputSOR, left, mid);
        MergeSort(inputORG, inputSOR, mid + 1, right);
        Merge(inputORG, inputSOR, left, mid, right);
    }
}

int main (int argc, char* argv[]) {
    // ERROR : Wrong command line input
    if (argc != 3 ) exit(EXIT_FAILURE);
    clock_t startTime;
    int i, N, input, count;
    int* inputSOR, *inputORG;
    double endTime;
    char* ptr;
    FILE *fp;

    N = strtol(argv[1], &ptr, 10);
    count = 0;
    if ( *ptr != '\0' ) exit(EXIT_FAILURE); // ERROR : If argv[1] is not integer
    if ( N == 0) exit(EXIT_FAILURE); // ERROR :  If argv[1] is 0 
    inputSOR = (int*)malloc(sizeof(int) * N);
    inputORG = (int*)malloc(sizeof(int) * N);

    //Read File
    fp = fopen(argv[2], "r");
    // ERROR : If file doesn't exist
    if ( fp == NULL ) exit(EXIT_FAILURE);
    for ( i = 0; i < N; i++ ) {
        if ((fscanf(fp, "%d\n", &input)) == EOF ){// If N>K
            N = i;
            break;
        }
        inputORG[i] = input;
    }
    fclose(fp);

    startTime = clock(); 
    MergeSort(inputORG, inputSOR, 0, N - 1);
    // ERROR :  If elapsed time is less then 1000ms
    if ( (clock() - startTime) < 1000 ) {
        do {
            count++;
            // Copy origin data to sorted array whenever loop started
            memcpy(inputSOR, inputORG, N * sizeof(int)); 
            MergeSort(inputORG, inputSOR, 0, N - 1);
        } while ( clock() - startTime < 1000 );
    }
    else count++;
    endTime = (double)(clock() - startTime) / (CLOCKS_PER_SEC / 1000);

    PrintArr(inputSOR, N);
    printf("Running time = %f ms\n", (double)(endTime / count) );

    free(inputSOR);
    free(inputORG);
    return 0;
}