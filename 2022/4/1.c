#include<stdio.h>
int main(){
char* str[] = { "This","is","Xiyou","Mobile" };
char** p = str + 1;
printf("%s\n", str[0]);
str[0] = str[2]+ 2;
printf("%s\n", str[0]);
str[1] = *(p + 1);
printf("%s\n", str[0]);//\n
printf("%s\n", str[1]);//Mobile
return 0;
}