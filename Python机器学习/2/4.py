n=input()
m1=n[0]
m2=n[1:]
m2=int(m2)

if m1=="$":
    print("￥{:.2f}".format(7*m2))
elif m1=="￥":
    print("${:.2f}".format(m2/7))
else:
    print("输入格式错误")