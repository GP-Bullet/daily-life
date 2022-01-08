#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct strbuf{
    int len;
    int alloc;//当前容量？我们每次动态分配的数组大小
    char *buf;
};

void strbuf_rtrim(struct strbuf *sb);//左端是哪?
void strbuf_ltrim(struct strbuf *sb);
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len);



void strbuf_rtrim(struct strbuf*sb){
    int i=0;
    while(sb->buf[i]==" ")
}