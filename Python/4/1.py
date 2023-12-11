alist=list(map(int,input().split()))
blist=list(map(int,input().split()))
alist.extend(blist)
clist=list(set(alist))
print(clist)

