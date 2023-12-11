number=input()
if(number[-1]=="C" or number[-1]=="c"):
    C=float(number[0:-1])
    F=C*1.8+32
    print("%.2fF"%F)
elif(number[-1]=="f" or number[-1]=="F"):
    F=float(number[0:-1])
    C=(F-32)/1.8
    print("%.2fC"%C)
else:
    print("Error")