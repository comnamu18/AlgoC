'''
20145523 KimSangHeon
Last updated date : 2018-03-09
'''
import sys
import time
import gc

#Print Result Function
def printArr(inputN):
    for i in inputN:
        print(i)
#Merge Sorting Function
def MergeSort(inputN, low, high):
    if low < high: 
        mid = int((low+high) / 2)
        MergeSort(inputN, low, mid)
        MergeSort(inputN, mid + 1, high)
        Merge(inputN, low, mid, high)
#Merge splitted Arrays
def Merge(inputN, low, mid, high):
    i = low
    j = mid + 1
    k = 0
    tmp = inputN[:]
    while i <= mid and j <= high:
        if inputN[i] > inputN[j]:
            tmp[k] = inputN[i]
            k = k + 1
            i = i + 1
        else:
            tmp[k] = inputN[j]
            k = k + 1
            j = j + 1
    #If still there is remaining things are exist
    while i <= mid : 
        tmp[k] = inputN[i]
        k = k + 1
        i = i + 1
    while j <= high :
        tmp[k] = inputN[j]
        k = k + 1
        j = j + 1

    for i in range(0,k):
        inputN[low + i] = tmp[i]

#Main part
if len(sys.argv) != 3: sys.exit('wrong input length') #ERROR : Wrong command line input
try :
    fp = open(sys.argv[2],"r")
except FileNotFoundError as e:
    print(str(e)) # ERROR : If file doesn't exist
try:
    N = int(sys.argv[1])
except ValueError as e:
    print(str(e)) # ERROR : If argv[1] is not integer
if N == 0 : sys.exit(0) # ERROR : If argv[1] is 0
inputN = []

#read data
for i in range(0, N):
    try:
        inp = int(fp.readline())
        if inp == '':#if N > K
            N = i
            break
    # ERROR : If file has data which is not integer
    except ValueError as e:
        print(str(e))

    inputN.append(inp)
inputTMP = inputN[:]
fp.close()
count = 0

startTime = time.monotonic()
MergeSort(inputN, 0, N - 1)
# ERROR : If elapsed time is less then 1000ms
if (time.monotonic() - startTime) < 1.000:
    while time.monotonic() - startTime < 1.000:
        count += 1
        # Copy origin data to inputN whenever loop started
        inputN = inputTMP[:]
        MergeSort(inputN, 0, N - 1)
else:
    count = 1
endTime = time.monotonic() - startTime

printArr(inputN)
print("Running time = " + str(endTime * 1000 / count) + " ms")
gc.collect()# free any kind of garbage memory
