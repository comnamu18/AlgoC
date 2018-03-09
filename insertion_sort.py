'''
20145523 KimSangHeon
Last updated date : 2018-03-09
'''
import sys
import datetime
import gc

#Print Result Function
def printArr(inputN):
    for i in inputN:
        print(i)
#Insertion Sorting Function
def InsertionSort (inputN, N) :
    for i in range(1, N):
        max = inputN[i]
        j = i - 1
        while j >= 0 and inputN[j] < max:
            inputN[j + 1] = inputN[j]
            inputN[j] = max
            j = j - 1

#Main part
if len(sys.argv) != 3: sys.exit('wrong input length')
fp = open(sys.argv[2],"r")
if fp is None: sys.exit('wrong input in file name(argv[2])')
N = int(sys.argv[1])
if type(N) is not int: sys.exit('wrong input in number(argv[1])')
inputN = []

#read data
for i in range(0,N):
    inp = int(fp.readline())
    if inp == '':#if N > K
        N = i
        break

    inputN.append(inp)

fp.close()

startTime = datetime.datetime.now()
InsertionSort(inputN, N)
endTime = datetime.datetime.now() - startTime

printArr(inputN)
print("Running time = " + str(int(endTime.total_seconds() * 1000)) + "ms")
gc.collect()# free any kind of garbage memory