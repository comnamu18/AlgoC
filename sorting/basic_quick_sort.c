/**
 * "Quick Sort"
 * - ./basic_quick_sort <input_file_name> <N>
 * - measure running time of 'Quick Sort'
 *
 * KimSangHeon / 20145523
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

//Print Result Function
void PrintArr ( int* data, unsigned int N ) {
    unsigned int i;
    for ( i = 0; i < N; i++) {
        printf("%d\n", data[i]);
    }
}
// Choose random pivot and swap it with data[0]
void choose_pivot (int *data, unsigned int n) {
    unsigned int rN;
    // If rn is 0, swap pivot means nothing so ignore rn = 0 case
    rN = rand() % n + 1;
    // Swap two numbers
    data[rN] = data[rN] + data[0];
    data[0] = data[rN] - data[0];
    data[rN] = data[rN] - data[0];
}
// Partition and move data[0] ro correct possition
unsigned int Partition (int *data, unsigned int r) {
    int p = data[0];
    int tmp;
    unsigned int i = 0;
    unsigned int j = 1;

    for ( j; j <= r; j++ ) {
        if ( data[j] < p ) {
            i++;
            // Swap data[j] and data[i]
            tmp = data[j];
            data[j] = data[i];
            data[i] = tmp;
        }
    }
    if ( i == 0 ) return i; // If i == l, then nothing happen
    // Swap data[0] and data[i]
    data[i] = data[i] + data[0];
    data[0] = data[i] - data[0];
    data[i] = data[i] - data[0];

    return i;
}
// recursively call Quick Sort
unsigned long quick_sort (int *data, unsigned int n) {
    unsigned long cnt = (n - 1); // number of comparisons
    unsigned int i;

    if ( cnt == 0 ) return cnt;
    // choose pivot and  always place it at first element of array
    choose_pivot(data, cnt);
    i = Partition(data, cnt);
    // If i = 0 or 1, left partition must be sorted so skip it
    if ( i > 1 ) quick_sort(data, i);
    // If i = cnt -1 or cnt, right partition must be sorted so skip it
    if ( i + 1 < cnt ) quick_sort(data + i + 1, cnt - i);

    return cnt;
}

int main (int argc, char* argv[]) {
    clock_t startTime;
    unsigned int N, oN, i; // Save original N for print statements
    int input;
    int* data, *dataORG;
    double duration, count;
    char* ptr;
    FILE *fp;

    // ERROR : Wrong command line input
    if (argc != 3 ) exit(EXIT_FAILURE);

    srand(time(NULL));
    N = strtol(argv[2], &ptr, 10);
    count = 0;
    if ( *ptr != '\0' ) exit(EXIT_FAILURE); // ERROR : If argv[2] is'nt integer
    if ( N < 1 ) exit(EXIT_FAILURE); // ERROR : If N is less then 0
    oN = N; // Save original N
    data = (int*)malloc(sizeof(int) * N);
    dataORG = (int*)malloc(sizeof(int) * N);

    fp = fopen(argv[1], "r");
    // ERROR : If file doesn't exist
    if ( fp == NULL ) exit(EXIT_FAILURE);
    for ( i = 0; i < N; i++ ) {
        if ((fscanf(fp, "%d\n", &input)) == EOF ){//If N>K
            N = i;
            break;
        }
        data[i] = input;
    }
    fclose(fp);
    //Save original data to another dataORG
    memcpy(dataORG, data, N * sizeof(int));

    startTime = clock(); 
    quick_sort(data, N);
    // ERROR : If elapsed time is less then 1000ms
    if ( (clock() - startTime) < 1000 ) {
        do {
            count++;
            // Copy origin data to data whenever loop started
            memcpy(data, dataORG, N * sizeof(int)); 
            quick_sort(data, N);
        } while ( clock() - startTime < 1000 );
    }
    else count++;
    duration = (double)(clock() - startTime) / (CLOCKS_PER_SEC / 1000);
    duration = (double)(duration / count);
    PrintArr(data, N);
    // Please keep these printf statements!
    printf("N = %7d,\tRunning_Time = %.3f ms\n", oN, duration);

    free(data);
    free(dataORG);
    return 0;
}

