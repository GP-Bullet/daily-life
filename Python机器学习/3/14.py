n=int(input())
x=[]
c=0
for i in range(n):
    print(" "*3*(n-i-1),end='')#根据规律发现题目要求的格式，即第一个数字的位置
    a=[1]
    x.append(a)#第一个数字为“1”
    for j in range(1,i):
        a.append(x[i-1][j-1]+x[i-1][j])#依次往列表后加上杨辉三角数
    a.append(1)#记得最后一位是“1”
    if i==0:#把第一行单独拿出来输出，毕竟每一行列表里前后都有“1”
        print("%d"%1)
        continue
    c=len(a)#计算列表内元素个数
    b=list(map(int,a))#将元素转变为int类型
    for k in range(c):
        if k==0:
            print(b[k],end='')
            continue
        print("%6d"%b[k],end='')
    print()