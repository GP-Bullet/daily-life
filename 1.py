import calendar

from calendar import *ort datetime
y = input('请输入年份')


dic = dict(enumerate(lis))

if y.isdigit() and m.isdigit() and d.isdigit() and 1<=int(m)<=12 and 1<=int(d)<=31 :

w = weekday(int(y),int(m),int(d))
print(dic[w])
