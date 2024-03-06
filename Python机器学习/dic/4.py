num=int(input())
T=0
F=0
for i in range(0,num,1):
    lista=(list(input().split()))
    setb=set(lista)
    if len(lista) > len(setb):
        T+=1
    else:
        F+=1
print("True=%d,False=%d"%(T,F))
