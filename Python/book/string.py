#输出元音字母
'''
str="AEIOUaeiou"
alist=[]
for i in range(0,5):
    word=input(":")
    alist.append(word)
print(alist)

for i in range(0,5):
    w=alist[i]
    if w[0] in str:
        print(w)

#输入如一段字符统计单词个数单词之间空格分开
str=input()
alist=str.split()
print(len(alist))

'''
