
//将串r中所有其值为ch1的字符换成ch2的字符
void chage(char *r,char ch1,char ch2)
{
for(int i=0;i<max;i++)//max为定义r数组最大的值
{
if(r[i]==ch1)
r[i]=ch2;
}
}
'2
//将串r中所有字符按照相反的次序仍存放在r中
void chageadd(char *r)
{
char temp;
int make=max-1;//max为定义r数组最大的值
for(int a=0;a<=max/2;a++)
{
temp=r[a];
r[a]=r[make-a];
r[make-a]=temp;
}
}
'3//删除r中值为ch
void del(char *r,char ch)
{
int count=max;//标记删除表后的实际长度
for(int i=0;i<count;i++)
{
if(r[i]==ch)
{
for(int t=i;t<count;t++)
r[i]=r[i+1];
}
count--;
}
if(count=max)
cout<<"r中无ch!";
}
'4 //从串r1中第index个字符起求出首次与字符r2相同的子串的起始位置
iint indexW(char *r,char *r2,int index)
{
int k,j,a;
for( a=index-1;r[a];a++)
for( k=0,j=a;r[j]==r2[k];k++,j++)
if(r2[k+1]==NULL)
return j;
cout<<"不存在";
return 0;
}


Status Replace(HString *S, HString T, HString V) 
{                                                // 初始条件：串S，T和V存在，T是非空串
    
    int i = 1;       
    if (StrEmpty(T)) 
        return ERROR;
    do
    {
        i = Index(*S, T, i); // 结果i为从上一个i之后找到的子串T的位置
        if (i)               // 串S中存在串T
        {
            StrDelete(S, i, StrLength(T)); // 删除该串T
            StrInsert(S, i, V);            // 在原串T的位置插入串V
            i += StrLength(V);             // 在插入的串V后面继续查找串T
        }
    } while (i);
    return OK;
}

