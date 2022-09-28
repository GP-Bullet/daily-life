#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100 //顺序栈存储空间的初始分配址
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef char SElemType;

typedef struct
{
    char *base; //栈底指针
    char *top; //栈顶指针
    int stacksize; //栈可用的最大容量
}SqStack;

Status InitStack(SqStack *S);//构造一个空栈s
Status Push(SqStack *S,char e);//插入元素e为新的栈顶元素
Status Pop(SqStack *S,char *e);//删除s的栈顶元素,用e返回其值
SElemType GetTop(SqStack S);//返回s的栈顶元素,不修改栈顶指针
Status In(char e);//判断读入字符是否为运算符
SElemType Precede(char a,char b);//比较运算符的优先级，a为纵轴值，b为横轴值
int Operate(int i,char theta,int j);//计算a(theta)b结果
char EvaluateExpression();//算术表达式求值的算符优先算法，设OPTR和OPND分别为运算符栈和操作数栈

int main()
{
    printf("请输入算术表达式,并以#结束(操作数只能是一位数)：");
    printf("表达式结果是：%d",EvaluateExpression());
    return 0;
}

Status InitStack(SqStack *S)
{//构造一个空栈s
    S->base=(char *)malloc(MAXSIZE*sizeof(char));//为顺序栈动态分配一个最大容量为MAXSIZE的数组空间
    if(!S->base) exit(OVERFLOW); //存储分配失败
    S->top=S->base; //top初始为base，空栈
    S->stacksize=MAXSIZE; //stacksize置为栈的最大容量MAXSIZE
 return OK;
}

Status Push(SqStack *S,char e)
{//插入元素e为新的栈顶元素
 if(S->top-S->base==S->stacksize) return ERROR; //栈满
    *S->top++=e; //元素e压入栈顶，栈顶指针加1
    return OK;
}

Status Pop(SqStack *S,char *e)
{//删除s的栈顶元素，用e返回其值
 if(S->top==S->base) return ERROR; //栈空
    *e=*--S->top; //栈顶指针减1，将栈顶元素赋给e
    return OK;
}     

SElemType GetTop(SqStack S)
{//返回s的栈顶元素，不修改栈顶指针
 if(S.top!=S.base) //栈非空
    return *(S.top-1); //返回栈顶元素的值，栈顶指针不变
}

Status In(char e)
{//判断读入字符是否为运算符
 if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#')
        return OK;//是
    else
        return ERROR;//不是
}

SElemType Precede(char a,char b)
{//比较运算符的优先级，a为纵轴值，b为横轴值
    char f;
    if(a=='+'||a=='-')
    {
        if(b=='+'||b=='-'||b==')'||b=='#')
        f='>';
        else if(b=='*'||b=='/'||b=='(')
        f='<';
    }
    else if(a=='*'||a=='/')
    {
        if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
        f='>';
        else if(b=='(')
        f='<';
    }
    else if(a=='(')
    {
        if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
        f='<';
        else if(b==')')
        f='=';
    }
    else if(a==')')
    {
        if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
        f='>';
    }
    else if(a=='#')
    {
        if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
        f='<';
        else if(b=='#')
        f='=';
    }
    return f;
}

int Operate(int i,char theta,int j)
{//计算a(theta)b结果
    int result;
    switch(theta) {
        case '+': result = i + j; break;
        case '-': result = i - j; break;
        case '*': result = i * j; break;
        case '/': result = i / j; break;
    }
    return result;
}

char EvaluateExpression()
{//算术表达式求值的算符优先算法，设OPTR和OPND分别为运算符栈和操作数栈
    SqStack OPND,OPTR;
    int ch; //把读入的字符转换为整数型，即ASCII表值
    char a,b,theta,x; //ch为当前读入字符, theta为运算符，x仅仅只是变量寄存弹出值，对计算表达式无影响
    InitStack(&OPND); //初始化OPND栈，寄存操作数和运算结果
    InitStack(&OPTR); //初始化OPTR栈，寄存运算符
    Push(&OPTR,'#');
    ch=getchar();
    while(ch!='#'||GetTop(OPTR)!='#')
    {
        printf(" %c\n",ch);
        if(!In(ch))//ch不是运算符则进OPND栈
        {
            ch=ch-48;//数字字符转换为对应整数
            Push(&OPND,ch);
            ch=getchar();
        }
        else
        {
            switch(Precede(GetTop(OPTR),ch))
            {//优先级选择
            case '<':
                Push(&OPTR,ch);
                ch=getchar();
                break;
            case '>':
                Pop(&OPTR,&theta);
                Pop(&OPND,&b);
                Pop(&OPND,&a);
                Push(&OPND,Operate(a,theta,b));
                break;
            case '=':
                Pop(&OPTR,&x);
                ch=getchar();
                break;
            }
        }
    }

    return GetTop(OPND);
}