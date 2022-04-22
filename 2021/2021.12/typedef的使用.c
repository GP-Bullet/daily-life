//如A是int的别名
#include<stdio.h>

typedef int A;
//通过命名来更好地理解数据类型
//是对类型的封装


typedef struct stu{
    char name[20];
    int age;
    char sex;
}STU;

int main(){
    A a=10;
    printf("a=%d",a);


    STU body1,body2;
    //等价于stuct stu body1,body2;
    return 0;



}  
