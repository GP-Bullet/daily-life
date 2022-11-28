#不会
a = eval(input())#合适的输入
b = eval(input())
for k in b.keys():
    a[k] = a.get(k, 0) + b[k]

t = list(a.items())
t.sort(key=lambda x : ord(x[0]) if type(x[0]) == str else x[0])
c = str(dict(t)).replace(' ', '').replace("'", '"')
print(c)
