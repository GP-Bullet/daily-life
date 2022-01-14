//Part 2A

#include"strbuf.h"


//1

void strbuf_init(struct strbuf*sb,size_t alloc){
    sb->len=0;
    sb->alloc=alloc;
    sb->buf=(char*)malloc(sizeof(char)*alloc);
}

void strbuf_attach(struct strbuf*sb,void*str,size_t len,size_t alloc){//str的len和alloc

    /* while(sb->len+len>sb->alloc){
        sb->alloc*=2;
        sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc));
    }      
    sb->len+=len;
    strcat(sb->buf,(const char*)str);
    */
    strbuf_init(sb,alloc);
    sb->len=len;
    sb->buf=(char*)str;

}
void strbuf_release(struct strbuf*sb){
    free(sb->buf);
}
void strbuf_swap(struct strbuf*a,struct strbuf*b){//空间不一样
    int temp1,temp2=0;                            //buf里面有内容吗
    temp1=a->len;                                 //不知道空间是否占满，realloc会影响其中内容
    a->len=b->len;
    b->len=temp1;

    temp2=a->alloc;
    a->alloc=b->alloc;
    b->alloc=temp2;

    //a->buf=(char*)realloc(a->buf,sizeof(char)*(a->alloc));
    //b->buf=(char*)realloc(b->buf,sizeof(char)*(b->alloc));
    /*  int max=a->len>b->len?a->len:b->len;
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
*/
    char*temp=(char*)malloc(sizeof(char)*a->len);
    temp=a->buf;
    a->buf=b->buf;
    b->buf=temp;    
}


char*strbuf_detach(struct strbuf *sb,size_t *sz){//原始内存取出是什么意思
    char*ptr=sb->buf;//为啥嘞
    *sz=sb->alloc;//为啥不是len
    strbuf_init(sb,0);
    return ptr;
}

int strbuf_cmp(const struct strbuf*first,const struct strbuf*second){
    //return strcmp(first->alloc,second->alloc);
    return first->len-second->len;
}

void strbuf_reset(struct strbuf*sb){//清空
    sb->len=0;
    strcpy(sb->buf,"");
}




//2

void strbuf_grow(struct strbuf*sb,size_t extra){//长度扩大啥意思,是指内存还是len
    /* if(sb->len+1+extra<sb->alloc){
        return;
    }
    sb->alloc=sb->len+extra;
    sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc));
    */
    if(sb->alloc==0){
        sb->alloc+=extra;
    }else{
        while(sb->alloc<sb->len+extra){
            sb->alloc*=2;
        }
    }
    sb->buf=(char*)realloc(sb->buf,sizeof(char)*sb->alloc);
}

void strbuf_add(struct strbuf*sb,const void *data,size_t len){
    strbuf_grow(sb,len);
    memcpy(sb->buf+sb->len,data,len);
    sb->len+=len;
    sb->buf[sb->len]='\0';
}

void strbuf_addch(struct strbuf*sb,int c){
   // strbuf_add(sb,&c,1);
    strbuf_grow(sb,2);
   // memset(sb->buf+sb->len,(char)c,sizeof(char));
    sb->buf[sb->len]=c;
    sb->len++; 
    sb->buf[sb->len]='\0';
}

void strbuf_addstr(struct strbuf *sb, const char *s){
   // strbuf_add(sb,s,strlen(s));
    strbuf_grow(sb,strlen(s)+1);
    memcpy(sb->buf+sb->len,s,strlen(s));
    sb->len+=strlen(s);
    sb->buf[sb->len]='\0';

}
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2){
//    sb->len+=sb2->len;
//    strbuf_add(sb,sb2->buf,sb2->len);
    strbuf_grow(sb,sb2->len+1);
    memcpy(sb->buf+sb->len,sb2->buf,sb2->len);
    sb->len+=sb2->len;
    sb->buf[sb->len]='\0';
}
void strbuf_setlen(struct strbuf *sb, size_t len){
    sb->len=len;
    sb->buf[len]='\0';
    
}
size_t strbuf_avail(const struct strbuf *sb){
    return sb->alloc-sb->len-1;
}
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len){//strcpy的进一步理解及strncpy
    /*int i;
    //    \0的问题
    if(pos>sb->alloc){
        printf("this position is wrong!");
    }else{
        sb->len+=len;
        while(strbuf_avail(sb)>len){//有=号
            sb->alloc*=2;
            sb->buf=(char*)realloc(sb->buf,sizeof(char)*(sb->alloc));
        }
        strcpy((char*)data+len+1,"");
        for(i=pos;i<=(sb->len)+1;i++){
            sb->buf[i+len]=sb->buf[i];
        }

    }*/
   // int i;
    strbuf_grow(sb,len+1);
//1
//    for(i=pos;i<=sb->len;i++){
//        sb->buf[i+len]=sb->buf[i];
//    }

//2

//    memcpy(sb->buf+pos+len,sb->buf+pos,sb->len-pos);
//    memcpy(sb->buf+pos,(char*)data,len);
//3

    memmove(sb->buf+pos+len,sb->buf+pos,sb->len-pos);
    memmove(sb->buf+pos,(char*)data,len);
    sb->len+=len;
    sb->buf[sb->len]='\0';
}


//3


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
//*还有个\t吗
void strbuf_rtrim(struct strbuf*sb){
    int i=sb->len-1;
    while(sb->buf[i]==' '||sb->buf[i]=='\t'){
        sb->len--;
        sb->buf[i]='\0';
        i--;
    }
}

void strbuf_ltrim(struct strbuf*sb){
    
    int i=0;
    while(sb->buf[i]==' '||sb->buf[i]=='\t'){
        sb->len--;
        i++;
    }
    char*ptr=(char*)malloc(sizeof(char)*(sb->len+1));
//    strcpy(ptr,sb->buf+i);
    memmove(ptr,sb->buf+i,sb->len);
    memmove(sb->buf,ptr,sb->len);
//    memmove(sb->buf,sb->buf+i,sb->len);

}


void strbuf_remove(struct strbuf *sb, size_t pos, size_t len){
/*    if(pos<=sb->len&&len<=sb->len-pos){
        strcpy(sb->buf+pos,sb->buf+pos+len);
    }else{
        printf("the pos or len is wrong!");
    }
}
*/  
    memmove(sb->buf+pos,sb->buf+pos+len,sb->len-pos-len);
    sb->len-=len;

}
//4




ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint){
    /* sb->buf=(char*)realloc(sb->buf,sizeof(char)*(hint?hint:8192));
    FILE*file=fdopen(fd,"r");
    sb->buf=(char*)realloc(sb->buf,sb->alloc+(hint?hint:8192));
    sb->alloc+=hint?hint:8192;
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
    */
    return 0;









}




int strbuf_getline(struct strbuf *sb, FILE *fp){
    /*size_t len=0;
    int sign=0;
    char*line=(char*)malloc(1000);
    if(sign==getline(&line,&len,fp)){
        len=strlen(line);
        sb->len+=len;
        if(sb->len>=sb->alloc){
            sb->alloc*2;
          //  realloc(sb->buf,sb->alloc);
        }
        strcat(sb->buf,line);
    }
    free(line);
    return len;*/
    return 0;
}



//5

struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max){
  /*  //str[i]='\0'
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


    return sb;*/
    return NULL;
}

bool strbuf_begin_judge(char* target_str, const char* str, int strlen){
    int i=0;
    while(i<=strlen){
        if(target_str[i]!=str[i]){
            return false;
            i++;
        }
    }
    return true;
}

/*int strbuf_pandaun(struct strbuf*sb,char*s){
    int i=0;
    while(i<=sb->len){
        if(sb->buf[i]!=s[i]){
            return 0;
            i++;
        }
    }
    return 1;
}*/

char* strbuf_get_mid_buf(char* target_buf, int begin, int end, int len){
    /*char*ptr=(char*)malloc(sizeof(char)*(end-begin));
    strbuf(ptr,target_buf+begin);

    return ptr;*/
    return NULL;
}

/*
char* strbuf_copy(struct strbuf*sb,int begin,int end,int len){
    char*ptr=(char*)malloc(sizeof(char)*(end-begin));
    strcpy(ptr,sb->buf+begin);

    return ptr;
}*/
