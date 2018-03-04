//Copyright to 20145523 KimSangHeon
//2018-03-03
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Print Result Function
void PrintArr (int* input, int N) {
    int i = 0;
    for ( i = 0; i < N; i++) {
        printf("%d\n", input[i]);
    }
}
//Insertion Sorting Function
void InsertionSort (int* input, int N) {
    int i, j, tmp, max;
    for ( i = 1; i < N; i++) {
        max = input[i];
        j = i - 1;
        //try to insert MAX value
        while ( j > -1 && input[j] < max ) {
            input[i] = input[j];
            input[j] = max;
            j--;
        }
    }
    PrintArr(input, N);
}

int main (int argc, char* argv[]) {
    if (argc != 3 ) return 0; // Wrong input
    clock_t starTime;
    int i, N;
    char* input;
    int* inputN;
    FILE *fp;

    starTime = clock(); // Starting Time Checking
    N = atoi(argv[1]);
    inputN = (int*)malloc(sizeof(int) * N);

    //Read File
    printf("%s\n", argv[2]);
    fp = fopen(argv[2], "r");
    i = 0;
    while (i < N) {
        fscanf(fp, "%s", input);
        inputN[i] = atoi(input);
        i++;
    }
    fclose(fp);

    InsertionSort(inputN, N);

    //Print Total program time by milliseconds
    printf("Running time = %f ms\n", ((float)(clock() - starTime)) / (CLOCKS_PER_SEC / 1000) );
}