/**
 * "MSD Radix Sort"
 * - ./msd_radix_sort <input_file_name> <N>
 * - measure running time of 'Radix Sort'
 *
 * KimSangHeon / 20145523
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#define INTEGER_BIT 32
#define digit(a,b) (( a >> ( INTEGER_BIT - b * CHAR_BIT)) & UCHAR_MAX)
static unsigned int *data, *dataORG, *aux;

//For the error control
void ExitWithMessage ( int type ) {
    switch (type) {
        case 1: 
            printf("Wrong command line input! \n");
            break;
        case 2:
            printf("N must be unsigned integer! \n");
            break;
        case 3:
            printf("N is not an integer! \n");
            break;
        case 4:
            printf("N is less then 0! \n");
            break;
        case 5:
            printf("File does not exist! \n");
            break;
    }
    exit(-1);
}
 //Print Result Function
 void PrintArr ( int N ) {
    int i;
    for ( i = 0; i < N; i++) {
        printf("%d\n", data[i]);
    }
}

//Insertion Sorting Function
void InsertionSort ( int first, int last ) {
    int i, j, N, max;
    N = last + 1;
    for ( i = first; i < N; i++ ) {
        max = data[(j = i)];
        //try to insert MAX value
        while ( --j >= first && data[j] > max ) {
            data[j + 1] = data[j];
        }
        data[j + 1] = max;
    }
}

/**
  * MSD Radix Sort
  * 8bit/8bit/8bit/8bit
  * consider 8bit as a bucket
  * d is for index counting
  **/
 void msd_radix_sort ( int first, int last, int d ){
    int i;
    unsigned int count[UCHAR_MAX + 2];
    if ( d > 5 ) return;
    if ( first >= last ) return;
    if ( last - first < INTEGER_BIT ) { // Too slow for small subarrays
        InsertionSort(first, last);
        return;
    }
    //initialize count array
    for ( i = 0; i <= UCHAR_MAX; i++) {
        count[i] = 0;
    }
 
    //divide to bucket
    for ( i = first; i <= last; i++) {
       count[digit(data[i], d) + 1]++;
    }
    for (i = 1; i <= UCHAR_MAX; i++) {
        count[i] += count[i - 1];
    }
    for ( i = first; i <= last; i++) {
        aux[count[digit(data[i],d)]++] = data[i];
    }
    //sorting
    for ( i = first; i <= last; i++) {
        data[i] = aux[i - first];
    }
    d++;
    //recursivley sort again from 0 to 255
    msd_radix_sort( first, first + count[0] - 1,  d);
    for ( i = 0; i < UCHAR_MAX; i++ ) {
        msd_radix_sort( first + count[i], first + count[i + 1] - 1, d);
    }
 }
 int main (int argc, char* argv[]) {
    clock_t startTime;
    int N, i;
    unsigned int input;
    double duration, count;
    char *numChk;
    FILE *fp;

    if (argc != 3 ) ExitWithMessage(1);    // Checking command line input
    // Checking N is correct unsigned integer
    if ( argv[2][0] == '-' ) ExitWithMessage(2);
    N = strtoul(argv[2], &numChk, 10);
    if ( *numChk != '\0' ) ExitWithMessage(3);
    if ( N < 1 ) ExitWithMessage(4);    // Checking N is bigger then 1
    fp = fopen(argv[1], "r");
    if ( fp == NULL ) ExitWithMessage(5);   // Checking file is exist
    //initialize
    count = 0;
    input = 0;
    data = (unsigned int*)malloc(sizeof(unsigned int) * N);
    dataORG = (unsigned int*)malloc(sizeof(unsigned int) * N);
    aux = (unsigned int*)malloc(sizeof(unsigned int) * N);
    //read file
    for ( i = 0; i < N; i++ ) {
        if ((fscanf(fp, "%u\n", &input)) == EOF ){//If N>K
            N = i;
            break;
        }
        data[i] = input;
    }
    fclose(fp);
    //Save original data to another dataORG
    memcpy(dataORG, data, N * sizeof(unsigned int));

    startTime = clock(); 
    msd_radix_sort(0, N - 1, 1);
    
    // ERROR : If elapsed time is less then 10ms
    if ( (clock() - startTime) < 10 ) {
        do {
            count++;
            // Copy origin data to data whenever loop started
            memcpy(data, dataORG, N * sizeof(unsigned int)); 
            msd_radix_sort(0, N - 1, 1);
        } while ( clock() - startTime < 10 );
    }
    else count++;
    
    duration = (double)(clock() - startTime) / (CLOCKS_PER_SEC / 1000);
    duration = (double)(duration / count);
    PrintArr(N);
    printf("Running_Time = %.3f ms\n", duration);

    free(aux);
    free(data);
    free(dataORG);
    return 0;
 }