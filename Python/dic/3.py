#用zip创建字典
key=[1,2,3,4,5,6,7]
values=['Mon','Tue','Wed','The','Fri','Sat','Sun']
k=int(input())
d=dict(zip(key,values))
print(d[k])