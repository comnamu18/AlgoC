import sys

def InsertionSort (input, N) :
    for i in range(1, N):
        max = input[i]
        j = i - 1
        while j >= 0 and input[j] < max:
            input[j + 1] = input[j]
            j = j - 1
        
        input[j] = max

if len(argv) != 3: sys.exit('wrong input')
fp = open(argv[2],"r")
N = argv[1]
for i in range(0,N):
    