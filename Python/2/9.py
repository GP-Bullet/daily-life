str = input()
list= str.split(sep=' ')
print (list)
if list[2] == '/':
    print((int(list[0]) / int(list[4])))
elif list[2] == '+':
    print(int(list[0]) + int(list[4]))
elif list[2] == '-':
    print(int(list[0]) - int(list[4]))
elif list[2] == '*':
    print(int(list[0]) * int(list[4]))
elif list[2] == '%':
    print(int(list[0]) % int(list[4]))
else:
    print('ERROR')