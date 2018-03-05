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
        max = input[i];
        j = i;
        //try to insert MAX value
        while ( --j >= 0 && input[j] < max ) {
            input[j + 1] = input[j];
            input[j] = max;
        }
    }
    PrintArr(input, N);
}

int main (int argc, char* argv[]) {
    if (argc != 3 ) exit(EXIT_FAILURE); // Wrong input
    clock_t starTime;
    int i, N, input;
    int* inputN;
    FILE *fp;

    starTime = clock(); // Starting Time Checking
    N = atoi(argv[1]);
    inputN = (int*)malloc(sizeof(int) * N);

    //Read File
    fp = fopen(argv[2], "r");
    if (fp == NULL) exit(EXIT_FAILURE); // If file doesn't exist
    i = 0;
    while (i < N) {
        //if N>K
        if ((fscanf(fp, "%d\n", &input)) == EOF){
            N = i;
            break;
        }
        inputN[i] = input;
        i++;
    }
    fclose(fp);

    InsertionSort(inputN, N);

    //Print total program time by milliseconds
    printf("Running time = %f ms\n", ((float)(clock() - starTime)) / (CLOCKS_PER_SEC / 1000) );

    return 0;
}