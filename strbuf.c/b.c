//Part 2B
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//?为什么要求内存只能成倍的增加
//?等号有没有
struct strbuf{
    int len;
    int alloc;//当前容量？我们每次动态分配的数组大小
    char *buf;
};

void strbuf_grow(struct strbuf*sb,size_t extra);
void strbuf_add(struct strbuf *sb, const void *data, size_t len);
void strbuf_addch(struct strbuf *sb, char c);
void strbuf_addstr(struct strbuf *sb, const char *s);
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2);
static inline void strbuf_setlen(struct strbuf *sb, size_t len);
static inline size_t strbuf_avail(const struct strbuf *sb);
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len);





void strbuf_grow(struct strbuf*sb,size_t extra){//长度扩大啥意思,是指内存还是len
    sb->len+=extra;
}
void strbuf_add(struct strbuf*sb,const void *data,size_t len){
    sb->len+=len;
    while(strbuf_avail(sb)>len){//有=号
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc));
    }
    strcat(sb->buf,(const char*)data);
}
void strbuf_addch(struct strbuf*sb,char c){
    strbuf_add(sb,&c,1);
}

void strbuf_addstr(struct strbuf *sb, const char *s){
    strbuf_add(sb,s,strlen(s));
}
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2){
    sb->len+=sb2->len;
    strbuf_add(sb,sb2->buf,sb2->len);
}
static inline void strbuf_setlen(struct strbuf *sb, size_t len){
    sb->len=len;
}
static inline size_t strbuf_avail(const struct strbuf *sb){
    return sb->alloc-sb->len-1;
}
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len){//strcpy的进一步理解及strncpy
    int i=sb->buf+pos;
    if(pos>sb->alloc){
        printf("this position is wrong!");
    }else{
        char*ptr=sb->buf+pos;
        sb->len+=len;
        while(strbuf_avail(sb)>len){//有=号
            sb->alloc*=2;
            sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc));
    }
        strcpy(sb->buf+pos,(const char*)data);
        while(){
            sb->buf++
        }
    }


}



