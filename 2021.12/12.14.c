#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
char *convert(const char *s);
int main()
{
    char *str="XiyouLinux Group 2022";
    char *temp=convert(str);
    puts(temp);
    return 0;
}
char *convert(const char *s)
{
    char t[50] = {'\0'};
    for(int i = 0;*s!='\0';i++)
    {
        if(*s>='a'&&*s<='z')
            t[i]=toupper(*s);
        else if(*s>='A'&&*s<='Z')
            t[i]=tolower(*s);
        else
            t[i]=*s;
            *s++;
    }
    return t;
}