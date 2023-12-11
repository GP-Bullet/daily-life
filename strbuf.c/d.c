#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//暂行、、、、、、、、、、、、、、、、、、、、、、、、、、

struct strbuf{
    int len;
    int alloc;//当前容量？我们每次动态分配的数组大小
    char *buf;//为什么buf可以做一个缓冲区
};

__ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint);
__ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint);
int strbuf_getline(struct 
zstrbuf *sb, FILE *fp);         



__ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint){
    sb->buf=(char*)realloc(sb->buf,sizeof(char)*(hint?hint:8192));
    FILE*file=fdopen(fd,"r");
    sb->buf=realloc(sb->buf,sb->alloc+(hint?hint:8192));
    sb->alloc+=hint?hint:8192;
    char*line=(char*)malloc(BUFSIZ);
    size_t len=0;
    int sign=0;
    while(sign=getline(&line,&len,flie)!=EOF){
        strcat(sb->buf,line);
        sb->len+=strlen(line);
    }
    fclose(file);
    file=NULL;
    free(line);
    return sb->len;
}

__ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint){
    sb->buf=realloc(sb->buf,sb->alloc+(hint?hint:8192));
    sb->alloc+=hint?hint:8192;
    FILE*file=fopen(path,"r");
    char*line=(char*)malloc(BUFSIZ);
    size_t len=0;
    int sign=0;
    while(sign=getline(&line,&len,file)!=EOF){
        strcat(sb->buf,line);
        sb->len+=strlen(line);
    }
    fclose(file);
    file=NULL;
    free(line);
    return sb->len;
}




int strbuf_getline(struct strbuf *sb, FILE *fp){
    size_t len=0;
    int sign=0;
    char*line=(char*)malloc(1000);
    if(sign=getline(&line,&len,fp)){
        len=strlen(line);
        sb->len+=len;
        if(sb->len>=sb->alloc){
            sb->alloc*2;
            realloc(sb->buf,sb->alloc);
        }
        strcat(sb->buf,line);
    }
    free(line);
    return len;
}
