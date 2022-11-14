str = input()
first, second = input().split(' ')
for i in range(len(str) , 0, -1):
    if str.rfind(first) == i - 1:
        print(i - 1, first)
    elif str.rfind(second) == i - 1:
        print(i - 1, second)
    str = str[:-1]

