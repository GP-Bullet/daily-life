n = int(input())
a = 1   #分子
b = 1   #分母
sum = 0
for i in range(n):
    s = a	   #存储分子
    a = a + b  #分子等于前一项分子分母的和
    b = s	   #分母等于前一项的分子
    sum += a / b
print("%.2f" % sum)
