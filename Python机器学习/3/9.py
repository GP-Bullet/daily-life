n=int(input(""))
if n==0:
    print("average = 0.00")
    print("count = 0")
else:
    str=input("")
    score=list(map(int,str.strip().split()))
    count=0
    for i in range(len(score)):
        if score[i]< 60:
            count+=1
    avg=sum(score)/len(score)
    print("average = %.2f"%avg)
    print("count = %d"%count)