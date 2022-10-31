n=input("")
if n[2]== "0":
    if n[1]=="0":
        print(n[0])
    else:
        print(n[-2::-1])
else:
    print(n[-1::-1])