/*Copyright to 20145523 KimSangHeon
Last updated date : 2018-03-16*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Print Result Function
void PrintArr ( int* input, int N ) {
    int i;
    for ( i = 0; i < N; i++ ) {
        printf("%d\n", input[i]);
    }
}
//Selection Sorting Function
void SelectionSort ( int* input, int N ) {
    int i, j, maxI, tmp;
    for ( i = 0; i < N - 1 ; i++ ) {
        maxI = i;
        for ( j = i + 1; j < N; j++ ) {
            //Find Maximum number's index
            if ( input[j] > input[maxI] ) {
                maxI = j;
            }
        }
        tmp = input[maxI];
        input[maxI] = input[i];
        input[i] = tmp;
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
    if ( N == 0) exit(EXIT_FAILURE); // ERROR : If argv[1] is 0 
    inputN = (int*)malloc(sizeof(int) * N);
    inputORG = (int*)malloc(sizeof(int) * N);

    fp = fopen(argv[2], "r");
    // ERROR : If file doesn't exist
    if ( fp == NULL ) exit(EXIT_FAILURE);
    for ( i = 0; i < N; i++ ) {
        if ((fscanf(fp, "%d\n", &input)) == EOF ){// If N>K
            N = i;
            break;
        }
        inputN[i] = input;
    }
    fclose(fp);
    //Save original data to another inputORG
    memcpy(inputORG, inputN, N * sizeof(int));

    startTime = clock(); 
    SelectionSort(inputN, N);
    // ERROR : If elapsed time is less then 1000ms
    if ( (clock() - startTime) < 1000 ) {
        do {
            count++;
            // Copy origin data to inputN whenever loop started
            memcpy(inputN, inputORG, N * sizeof(int)); 
            SelectionSort(inputN, N);
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