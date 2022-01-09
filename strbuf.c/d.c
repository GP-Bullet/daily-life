#include<stdio.h>
#include<stdlib.h>
#include<string.h>



struct strbuf{
    int len;
    int alloc;//当前容量？我们每次动态分配的数组大小
    char *buf;//为什么buf可以做一个缓冲区
};

__ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint);
__ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint);
int strbuf_getline(struct strbuf *sb, FILE *fp);         



__ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint){
    sb->buf=(char*)realloc(sb->buf,sizeof(char)*(hint?hint:8192));


}


