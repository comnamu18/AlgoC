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
def MergeSort(inputN, N):
    if N < 2: return
    mid = int(N / 2)
    #Split input Array into Two arrays
    Left = inputN[:mid]
    Right = inputN[mid:]
    #Keep Spliting till less then two components left
    MergeSort(Left, mid)
    MergeSort(Right, N - mid)
    #Merge splited arrays
    Merge(inputN, Left, Right, N)

def Merge(inputN, Left, Right, N):
    i = 0
    j = 0
    k = 0
    LeftN = int(N / 2)
    RightN = N - LeftN
    while i < LeftN and j < RightN:
        if Left[i] > Right[j]:
            inputN[k] = Left[i]
            k = k + 1
            i = i + 1
        else:
            inputN[k] = Right[j]
            k = k + 1
            j = j + 1
    #If still there is remaining things are exist
    while i < LeftN : 
        inputN[k] = Left[i]
        k = k + 1
        i = i + 1
    while j < RightN :
        inputN[k] = Right[j]
        k = k + 1
        j = j + 1

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
MergeSort(inputN, N)
# ERROR : If elapsed time is less then 1000ms
if (time.monotonic() - startTime) < 1.000:
    while time.monotonic() - startTime < 1.000:
        count += 1
        # Copy origin data to inputN whenever loop started
        inputN = inputTMP[:]
        MergeSort(inputN, N)
else:
    count = 1
endTime = time.monotonic() - startTime

printArr(inputN)
print("Running time = " + str(endTime * 1000 / count) + " ms")
gc.collect()# free any kind of garbage memory