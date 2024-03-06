#注意输入输出格式怎么搞

#键值互换
'''
a_dict={'a':11,'b':22,'c':33}
b_dict={}
for i in a_dict:
    b_dict[a_dict[i]]=i
print(b_dict)
'''

#统计单词出现次数

sentence = input("请输入一串字符：")
# 将所有单词转换为小写，避免大小写造成的重复计算
sentence = sentence.lower()

# 分割单词
words = sentence.split()

# 创建一个空字典，用于存储每个单词出现的次数
word_count = {}

# 遍历单词列表，统计每个单词出现的次数
for word in words:
    if word in word_count:
        # 如果单词已经在字典中出现过，就将它的计数加1
        word_count[word] += 1
    else:
        # 如果单词还没有出现过，就将它加入字典，并将计数设为1
        word_count[word] = 1

# 输出每个单词及其出现的次数
for word, count in word_count.items():
    print(word, ":", count)

