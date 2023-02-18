a=input()
b=input()
c=input()
print("%.2f"%a)
print("%e %E %.2%"%(a,a,a))
#练习
print(format(b,"2") "%0x"%b)




f = input()
int1 = int(input())
str1 = input()
s =float(f)
print("%.2f"%s)
print("%e %E %.2f%%"%(s, s, s*100))
print("{0:b}".format(int(int1)), end="")                 
print(" %x"%int(int1))
c=str.strip(str1)
print(str.upper(c))
print("%20s"%c)
print(c.center(20, "*"))
print("{} + {} = {}".format(s, int(int1), s+int(int1)))

