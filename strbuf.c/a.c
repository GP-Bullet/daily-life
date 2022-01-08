#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//?为什么要求内存只能成倍的增加

struct strbuf{
    int len;
    int alloc;//当前容量？我们每次动态分配的数组大小
    char *buf;
};
void strbuf_init(struct strbuf *sb, size_t alloc);
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t mem);	
void strbuf_release(struct strbuf *sb);
void strbuf_swap(struct strbuf *a, struct strbuf *b);
char *strbuf_detach(struct strbuf *sb, size_t *sz);
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second);
void strbuf_reset(struct strbuf *sb);




int main(){
    struct strbuf sb;
    strbuf_init(&sb,10);
    strbuf_attach(&sb,"xiyou",5,10);
    assert(strcmp(sb.buf,"xiyou")==0);
    strbuf_addstr(&sb,"linux");
    assert(strcmp(sb.buf,"xiyoulinux")==0);
    strbuf_release(&sb);
}


void strbuf_init(struct strbuf*sb,size_t alloc){
    sb->len=0;
    sb->alloc=alloc;
    sb->buf=(char*)malloc(sizeof(char)*alloc);
}
void strbuf_attach(struct strbuf*sb,void*str,size_t len,size_t alloc){//str的len和alloc
    while(sb->len+len>sb->alloc){
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc));
    }
    sb->len+=len;
    strcat(sb->buf,(const char*)str);
}
void strbuf_release(struct strbuf*sb){
    free(sb->buf);
}
void strbuf_swap(struct strbuf*a,struct strbuf*b){//空间不一样
    int temp1,temp2=0;                            //buf里面有内容吗
    temp1=a->len;                                 //不知道空间是否占满，realloc会影响其中内容
    a->len=b->len;
    b->len=temp1;
  //  temp2=a->alloc;
  //  a->alloc=b->alloc;
  //  b->len=temp2;

    //a->buf=(char*)realloc(a->buf,sizeof(char)*(a->alloc));
    //b->buf=(char*)realloc(b->buf,sizeof(char)*(b->alloc));
    int max=a->len>b->len?a->len:b->len;
    char*temp=(char*)malloc(sizeof(char)*max);
    while(a->alloc<max){
        a->alloc*=2;
        a->buf=(char*)realloc(a->buf,(sizeof(char)*(a->alloc)));
    }
    while(b->alloc<max){
        b->alloc*=2;
        b->buf=(char*)realloc(b->buf,(sizeof(char)*(b->alloc)));
    }
    strcpy(temp,a->buf);
    strcpy(a->buf,b->buf);
    strcpy(b->buf,temp);
    
}
char*strbuf_detach(struct strbuf *sb,size_t *sz){//原始内存取出是什么意思
    *sz=sb->len;
    return sb->buf;
}
int strbuf_cmp(const struct strbuf*first,const struct strbuf*second){
    //return strcmp(first->alloc,second->alloc);
    return first->alloc-second->alloc;
}
void strbuf_reset(struct strbuf*sb){//清空
    sb->len=0;
    strcpy(sb->buf,"");
}