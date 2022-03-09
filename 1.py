import calendar

from calendar import *

import datetime

y = input('请输入年份')

m = input('请输入月份')

d = input('请输入日')

lis = ['星期一','星期二','星期三','星期四','星期五','星期六','星期日',]

dic = dict(enumerate(lis))

if y.isdigit() and m.isdigit() and d.isdigit() and 1<=int(m)<=12 and 1<=int(d)<=31 :

    w = weekday(int(y),int(m),int(d))

print(dic[w])