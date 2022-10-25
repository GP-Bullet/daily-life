x,y=eval(input(""))
#为什么没有存括号
if x>0 and y>0 :
    print("第一象限")
elif x>0 and y<0 :
    print("第四象限")
elif x<0 and y>0 :
    print("第二象限")
else :
    print("第三象限")