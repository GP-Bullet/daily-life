#include"strbuf.h"


void strbuf_init(struct strbuf*sb,size_t alloc){
    sb->len=0;
    sb->alloc=alloc;
    sb->buf=(char*)malloc(sizeof(char)*alloc);
}


void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    strbuf_init(sb,alloc);
    sb->len=len;
    sb->buf=(char*)str;

}