import math
n=int(input())
flag=0
for men in range(math.ceil(n/3)):
    for women in range(math.ceil(n/2)):
        for child in range(n):
            if child%2==0:
                if men*3+women*2+child==n and men+women+child==n:
                    print("men = %d,women = %d,child = %d"%(men,women,child))
                    flag=1

if flag==0:
    print("None")