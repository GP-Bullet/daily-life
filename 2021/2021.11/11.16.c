
//计算机组成


/*小细节：1、fflush(stdin);清空输入缓冲区
//!n和回车

2、getchar()
getche()
getch()

3、switch  case


4、for和while相互转化
a;
while(b){
    d;
    c;
}






if...goto万不得已才用--跳出多重for循环
a:if(i<=100)//
{
    s=s+i;
    ++i:
    goto a;
}

goto作为if的执行语句   C和指针  


break---跳出当前循环
continue---结束本次循环（）

//todo写写线代吧
//!代码格式的问题   进度的问题   算法积累的问题
//?
//*
//

a=-a，正负交替
//求和--找规律
1
*/


//阶乘（初级）
#include<stdio.h>
int main(){
    int sum=0,a=1;
    for(int i=1;i<6;i++){
        a=a*i;
        sum=sum+a;
    }
    printf("%d",sum);
    return 0;

}
//longlong
//高精度