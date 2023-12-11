a,b = map(int,input().split())
l = []
for i in range(a,b+1):
    if i%(3*5*7)==0:
        l.append(i)
#l = set(l)
print(len(l))
