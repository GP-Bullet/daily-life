w=float(input())
h=float(input())
b=w*703/(h*h)
print('BMI = %.2f'%(int(b*100)/100))
if b>25:
    print('体重超重')
elif b<18.5:
    print('体重过轻')
else:
    print('体重最佳')