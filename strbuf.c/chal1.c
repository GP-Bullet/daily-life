#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct strbuf{
    int len;
    int alloc;
    char *buf;
};

struct strbuf *strbuf_split_buf(const char *str, size_t len, char terminator, int max);

struct strbuf *strbuf_split_buf(const char *str, size_t len, char terminator, int max){
    //str[i]='\0'
    //str+i='\0'
    struct strbuf *sb=(struct strbuf*)malloc(sizeof(struct strbuf)*max);

    
    int count=0;
    int i=0;
    while(i<len){
        if(str[i]==terminator&&count<=max){
            count++;
        //    strcpy(str+i,"\0");
        }
    }

    
    return sb;
}
