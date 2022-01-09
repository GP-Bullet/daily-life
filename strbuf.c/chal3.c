#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct strbuf{
    int len;
    int alloc;
    char *buf;
};


char* strbuf_copy(struct strbuf*sb,int begin,int end){
    char*ptr=(char*)malloc(sizeof(char)*(end-begin));
    strcpy(ptr,sb->buf+begin);

    return ptr;
}