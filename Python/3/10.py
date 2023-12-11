n=eval(input(""))
if n%2==0:
    for i in range(1,n/2+1):
        sum+=(n+1-i)*i
print(sum)