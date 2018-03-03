//Copyright to 20145523 KimSangHeon
//2018-03-03
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Print Result Function
void PrintArr (char* input, int N) {
    int i = 0;
    for ( i = 0; i < N; i++) {
        printf("%d\n", input[i]);
    }
}
//Selection Sorting Function
void SelectionSort (char* input, int N) {
    int i, j, k, max, tmp;
    for ( i = 0; i < N - 1 ; i++) {
        max = input[i];
        k = i;
        for ( j = i + 1; j < N; j++) {
            if (input[j] > max) {
                max = input[j];
                k = j;
            }
        }
        tmp = input[i];
        input[i] = max;
        input[k] = tmp;
    }
    PrintArr(input, N);
}

int main (int argc, char* argv[]) {
    if (argc != 2 ) return 0; // Wrong input
    clock_t starTime;
    int N;
    char* input;
    FILE *fp;

    starTime = clock(); // Starting Time Checking
    N = atoi(argv[0]);
    input = (char*)malloc(sizeof(char) * N);

    //Read File
    fp = fopen(argv[1], "r");
    if (fscanf(fp, "%s", input) == EOF) return 0; //IF File is Empty
    fclose(fp);

    SelectionSort(input, N);

    //Print Total program time by milliseconds
    printf("Running time = %f ms\n", ((float)(clock() - starTime)) / (CLOCKS_PER_SEC / 1000) );
}