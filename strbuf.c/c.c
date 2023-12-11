#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct strbuf{
    int len;
    int alloc;//当前容量？我们每次动态分配的数组大小
    char *buf;
};

void strbuf_rtrim(struct strbuf *sb);//左端是哪?->最开始的左端 还是  从左端开始
void strbuf_ltrim(struct strbuf *sb);
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len);


/*
void strbuf_rtrim(struct strbuf*sb){
    int i=0;
    while(sb->buf[i]=='\0'){
        if(sb->buf[i]==' '){
            strcpy(sb->buf+i,"");
            sb->len--;
        }
        i++;
    }

}*/
//*这俩函数名字是反的
void strbuf_rtrim(struct strbuf*sb){
    int i=0;
    while(sb->buf[i]==' '){
        sb->len--;
        i++;
    }
    char*ptr=(char*)malloc(sizeof(char)*(sb->len+1));
    strcpy(ptr,sb->buf+i);
    fflush(stdin);
    strcpy(sb->buf,ptr);
}

void strbuf_ltrim(struct strbuf*sb){
    int i=sb->len-1;
    while(sb->buf[i]==' '){
        sb->len--;
        sb->buf[i]=='\0';
        i--;
    }
}
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len){
    if(pos<=sb->len&&len<=sb->len-pos){
        strcpy(sb->buf+pos,sb->buf+pos+len);
    }else{
        printf("the pos or len is wrong!");
    }
}

