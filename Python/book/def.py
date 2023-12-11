def isprime(n):
    for i in range(2,n):
        if(n%i==0):
            return 0
        return 1

m=int(input())
flag=isprime(m)
