#x=list(map(int,input().split(",")))   
x=eval(input())
for m in range(len(x)): 
    if x[m]==max(x): 
        print(m)  
