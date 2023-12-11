lirun=int(input(""))
jiangjin=0.0
if lirun<=100000:
    jiangjin=lirun*0.1
elif lirun<=200000:
    jiangjin = 10000+(lirun-100000)*0.075
elif lirun<=400000:
    jiangjin = 10000+7500+(lirun-200000)*0.05
elif lirun<=600000:
    jiangjin = 10000+7500+10000+(lirun-400000)*0.03
elif lirun<=1000000:
    jiangjin=10000+7500+10000+6000+(lirun-600000)*0.015
else:
    jiangjin=10000+7500+10000+6000+6000+(lirun-1000000)*0.01

if lirun<0:
    print(0)
else:
    print(jiangjin)