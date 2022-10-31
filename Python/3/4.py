n=int(input(""))
if(n==0):
    print(0)
else:
    sum=2.0
    fenzi=1.0
    fenmu=2.0
    for i in range(n):        
        fenzi=fenzi+fenmu
        fenmu=fenzi
        sum+=fenzi/fenmu
    print("%.2f"%sum)