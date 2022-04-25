#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>

#define PARAM_NONE 0	//无参数
#define PARAM_A 1		//有参数a
#define PARAM_L 2		//有参数l
#define PARAM_r 4		//有参数r
#define PARAM_R 8		//有参数R
#define PARAM_I 16      //有参数i
#define PARAM_S 32      //有参数s
#define PARAM_T 64      //有参数t
#define MAX 128

int cmp(const void*,const void*);
int cmpt(const void*a,const void*b);
int get_param(int argc, char *argv[]);
void ls_do(const char*,int);
void display_l(struct stat*,const char*);// -l

int main(int argc,char**argv)
{
    int i=1,mode=get_param(argc,argv);
    char*path=(char*)malloc(sizeof(char)*MAX);
    strcpy(path,"");
    if(argc==1){//"ls"
        ls_do(".",mode);
    }else{
        int sign=1;
        for(i=1;i<argc;i++){
            if(argv[i][0]=='-')continue;
            else{
                sign=0;
                ls_do(argv[i],mode);
            }
        }
        if(sign)ls_do(".",mode);
    }
    free(path);
    return 0;
}
int cmp(const void*a,const void*b){
    char**a1=(char**)a;
    char**b1=(char**)b;
    return strcmp(*a1,*b1);
}
int cmpt(const void*a,const void*b){
    char**a1=(char**)a;
    char**b1=(char**)b;
    struct stat sta;
    
    time_t t1,t2;
    stat(*a1,&sta);
    t1=sta.st_mtime;
    stat(*b1,&sta);
    t2=sta.st_mtime;
    return t2-t1;

}
int get_param(int argc,char**argv){
    int param=PARAM_NONE,ar=0;
    while(++ar<argc&&argv[ar][0]!='-');
    for(int i=1;ar<argc&&i<strlen(argv[ar]);i++){
        switch(argv[ar][i])
        {
            case 'a':param|=PARAM_A;break;
            case 'l':param|=PARAM_L;break;
            case 'r':param|=PARAM_r;break;
            case 'R':param|=PARAM_R;break;
            case 'i':param|=PARAM_I;break;
            case 's':param|=PARAM_S;break;
            case 't':param|=PARAM_T;break;
        }
        if(i==strlen(argv[ar])-1){
            for(int j=ar+1;j<argc;j++){
                if(argv[j][0]=='-'){
                    ar=j;
                    i=0;
                    printf(" a \n");
                    break;
                }
            }
        }
    }
    return param;
}
void display_err(const char *err_string,int line)
{
    fprintf(stderr, "line: %d ", line);
    perror(err_string);
    exit(1);
}
void display_l(struct stat*sta,const char*name){
    DIR*dir;
    mode_t mode_file=sta->st_mode;
    if(S_ISLNK(mode_file))printf("l");
    else if(S_ISREG(mode_file))printf("-");
    else if(S_ISDIR(mode_file))printf("d");
    else if(S_ISCHR(mode_file))printf("c");
    else if(S_ISBLK(mode_file))printf("b");
    else if(S_ISFIFO(mode_file))printf("f");
    else if(S_ISSOCK(mode_file))printf("s");

    if(S_IRUSR & mode_file){
        printf("r");
    }else printf("-");
    if(S_IWUSR & mode_file){
        printf("w");
    }else printf("-");
    if(S_ISUID & mode_file){
        if(S_IXOTH & mode_file)
            printf("s");
        else printf("S");
    }else if(S_IXUSR & mode_file){
        printf("x");
    }else printf("-");

    if(S_IRGRP & mode_file){
        printf("r");
    }else printf("-");
    if(S_IWGRP & mode_file){
        printf("w");
    }else printf("-");
    if(S_ISGID & mode_file){
        if(S_IXOTH & mode_file)
            printf("s");
        else printf("S");
    }else if(S_IXGRP & mode_file){
        printf("x");
    }else printf("-");

    if(S_IROTH & mode_file){
        printf("r");
    }else printf("-");
    if(S_IWOTH & mode_file){
        printf("w");
    }else printf("-");
    if(S_ISVTX & mode_file){
        printf("T");
    }else if(S_IXOTH & mode_file){
        printf("x");
    }else printf("-");

    printf("%2ld ",sta->st_nlink);
    printf("%4s ",getpwuid(sta->st_uid)->pw_name);
    printf("%4s",getgrgid(sta->st_gid)->gr_name);
    printf("%6ld",sta->st_size);

    char time[32];

    strcpy(time,ctime(&sta->st_mtime));//is mtime not atime
    time[strlen(time)-1]='\0';
    printf(" %.12s",time+4);
    if(S_ISLNK(mode_file))printf("\033[36m %s\033[0m\n",name);
    else if(S_ISDIR(mode_file))printf("\033[34m %s\033[0m\n",name);
    else printf(" %s\n",name);

}
void ls_do(const char*path,int mode){
    DIR*dir_fd;
    struct dirent*dir;
    struct stat sta;
    int total,ls_count=0;
    char**ls_r=(char**)malloc(sizeof(char*)*MAX*MAX*MAX);
    char**file_name=(char**)malloc(sizeof(char*)*MAX*MAX*MAX);
    int count=0;

    if((dir_fd=opendir(path))==NULL){
        fprintf(stderr, "line: %d ",__LINE__);
        perror("opendir");
        free(ls_r);
        free(file_name);
        return;
        //display_err("opendir",__LINE__);
    }
    printf("\033[33m%s:\033[0m\n",path);
    while((dir=readdir(dir_fd))!=NULL){
        if((dir->d_name)[0]=='.'&&(mode&PARAM_A)==0)continue;
        file_name[count]=malloc(sizeof(char)*MAX*MAX);
        strcpy(file_name[count],dir->d_name);
        count++;
    }

    if(mode & PARAM_T)qsort(file_name,count,sizeof(file_name[0]),cmpt);
    if(!(mode & PARAM_T)) qsort(file_name,count,sizeof(file_name[0]),cmp);
    int i;

    for((mode & PARAM_r)?(i=count-1):(i=0);(mode & PARAM_r)?(i>=0):(i<count);(mode & PARAM_r)?(i--):(i++)){
        char*path_full=(char*)malloc(sizeof(char)*MAX*MAX);
        if(!strcmp(path,"/"))sprintf(path_full,"/%s",file_name[i]);
        else sprintf(path_full,"%s/%s",path,file_name[i]);
        if(lstat(path_full,&sta)==-1){
            fprintf(stderr, "line: %d ",__LINE__);
            perror("opendir");
            free(path_full);
            free(file_name[i]);
            continue;
        }

        if(mode & PARAM_I)printf("%ld ",sta.st_ino);

        if(mode & PARAM_S)printf("%2ld ",sta.st_size?((sta.st_size/1024-1)/4+1)*4:0);
        if(mode & PARAM_L)display_l(&sta,file_name[i]);

        mode_t mode_file=sta.st_mode;
        if(!(mode & PARAM_L)){
            if(S_ISLNK(mode_file))printf("\033[36m%s  \033[0m",file_name[i]);
            else if(S_ISDIR(mode_file))printf("\033[34m%s  \033[0m",file_name[i]);
            else printf("%s  ",file_name[i]);
        }

        if((mode & PARAM_R)&&!(S_ISLNK(sta.st_mode))&&S_ISDIR(sta.st_mode)&&(strcmp(file_name[i],".")*strcmp(file_name[i],".."))){
            ls_r[ls_count]=(char*)malloc(sizeof(char)*MAX*MAX);
            strcpy(ls_r[ls_count++],path_full);
        }
        free(file_name[i]);
        free(path_full);
    }printf("\n");
    for(int i=0;i<ls_count;i++){
        printf("\n\033[33m%s:\033[0m\n",ls_r[i]);
        ls_do(ls_r[i],mode);
        free(ls_r[i]);
    }
    ls_count=0;
    if(!(mode & PARAM_L))printf("\b\b");
    free(ls_r);
    free(file_name);
    closedir(dir_fd);
    dir_fd=NULL;
}