//原本只是—R根目录时会报段错误
//便去借鉴更好的代码
//可是原文件没有备份
//把参数的提取方式改了，-R改了
//可是整体结构变的更乱了
//不知道怎么继续改了
//



#include<stdio.h>
#include<stdlib.h>//qsort
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<pwd.h>//getpwuid
#include<grp.h>//getgrgid
#include<time.h>//ctime
/*
#define PARAM_NONE 0
#define PARAM_A    1              //参数a
#define PARAM_L    2              //参数l
#define PARAM_I    4              //参数i
#define PARAM_R    8              //参数r
#define PARAM_T    16             //参数t
#define PARAM_RR   32             //参数R
#define PARAM_S    64             //参数s
#define MAXROWLEN  155            //每行所用最大格数
*/
int ls_A;
int ls_L;
int ls_I;
int ls_S;
int ls_R;
int ls_T;
int ls_RR;


char filename[256][PATH_MAX+1];
long filetime[256];

//?哪个函数用到时间


void sort(int num);
void judge_file(char*name,char*filename);
void error(const char*string,int line);
void show_inode(char*name,char*filename);
void show_size(char*name,char*filename);
void show_file(char*name,char*filename);
void print(struct stat buf,char* filename);
void show_dir(char*PATH);
void show_R(char*PATH);
void get_param(int argc, char *argv[],int ch,char*string);


void error(const char*string,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(string);
    exit(1);
}




int main(int argc,char*argv[]){

    struct stat buf;

//    char param[256];//存各参数
//    int count,re=0;
//    int num=1;
    //读参数
    int ch;
    get_param(argc,argv,ch,"alistrR");

    if(argc==1||*argv[argc-1]=='-'){//即输入均为参数
                      //'\0'用不用补 
        show_dir((char*)".");
        
    }
    if(argc==2&&ls_RR){ 
        judge_file((char*)".",(char*)".");
    }
    
/*
    for(int k=0;k<count;k++){//遍历param
        if(param[k]=='a')
            flag|=PARAM_A;
            else if(param[k]=='l')
            flag|=PARAM_L;
            else if(param[k]=='i')
            flag|=PARAM_I;
            else if(param[k]=='R')
            flag|=PARAM_RR;
            else if(param[k]=='r')
            flag|=PARAM_R;
            else if(param[k]=='t')
            flag|=PARAM_T;
            else if(param[k]=='s')
            flag|=PARAM_S;
        }


*/
//处理目录和文件   另起一个循环 减少无路径时的判断
    for(int l=optind;l<argc;l++){
    //    if(argv[l][0]=='-'){//减少重复
    //        continue;
    //    }else{//判断目录
            if(S_ISDIR(buf.st_mode)){
                if(ls_RR){
                    judge_file(argv[l],argv[l]);
                }
            //?用不用补上 /
                printf("%s:\n",argv[l]);
                show_dir(argv[l]);

            }else{//文件  是否正确
                if(ls_L){
                    show_file(argv[l],argv[l]);
                }else{
                    print(buf,argv[l]);
                }

     //           strcpy(PATH,argv[l]);
     //           show_file(PATH,PATH);                                    //?多个文件  保存到结构体   是否正确        
     //       }
            
        }
        printf("\n");
        return 0;
    }

}










void get_param(int argc, char *argv[],int ch,char*string){
    /*
    while(--argc){
    ++argv;
    if(*argv[0] == '-'){
            while(*(++(*argv))){
            if(**argv == 'a')   ls_A= 1;
                if(**argv == 'l')   ls_L = 1
                if(**argv == 'R')   ls_RR = 1;
            }
        }
    }
    */
    
    ch=getopt(argc,argv,string);
    while(ch!=-1){
        switch(ch){
            case 'a': ls_A=1;break;                                  
            case 'l': ls_L=1;break;
            case 'i': ls_I=1;break;  
            case 's': ls_S=1;break;
            case 'r': ls_R=1;break;
            case 't': ls_T=1;break;
            case 'R': ls_RR=1;break;
            default:  
                printf("wrong param:%c\n",optopt);
                return ;
        } 
    }
}
void show_mode_rights(struct stat buf){
//文件类型
    if(S_ISLNK(buf.st_mode)){
        printf("l");
    }else if(S_ISREG(buf.st_mode)){
        printf("-");
    }else if(S_ISDIR(buf.st_mode)){
        printf("d");
    }else if(S_ISCHR(buf.st_mode)){
        printf("c");
    }else if(S_ISBLK(buf.st_mode)){
        printf("b");
    }else if(S_ISFIFO(buf.st_mode)){
        printf("f");
    }else if(S_ISSOCK(buf.st_mode)){
        printf("s");
    }

//权限
    //用户权限
    if(buf.st_mode&S_IRUSR){
        printf("r");
    }else{
        printf("-");
    }
    if(buf.st_mode&S_IWUSR){
        printf("w");
    }else{
        printf("-");
    }
    if(buf.st_mode&S_IXUSR){
        printf("x");
    }else{
        printf("-");
    }
    //用户组
    if(buf.st_mode&S_IRGRP){
        printf("r");
    }else{
        printf("-");
    }
    if(buf.st_mode&S_IWGRP){
        printf("w");
    }else{
        printf("-");
    }
    if(buf.st_mode&S_IXGRP){
        printf("x");
    }else{
        printf("-");
    }
    //其他用户
    if(buf.st_mode&S_IROTH){
        printf("r");
    }else{
        printf("-");
    }
    if(buf.st_mode&S_IWOTH){
        printf("w");
    }else{
        printf("-");
    }
    if(buf.st_mode&S_IXOTH){
        printf("x");
    }else{
        printf("-");
    }
}
void print(struct stat buf,char* filename)
{
    if(S_ISDIR(buf.st_mode)){
        printf("\033[01;34m%-10s\033[0m", filename);
    }else if(S_ISLNK(buf.st_mode)){
        printf("\033[01;36m%-10s\033[0m", filename);
	}
	else if(S_ISFIFO(buf.st_mode)){
		printf("\033[40;33m%-10s\033[0m", filename);
	}
	else if(S_ISSOCK(buf.st_mode)){
		printf("\033[01;35m%-10s\033[0m", filename);
	}
	else if(S_ISBLK(buf.st_mode)){
		printf("\033[40;33;01m%-10s\033[0m", filename);
	}
	else if(S_ISCHR(buf.st_mode)){
		printf("\033[40;33;01m%-10s\033[0m", filename);
	}
	else if(S_ISREG(buf.st_mode)){
        if(buf.st_mode&S_IXOTH){
            printf("\033[32m %s  \033[0m",filename);
        }else{
            printf("%s  ",filename);
        }
    }
}
int cmp(const void*a,const void*b){
    return (char*)a-(char*)b;
}

/*
void show_dir(char*PATH){
    DIR*dir;
    struct dirent *item;
    struct stat buf;
    char name[300];
    if((dir=opendir(PATH))==NULL){
        error("opendir",__LINE__);
    }
    
    int cnt=0;
//    int len=0;
    while((item=readdir(dir))!=NULL){
        strcpy(filename[cnt],item->d_name);
//?        len=strlen(filename[cnt]);
//?       len=0;
        cnt++;
    }
    for(int i=0;i<cnt;i++){
        if(lstat(filename[i],&buf)==-1){
            error("lstat",__LINE__);
        }
        filetime[i]=buf.st_mtime;
    }
    sort(cnt);
//判断-a  -t  -s  
    int j=0;
    for(j=0;j<cnt;j++){
        sprintf(name,"%s%s",PATH,filename[j]);
        stat(name,&buf);
        if(filename[j][0]=='.'&&PARAM_A){
            continue;
        }
    }
    
    if(ls_L){
        show_file(name,filename[j]);
    }else if(ls_RR){
        //show_R();
    }else if(ls_I){
        show_inode(name,filename[j]);
    }else if(ls_S){
        show_size(name,filename[j]);
    }

 //   if((ls_L||ls_S)){
 //       printf("总用量 %d\n",total);
    else // ls -a dir,没有参数，只显示一个目录，
        { 
            if(ls_I)
            {
            show_inode(name,filename[j]);
            }
            else 
            {
            //如果是目录的话就用蓝色
            //如果是可执行文件的话就用绿色
            print(buf,filename[j]);
                }
         //   printf("%5s  ",filename[j]);// 显示文件名，
            }
        
        printf("\n");
        closedir(dir);


}*/











void show_dir(char *dir)//显示目录下的所有文件，同时判断是否有-a选项，里面的是目录的路径名，有相对路径，也有绝对路径
{
    int i=0;
    DIR *mydir;
    struct dirent *myitem;
    char fname[256];
    struct stat buf;//获取文件属性打印文件颜色
    if((mydir = opendir(dir)) == NULL)
    {
        perror("fail to opendir!\n");
        return ;                     
    }
    int cnt=0;
//    getfilename(dir,&cnt);//得到目录下文件的名字以及时间
//    gettime(cnt,dir);
    while((myitem=readdir(mydir))!=NULL){
        strcpy(filename[cnt],myitem->d_name);
//?        len=strlen(filename[cnt]);
//?       len=0;
        cnt++;
    }
    for(int i=0;i<cnt;i++){
        if(lstat(filename[i],&buf)==-1){
            error("lstat",__LINE__);
        }
        filetime[i]=buf.st_mtime;
    }
    sort(cnt);
    int j=0;
    for(j=0;j<cnt;j++)
    {
        //fname里面是目录的名字和文件的名字,全都弄到fname里面
           sprintf(fname,"%s/%s",dir,filename[j]);//dir这个目录的路径名字，文件名，这些名字全都答应到fname这个字符串里面来接收
           stat(fname,&buf);
     //      if(filename[j][0] == '.' )//没有-a参数，如果if条件成立的就继续下一次循环，否则往下执行
             
    //     {
    //       continue;//在目录往下继续搜索，遇到隐藏文件就跳过
    //     }


          if(ls_L)//走到这里就说明有-a参数，ls -l -a dir，同时也有-l参数
        {
           //srvprintf(fname,"%s/%s",dir,myitem->d_name);//dir这个目录的路径名字，文件名，这些名字全都答应到fname这个字符串里面来接收
       //    printf("%s",fname);
      
            show_file(fname,filename[j]);//把文件的秘密打印出来,第一个是目录的路径名，第二个是里面的文件名                                      
        }

    //      else if()//出现了-R选项
    //      {
            //display_Rflag(fname,filename[j],buf);//fname里面是路径名，filename[j]里面都是文件
    //      }
          else if(ls_I)//出现了-i选项就执行
          {

           //sprintf(fname,"%s/%s",dir,myitem->d_name);//dir这个目录的路径名字，文件名，这些名字全都答应到fname这个字符串里面来接收
            show_inode(fname,filename[j]);
            i++;
            if(i%5==0)
            {
            printf("\n");
            }
          }
          else if(ls_S)
          {
            show_size(fname,filename[j]);
          }
          else // ls -a dir,没有参数，只显示一个目录，
          { 
            if(ls_I)
            {
            show_inode(fname,filename[j]);
            }
            else 
            {
            //如果是目录的话就用蓝色
            //如果是可执行文件的话就用绿色
            print(buf,filename[j]);
                }
         //   printf("%5s  ",filename[j]);// 显示文件名，
            }
          }
         printf("\n");
         closedir(mydir);

}








/*
//-lshow_mode_rights
void total(int cnt){
    int total=0;//计算总用量
    for(int i=0;i<cnt;i++){
        if(lstat(filename[i],&buf)==-1){
            error("lstat",__LINE__);
        }
        if(ls_A){
            total=total+buf.st_blocks/2;
        }else{
            if(filename[i][2]!='.'){
            total=total+buf.st_blocks/2;
        }
    }
}   
}
*/



//?name ,nname
//-i
void show_inode(char*name,char*filename){
    struct stat buf;
        
    if(stat(name,&buf)!=-1){
        error("lstat",__LINE__);
    }
    printf("%ld  ",buf.st_ino);
    print(buf,filename);

}

//-s
void show_size(char*name,char*filename){
    struct stat buf;
    if(stat(name,&buf)==-1){
        error("lstat",__LINE__);
    }
    printf("%2ld  ",buf.st_blocks/2);
    print(buf,name);
}





//ASCII码排
//效率太低
//qsort?

//-r -t 默认
void sort(int num){
    char temp[256];
    for(int i=0;i<num-1;i++){
        for(int j=0;j<num;j++){
            if(ls_T){
                if(filetime[j]<filetime[j+1]){
                    strcpy(temp,filename[j]);
                    strcpy(filename[j],filename[j+1]);
                    strcpy(filename[j+1],temp);
                }
            }
            if(ls_R){
                if(strcmp(filename[j],filename[j+1])<0){
                    strcpy(temp,filename[j]);
                    strcpy(filename[j],filename[j+1]);
                    strcpy(filename[j+1],temp);
                }
            }else{
                if(strcmp(filename[j],filename[j+1])>0){
                    strcpy(temp,filename[j]);
                    strcpy(filename[j],filename[j+1]);
                    strcpy(filename[j+1],temp);
                }
            }
        }
    }
}


void judge_file(char*name,char*filename){
    char file[PATH_MAX];
    struct stat buf;
    stat(name,&buf);

    if(S_ISDIR(buf.st_mode)){
        printf("%s:\n",name);
    
    DIR*dp;
    struct dirent*dir;
    dp=opendir(name);

    while(dir=readdir(dp)){
        sprintf(file,"%s%s",name,dir->d_name);
        stat(file,&buf);
        if(ls_A){
            if(strcmp(dir->d_name,".") == 0 ||strcmp(dir->d_name,"..") == 0||dir->d_name[0]=='.')
                    {
                            continue;                    
                    }
        }
        print(buf,dir->d_name);
    }
    printf("\n");
    show_R(name);

    closedir(dp);
    }else{
        return;
    }
}

//改了一个-R崩了
void show_R(char*PATH){
    char path[PATH_MAX];
    DIR *dp;
    struct dirent *sdp;
    dp = opendir(PATH);
            if(dp == NULL)
            {
                perror("opendir error");
                    return;
                        
            }
            while(sdp = readdir(dp))
            {
                
                    if(strcmp(sdp->d_name,".") == 0 ||strcmp(sdp->d_name,"..") == 0||sdp->d_name[0]=='.')
                    {
                            continue;
                                
                    }

                        //读这个目录项，继续判断是不是目录，如果是目录iu还得再进入，如果是文件就打印
                        //    //ifFile(sdp->d_name);//不能直接这样，要绝对路径才可以
                            sprintf(path, "%s/%s", PATH, sdp->d_name);
                            judge_file(path,sdp->d_name);
            }
printf("\n");
                closedir(dp);
                return;

}
void show_file(char*name,char*filename){
    struct stat buf;
    if(stat(name,&buf)==-1){
        error("lstat",__LINE__);
    }
    if(ls_S){
        show_size(name,filename);
    }
    if(ls_I){
        show_inode(name,filename);
    }
    show_mode_rights(buf);
    printf(" %2ld ",buf.st_nlink);//硬链接数
          //打印用户名和所属组
    printf("%10s ",getpwuid(buf.st_uid)->pw_name);
    printf("%10s ",getgrgid(buf.st_gid)->gr_name);

    printf(" %8ld  ",buf.st_size);//所占的字节大小
//    char *ctime();
//    printf("%.12s  ",4+ctime(&(&buf) -> st_mtime));
//    print(buf,filename);//打印的同时显示颜色
    printf("\n");
    return ;


}





