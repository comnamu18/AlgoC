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

fp.close()#free fp

startTime = datetime.datetime.now()
MergeSort(inputN, N)
endTime = datetime.datetime.now() - startTime

printArr(inputN)
print("Running time = " + str(int(endTime.total_seconds() * 1000)) + "ms")
gc.collect()# free any kind of garbage memory