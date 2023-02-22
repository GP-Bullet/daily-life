import math
try:
    x=float(input())
    if x>0:
        print("f(%.2f) = %.2f"%(x,math.cos(x)+math.exp(x)))
    else:
        print("f(%.2f) = 0.00"%x)
except:
    print("Input Error")