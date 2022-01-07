/*
int main() {


    char str[6] = "xiyou";
    strcat(str, "linux");
    printf("%s\n", str);


    return 0;
}

int main(){

    char str1[6]="xiyou";
    char str2[10]="linux";
    strcat(str1,str2);
    printf("%s\n",str1);


    return 0;
}
*/



#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){

    int len=5;
    char *str=malloc(,sizeof(char)*len);
    memcpy(str,"xiyou",5);
    str=realloc (str,len+strlen("linux")+1);
    strcpy(str+5,"linux");
    printf("%s\n",str);
}
