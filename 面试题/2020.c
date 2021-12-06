//*1
#if 0
#include<stdio.h>


int main(int argc, char *argv[])
{   int i;
    i--;printf("%d %d",i,sizeof(i));
    if (i > sizeof(i))
    {
    printf(">\n");
    }
    else
    {
    printf("<\n");
    }
    return 0;
}
#endif
//全局变量初始化默认i是0，i--变成-1
//sizeof()结果为无符号
//有符号和无符号比较全转无符号，而-1转成无符号
//10000000 00000000 00000000 00000001
//开头的1不再表示符号
//显然大于sizeof(i)=4

//*2
#if 0
#include<stdio.h>
#define A 2 + 2
#define B 3 + 3
#define C A * B
int main(int argc, char *argv[])
{      
    printf("%d %d",A,B);
    printf("%d\n", C);
    return 0;
}
#endif
//2+2*3+3=11
//11
//所以我们在定义的时候，养成一个良好的习惯，建议所有的层次都要加括号。只是一个简单的替换


//?int,double能不能认为它只是开辟了一个相应字节的空间
//*3
#if 0
#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
 char str[] = "Welcome to XiyouLinuxGroup";
 printf("%zu %zu\n", strlen(str), sizeof(str));
 return 0;
}
#endif
//26 27
//\0
//2021面试1.


//*4
#if 0
#include<stdio.h>
int main()
{
 int x = 0;
 static int num = 0;
 for (int i = 0; i < 5; i++)
 {
 x++;
 num++;
 }
 printf("x = %d num = %d\n", x, num);
 return 0;
}

#endif
//5  5
//?有什么不同吗?

//*5
#if 0
#include<stdio.h>
int main(int argc, char *argv[])
{
    int number;
    unsigned mask;
    mask = 1u << 31;
    scanf("%d", &number);
while (mask)
{
    printf("%d", (number & mask) ? 1 : 0);
    mask >>= 1;
}
    return 0;
}
#endif
//输出一个数的二进制
//?原理


//*6
#if 0
#include<stdio.h>
int main(int argc, char *argv[])
{
 char *str = "Xiyou Linux Group";
 printf("%c\n", *str + 1);
 printf("%c\n",'X'+1);
 return 0;
}
#endif
//Y
//*str='X'

//*7
#if 0
#include<stdio.h>
int main(int argc, char *argv[])
{
 double a = 3.14;
 float b = a;
 if ((float)a == b)
 {
 printf("Xiyou");
 }
 if (a != b)
 {
    printf("LinuxGroup\n");
    }
    if(a==(double)b){
        printf("1234");
    }
    if(a==b){
        printf("123456");
    }

 return 0;
}
#endif  
//float和double的存储方式
//1e-6表示1乘以10的负6次方。
//Math.abs(x)<1e-6其实相当于x==0
//1e-6(也就是0.000001)叫做epslon，用来抵消浮点运算中因为误差造成的相等无法判断的情况。它通常是一个非常小的数字(具体多小要看你的运算误差)
//比如说因为精度误差，用十进制举例，我们要算1/3+1/3+1/3==1(从数学上说，肯定相等)，但是因为精度问题，等号左边算出来是0.3333333+0.3333333+0.3333333=0.9999999，
//存在了误差，右边是1.0000000，那么如果直接用==，返回false，我们希望它被视作相等。那么就要两数相减取绝对值小于epslon的办法。
//if(fabs(a-b)<=eps_0) 
//float的精度误差在1e-6；
//所以要判断一个float型数：if(fabs(f) < 1e-6)；
//若满足，则相等
//double精度误差在1e-15
//要判断一个double型数：if(fabs(f) < 1e-15)；
//若满足，则相等
//?但是为什么相等的数不能用==那？


//*8
#if 0
#include<stdio.h>
int main(int argc, char *argv[])
{
 int a[6] = {0x6f796958, 0x694c2075, 0x2078756e, 0x756f7247, 0x30322070, 
0};
 printf(" %d\n", printf("%s", (char *)a));
    printf("%s", (char *)a);//Xiyou Linux Group 20,共20个数,返回值20，以及为什么正确输入
    printf(" %d\n","Xiyou Linux Group 20");
    char *str="Xiyou Linux Group 20";
    printf(str);
 return 0;
}
#endif
//与2021最后一题共同


//* 9
#if 0
#include<stdio.h>
int main(int argc, char *argv[])
{
 int a[2][3] = {{5, 7}, {5, 2}};
 int b[2][3] = {5, 7, 5, 2};
 int c[2][2] = {{5, 7}, {5, 2}};
 int d[2][2] = {5, 7, 5};
 printf("%d %d\n", a[1][1], b[1][1]);
 printf("%d %d\n", c[1][1], d[1][1]);
 return 0;
}
#endif
//2 0
//2 0


//*10
#if 0
#include<stdio.h>
int main(int argc, char *argv[])
{
    int a = 1;
    int *p=&a;

    printf("%d\n", *(char *)&a);
    printf("%d\n",*p);
    printf("%d\n",(char)a);
    printf("%d\n",(char)26);
}
#endif
//1


/*声明一个变量
如  int a=-1;
    unsigned int a=-1;
    double a=1.0;
能否这样理解：仅仅是开辟了一个相应大小的内存空间
应该不仅仅如此，还应该规定了它相应的存储方式如SEM，还是二进制补码
应该怎么更深的理解呢？


再就是printf("%d %u %lf")等等，又真正代表什么
是由二进制一堆01翻译成相应类型吗
与声明又如何对应呢
应该怎么更深的理解？*/


//*11
#if 0
#include<stdio.h>

int main(int argc, char *argv[])
{
         = "XiyouLinux\0";
 char *b = "XiyouLinux\0";
    a[5] = '\0';
 // b[5] = '\0';
    printf("%s\n", a);
 // printf("%s\n",b);
    return 0;
}
#endif



//*12       



//*13
#include<stdio.h>
void sort(int arr[], int size)
{
 int i, j, tmp;
 for (i = 0; i < size - 1; i++)
 {
 for (j = 0; j < size - i - 1; j++)
 {
 if (arr[j] > arr[j + 1])
 {
 tmp = arr[j];
 arr[j] = arr[j + 1];
 arr[j + 1] = tmp;
 }
 }
 }
}






