'''
20145523 KimSangHeon
Last updated date : 2018-03-17
'''
import sys
import time

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
InsertionSort(inputN, N)
# ERROR : If elapsed time is less then 1000ms
if (time.monotonic() - startTime) < 1.000:
    while time.monotonic() - startTime < 1.000:
        count += 1
        # Copy origin data to inputN whenever loop started
        inputN = inputTMP[:]
        InsertionSort(inputN, N)
else:
    count = 1
endTime = time.monotonic() - startTime

printArr(inputN)
print("Running time = " + str(endTime * 1000 / count) + " ms")