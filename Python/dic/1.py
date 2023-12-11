#不会写
dic = {}
while True:
    s = input()        #循环输入，\n 结尾
    if s == "!!!!!":
        break
    for ch in "!.,:*?":
        s = s.replace(ch," ") #在s中 把ch 的循环的符号 替换为空格
    s = s.lower()   
    ls = s.split()  #切片保存在列表中 
    for i in ls:
        if i in dic:     # in 查询在不在字典
            dic[i] += 1
        else:
            dic[i]=1

print(len(dic))   #共有几个单词
li = list(dic.items()) #转为列表
li.sort(key=lambda x:x[0])
li.sort(key=lambda x:x[1],reverse=True)
count = 0
for i in li:   #可以很方便的遍历全部
    print("{}={}".format(i[0],i[1])) #格式输出
    count += 1
    if count==10:
        break

