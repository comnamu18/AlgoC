/**
 * "3-way Quick Sort"
 * - ./3way_quick_sort <input_file_name> <N>
 * - measure running time of '3-way Quick Sort'
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
    unsigned int c = 0;
    for ( i = 0; i < N; i++) {
        printf("%d\n", data[i]);
    }
}
void choose_pivot (int *data, unsigned int n) {
    unsigned int rN;
    // If rn is 0, swap pivot means nothing so ignore rn = 0 case
    rN = rand() % n + 1;
    // Swap two numbers
    data[rN] = data[rN] + data[0];
    data[0] = data[rN] - data[0];
    data[rN] = data[rN] - data[0];
}
// Partition and move data[0] to correct possition
void Partition (int *data, unsigned int r,
                unsigned int *rI, unsigned int *rC) {
    int p = data[0];
    int tmp;
    unsigned int i = 0;  // For 1st Partition pointers
    unsigned int j = 1; // Loop
    unsigned int k = r; // For 2nd Partition pointers
    
    while ( data[k] == p ) { // Find right position of k
        if ( k < 1 ) { // If all same
            *rI = r + 1;
            return;
        }
        k--;
    }

    while ( j <= k) {
        if ( data[j] < p ) {
            i++;
            // Swap data[j] and data[i]
            tmp = data[j];
            data[j] = data[i];
            data[i] = tmp;
        }
        if ( data[j] == p ) {
            // Swap data[k] and data[j]
            tmp = data[j];  
            data[j] = data[k];
            data[k] = tmp;
            k--;
            j--; // Cause original data[k] is not partitioned yet
        }
        j++;
    }
    
    // Save 2nd partition's informations
    *rI = i;
    *rC = r - k + 1;

    if ( i != 0 ) { // If 1st Partition has something
        // Swap data[0] and data[i]
        data[0] = data[0] + data[i];
        data[i] = data[0] - data[i];
        data[0] = data[0] - data[i];
    }
    if ( k == r ) return; // If no duplicate
    // Set right position of 2nd Partition
    for ( j = r; j > k; j--) {
        i++;
        tmp = data[j];
        data[j] = data[i];
        data[i] = tmp;
    }
}
unsigned long three_way_quick_sort (int *data, unsigned int n) {
    unsigned long cnt = (n - 1); // number of comparisons
    unsigned int i, c; // i = 2nd Partition start point
                       // c = 2nd Partition length

    if ( cnt == 0 ) return cnt;
    // choose pivot and  always place it at first element of array
    choose_pivot(data, cnt);
    Partition(data, cnt, &i, &c);
    // If all Same then partition is not needed
    if ( i == n ) return cnt;
    // If 2nd Partition = 0 or 1, 1st partition must be sorted so skip it
    if ( i > 1 ) three_way_quick_sort(data, i);
    // If 2nd Partition = cnt-1 or cnt, 3rd partition must be sorted so skip it
    if ( i + c < cnt ) three_way_quick_sort(data + i + c, cnt - i - c + 1);

    return cnt;
}



int main (int argc, char* argv[]) {
    clock_t startTime;
    unsigned int N, oN, i; // To save original N value
    int input;
    int* data, *dataORG;
    double duration, count;
    char* ptr;
    FILE *fp;
    unsigned int d = 0;

    // ERROR : Wrong command line input
    if (argc != 3 ) exit(EXIT_FAILURE);

    srand(time(NULL));
    N = strtol(argv[2], &ptr, 10);
    count = 0;
    if ( *ptr != '\0' ) exit(EXIT_FAILURE); // ERROR : If argv[2] is'nt integer
    if ( N < 1 ) exit(EXIT_FAILURE); // ERROR : If N is less then 0
    oN = N; // Save Original N value
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
    three_way_quick_sort(data, N);
    // ERROR : If elapsed time is less then 1000ms
    if ( (clock() - startTime) < 1000 ) {
        do {
            count++;
            // Copy origin data to data whenever loop started
            memcpy(data, dataORG, N * sizeof(int)); 
            three_way_quick_sort(data, N);
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

