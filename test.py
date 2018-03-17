import time
import sys

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

now= time.monotonic()
#read data
for i in range(0,N):
    try:
        inp = int(fp.readline())
        if inp == '':#if N > K
            N = i
            break
    # ERROR : If file has data which is not integer
    except ValueError as e:
        print(str(e))

    inputN.append(inp)

fp.close()
end = time.monotonic()

print(end-now)