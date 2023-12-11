#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct strbuf{
    int len;
    int alloc;
    char *buf;
};


int strbuf_pandaun(struct strbuf*sb,char*s){
    int i=0;
    while(i<=sb->len){
        if(sb->buf[i]!=s[i]){
            return 0;
            i++;
        }
    }
    return 1;
}
