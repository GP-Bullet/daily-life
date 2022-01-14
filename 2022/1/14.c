ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint){
    sb->buf=(char*)realloc(sb->buf,sb->alloc+(hint?hint:8192));
    sb->alloc+=hint?hint:8192;
    FILE*file=fopen(path,"r");
    char*line=(char*)malloc(BUFSIZ);
    size_t len=0;
    int sign=0;
    while(sign==getline(&line,&len,file)!=EOF){
        strcat(sb->buf,line);
        sb->len+=strlen(line);
    }
    fclose(file);
    file=NULL;
    free(line);
    return sb->len;
}
