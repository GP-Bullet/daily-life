#include<stdio.h>
#include<math.h>

void print_menu(void);
int choice_menu(void);
void calculation(int cmd);
double fun_add(double x,double y);
double fun_sub(double x,double y);
double fun_mul(double x,double y);
double fun_div(double x,double y);
double get_number(void);

int main(){
    int n;

    while((n=choice_menu())){
        calculation(n-1);
    }

    return 0;
}

int choice_menu(){
    int num;

    print_menu();
    for(int i=0;!scanf(" %d",&num)||num<1||num>5;i++){
        while(getchar()!='\n');

        if((i+1)%10 ==0)
            print_menu();
        
        puts("无效输入，请输入整数");
    }
    while(getchar()!='\n');

    return(num==5? 0: num);
}

void print_menu(){
    static const char* menu[]=  //?为啥
    {
		"======================================" ,
		"请选择您需要的功能:" ,
		"1 加			2 减" ,
		"3 乘			4 除" ,
		"5 退出" ,
		"======================================" 
	};
    //?system(cls);

    for(int i=0;i<sizeof(menu);i++){
        puts(menu[i]);
    }
}

void calculation(int cmd){
    double r,n1,n2;
    double(*f[4])(double x,double y)={
        fun_add,fun_sub,fun_mul,fun_div
    };

    puts("请输入您要计算的第一个数");
    n1=get_number();
    puts("请输入您要计算的第二个数");
    n2=get_number();
    printf("计算结果为：%.2lf\n",f[cmd](n1,n2));
    //!system("pause");
}

double fun_add(double x,double y){
    double sum=0;

    sum=x+y;

    return sum;
}

double fun_sub(double x,double y){
    double results =0;
    results=x-y;

    return results;
}

double fun_mul(double x,double y){
    double results=0;

    results=x*y;

    return results;
}


double fun_div(double x,double y){
    double results=0;

    if(y==0){
        fputs("参数错误：除数不能为0\n",stderr);
    }else
        results=x/y;
    return results;
}

double get_number(){
    double x=0;
    while(!scanf(" %lf",&x)){
        while(getchar()!='\n');
        puts("无效输入，请输入正确的数字");
    }
    while(getchar()!='\n');

    return x;

}

