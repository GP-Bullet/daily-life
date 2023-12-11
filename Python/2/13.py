a=input().split(" ")
y=int(a[0])
m=int(a[1])
b1=[1,3,5,7,8,10,12]
b2=[4,6,9,11]
if m in b1:
    print("31")
elif m==2:
    if y%4==0 and y%100!=0 or y%400==0:
        print("29")
    else:
        print("28")
elif m in b2:
    print("30")
else:
    print("Error")