#include<stdio.h>
#include<fcntl.h>  //open
#include<unistd.h>// close
#include<string.h>
#include<sys/stat.h>



#define PARAM_NONE 0
#define PARAM_A 1       //参数a
#define PARAM_L 2       //参数l
#define PARAM_I 4       //参数i
#define PARAM_R 8       //参数r
#define PARAM_T 16      //参数t
#define PARAM_RR 32     //参数R
#define PARAM_S 64      //参数s
#define MAXROWLEN 155   //每行所用最大格数



int g_maxlen;                   //最长文件名长度
int g_leave_len = MAXROWLEN;    
int total = 0;                  //文件大小总和
int h = 0;                      //每行已输出文件名的个数，用来判断是否换行
int han = 4;                    //一行输出文件名的个数

//path
//shuzu
//


int main(int argc,char* argv[]){
    int i,j,k,num;
    char path[PATH_MAX+1];
    char param[32];
    int flag_param=PARAM_NONE;
    struct stat buf;


    j=0;
    num=0;

    
    for(i=1;i<argc;i++){
        if(argv[i][0]=='-'){
            for(k=1;k<strlen(argv[i]);j++,k++){
                param[j]=argv[i][k];
            }
            num++;
        }
    }


    for(i=0;i<j;i++){
        if(param[i]=='a'){
            flag_param |= PARAM_A;
        }else if(param[i]=='l'){
            flag_param |=PARAM_L;
        }else if(param[i]=='R'){
            flag_param|=PARAM_RR;
        }else if(param[i]=='r'){
            flag_param|=PARAM_R;
        }else if(param[i]=='t'){
            flag_param|=PARAM_T;
        }else if(param[i]=='i'){
            flag_param|=PARAM_I;
        }else if(param[i]=='s'){
            flag_param|=PARAM_S;
        }
        else{
            printf("没有--%c这个功能哟！",param[i]);
            exit(1);
        }
    }

    if(num+1==argc){
        strcpy(path,"./");
        path[2]='\0';
        display_dir(flag_param,path);
        return 0;
    }

    i=1;
    do{
        if(argv[i][0]=='-'){
            i++;
            continue;
        }else{
            strcpy(path,argv[i]);
            if(stat(path,&buf)==-1)
                //my_err("stat",)__LTNE__)
            ;
            
            if(S_ISDIR(buf.st_mode)){
                if(path[strlen(argv[i])-1]!='/'){
                    path[strlen(argv[i])]='/';
                    path[strlen(argv[i]+1)]='\0';
                }else
                    path[strlen(argv[i])]='\0';
                display_dir(flag_param,path);
                i++;
            }else{
                display(flag_param,path);
                i++;
            }
        }
    }while(i<argc);
    return 0;


}

/*
void do_ls(char dirname[]){
    DIR*dir_ptr;
    struct dirent *direntp;

    if((dir_ptr=opendir(dirname))==NULL){
        perror("打开目录失败");
        exit(1);
    }else{
        while(direntp=readdir(dir_ptr)!=NULL){
            restored_ls(direntp);
        }
        sort(filename,0,filenums-1);

    }
}*/