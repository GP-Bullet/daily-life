#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct strbuf{
    int len;
    int alloc;
    char *buf;
};

struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max);

struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max){
    
}
