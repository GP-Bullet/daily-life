from os import lseek


等号赋值是引用

b_list=list(input("输入数据:"))
a_list=[]
for i in b_list.split(","):
    a_list.append(i)