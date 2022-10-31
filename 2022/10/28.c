#include<stdio.h>
int a = 3;
void test()
{
	int a = 1;
	a += 1;
    int i=i+1;
    printf("a=%d\n", i);
     {
        printf("a=%d\n", a);
         int a;
	     printf("a=%d\n", a);
         a=a;
         printf("a=%d\n", a);
         a=a+1;
         printf("a=%d\n", a);
     }
	printf("a=%d\n", a);
	
}
int main()
{
	test();
	printf("a=%d\n", a);
	return 0;
}
