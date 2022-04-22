    #include"myshell.h"

int main() {

	//获取当前工作目录、用户名、主机名
	int result = getCurWorkDir();
	if (ERROR_SYSTEM == result) {
		fprintf(stderr, "\e[31;1mError: System error while getting current work directory.\n\e[0m");
		exit(ERROR_SYSTEM);
	}
	getUsername();
	getHostname();

	
	char argv[BUF_SZ];
	while (TRUE) {
		printf("\e[32;1m%s@%s:%s\e[0m$ ", username, hostname,curPath); // 显示为绿色
		//获取用户输入的命令 
		fgets(argv, BUF_SZ, stdin);
		int len = strlen(argv);
		if (len != BUF_SZ) {
			argv[len-1] = '\0';
		}

		int commandNum = split_command(argv);
		
		if (commandNum != 0) { // 用户有输入指令
			if (strcmp(commands[0], COMMAND_EXIT) == 0) { // exit命令
				result = call_exit();
				if (ERROR_EXIT == result) {
					exit(-1);
				}
			} else if (strcmp(commands[0], COMMAND_CD) == 0) { // cd命令
				result = call_cd(commandNum);
				switch (result) {
					case ERROR_MISS_PARAMETER:
						fprintf(stderr, "\e[31;1mError: Miss parameter while using command \"%s\".\n\e[0m"
							, COMMAND_CD);
						break;
					case ERROR_WRONG_PARAMETER:
						fprintf(stderr, "\e[31;1mError: No such path \"%s\".\n\e[0m", commands[1]);
						break;
					case ERROR_TOO_MANY_PARAMETER:
						fprintf(stderr, "\e[31;1mError: Too many parameters while using command \"%s\".\n\e[0m"
							, COMMAND_CD);
						break;
					case RESULT_NORMAL: // cd命令正常执行，更新当前工作l目录
						result = getCurWorkDir();
						if (ERROR_SYSTEM == result) {
							fprintf(stderr
								, "\e[31;1mError: System error while getting current work directory.\n\e[0m");
							exit(ERROR_SYSTEM);
						} else {
							break;
						}
				}
			} else { // 其它命令
				result = call_command(commandNum);
				switch (result) {
					case ERROR_FORK:
						fprintf(stderr, "\e[31;1mError: Fork error.\n\e[0m");
						exit(ERROR_FORK);
					case ERROR_COMMAND:
						fprintf(stderr, "\e[31;1mError: Command not exist in myshell.\n\e[0m");
						break;
					case ERROR_MANY_IN:
						fprintf(stderr, "\e[31;1mError: Too many redirection symbol \"%s\".\n\e[0m", COMMAND_IN);
						break;
					case ERROR_MANY_OUT:
						fprintf(stderr, "\e[31;1mError: Too many redirection symbol \"%s\".\n\e[0m", COMMAND_OUT);
						break;
					case ERROR_FILE_NOT_EXIST:
						fprintf(stderr, "\e[31;1mError: Input redirection file not exist.\n\e[0m");
						break;
					case ERROR_MISS_PARAMETER:
						fprintf(stderr, "\e[31;1mError: Miss redirect file parameters.\n\e[0m");
						break;
					case ERROR_PIPE:
						fprintf(stderr, "\e[31;1mError: Open pipe error.\n\e[0m");
						break;
					case ERROR_PIPE_MISS_PARAMETER:
						fprintf(stderr, "\e[31;1mError: Miss pipe parameters.\n\e[0m");
						break;
				}
			}
		}
	}
}





int getCurWorkDir() { // 获取当前的工作目录
	char* result = getcwd(curPath, BUF_SZ);
	if (result == NULL)
		return ERROR_SYSTEM;
	else return RESULT_NORMAL;
}



//exit
//terminal信号
int call_exit(){
    pid_t pid=getpid();
    if(kill(pid,SIGTERM)==-1){
        return ERROR_EXIT;
    }else{
        return RESULT_NORMAL;

    }


}


int call_cd(int commandNUM){
    int result=RESULT_NORMAL;

    if(commandNUM<2){
        result=ERROR_MISS_PARAMETER;
    }else if(commandNUM>2){
        result=ERROR_TOO_MANY_PARAMETER;
    }else{
        int ret=chdir(commands[1]);//该函数的用法
        if(ret)
            result=ERROR_WRONG_PARAMETER;
    }

    return result;//这是干啥的

}
void getUsername() { // 获取当前登录的用户名
	struct passwd* pwd = getpwuid(getuid());
	strcpy(username, pwd->pw_name);
}

void getHostname() { // 获取主机名
	gethostname(hostname, BUF_SZ);
}

int isCommand(const char* command){
    if(command==NULL||strlen(command)==0)
    return FALSE;

    int result=TRUE;

    int fds[2];
    if(pipe(fds)==-1){
        result=FALSE;
    }else{
        /*暂存输入输出重定向标志*/
        int inFd=dup(STDIN_FILENO);
        int outFd=dup(STDOUT_FILENO);

        pid_t pid=vfork();
        if(pid==-1){
            result=FALSE;
        }else if(pid==0){
                           //将结果输出重定向到文件描述符
            close(fds[0]);
            dup2(fds[1],STDOUT_FILENO);
            close(fds[1]);

            char tmp[BUF_SZ];
            sprintf(tmp,"command -v %s",command);
            system(tmp);
            exit(1);
        }else{
            waitpid(pid,NULL,0);
            //输入重定向
            close(fds[1]);
            dup2(fds[0],STDIN_FILENO);
            close(fds[0]);
        }

        if(getchar()==EOF){
            result=FALSE;
        }

        dup2(inFd,STDIN_FILENO);
        dup2(outFd,STDOUT_FILENO);
    }
    return result;
}   

int split_command(char command[BUF_SZ]){
    int num=0;
    int i,j;
    int len=strlen(command);


    for(i=0,j=0;i<len;i++){
        if(command[i]!=' '){
            commands[num][j++]=command[i];
        }else{
            if(j!=0){
                commands[num][j]='\0';
                ++num;
                j=0;
            }
        }
    }
    if(j!=0){
        commands[num][j]='\0';
        ++num;
    }
    return num;
}

//从哪到哪的命令

//为了保证格式统一


//result


//?stdin

int call_command(int commandNum){
    pid_t pid=fork();
    if(pid==-1){
        return ERROR_FORK;
    }else if(pid==0){
        int inFds=dup(STDIN_FILENO);
        int outFds=dup(STDOUT_FILENO);

        int result=command_PIPE(0,commandNum);

        //还原标准输入、输出重定向
        dup2(inFds,STDIN_FILENO);
        dup2(outFds,STDOUT_FILENO);
        exit(result);
    }else{
        int status;
        waitpid(pid,&status,0);
        return WEXITSTATUS(status);
    }
}


int command_PIPE(int left,int right){
    if(left>=right){
        return RESULT_NORMAL;
    } 
    int pipe_wh=-1;   //-1

    for(int i=left;i<right;++i){
        if(strcmp(commands[i],COMMAND_PIPE)==0){//调个函数？
            pipe_wh=i;
            break;
        }
    }

    if(pipe_wh==-1){//不含管道
        return command_Redirect(left,right); 
    }else if(pipe_wh+1==right){
        return ERROR_PIPE_MISS_PARAMETER;
    }


    int fds[2];
    if(pipe(fds)==-1){
        return ERROR_PIPE;//什么情况下
    }

    int result=RESULT_NORMAL;
    pid_t pid= vfork();   //fork?
    if(pid==-1){
        result=ERROR_FORK;
    }else if(pid==0){//子进程执行单个命令
        close(fds[0]);//关闭读
        dup2(fds[1],STDOUT_FILENO);//把标准输出重定向到fd[1]  //dup2
        close(fds[1]);//关闭写

        result=command_Redirect(left,pipe_wh);
        exit(result);
    }else{//父进程递归 执行后续命令
        int status;
        waitpid(pid,&status,0);
        int exitCode=WEXITSTATUS(status);    //?wait

        if(exitCode != RESULT_NORMAL){//子进程的指令未正常退出,打印错误信息
            char info[4096]={0};  //一个页表有4096
            char line[BUF_SZ];
            close(fds[1]);
            dup2(fds[0],STDIN_FILENO);//将标准输入重定向到fds[0]
            close(fds[0]);

            while(fgets(line,BUF_SZ,stdin)!=NULL){//读取子进程错误信息
                strcat(info,line);
            }
            printf("%s",info);//打印错误信息

            result=exitCode;
        }else if(pipe_wh+1<right){
            close(fds[1]);
            dup2(fds[0],STDIN_FILENO);
            close(fds[0]);

            result=command_PIPE(pipe_wh+1,right);//递归
            //开始时没有+1
        }
    }

    return result;
}

int command_Redirect(int left,int right){
    //指令不存在
    if(!isCommand(commands[left])){
        return ERROR_COMMAND;
    }
    //判断重定向

    int inNum=0,outNum=0;
    char *inFile=NULL,*outFile=NULL;
    int endFlg=right; //指令在重定向前的终止下标

    for(int i=left;i<right;++i){
        if(strcmp(commands[i],COMMAND_IN)==0){//输入重定向
            ++inNum;
            if(i+1<right){
                inFile=commands[i+1];
            }else{
                return ERROR_MISS_PARAMETER;
            } 
            if(endFlg==right)endFlg=i;
        }else if(strcmp(commands[i],COMMAND_OUT)==0){//输出重定向
            ++outNum;
            if(i+1<right){
                outFile=commands[i+1];
            }else{
                return ERROR_MISS_PARAMETER;
            }
            if(endFlg==right)endFlg=i;
        }
    }

    //处理重定向

//?文件的一些函数用什么比较好

    if(inNum==1){
        FILE*fp=fopen(inFile,"r");
        if(fp==NULL)//输入重定向文件不存在
            return ERROR_FILE_NOT_EXIST;
        fclose(fp);
    }

    if(inNum>1){//输入重定向超过一个
        return ERROR_MANY_IN;  //真的会报错吗
    }else if(outNum>1){
        return ERROR_MANY_OUT;
    }

    int result=RESULT_NORMAL;
    pid_t pid=vfork();
    if(pid==-1){
        result=ERROR_FORK;
    }else if(pid==0){
        //输入输出重定向
        if(inNum==1){
            freopen(inFile,"r",stdin);
        }if(outNum==1){
            freopen(outFile,"w",stdout);
        }

        //执行命令
        char *com[BUF_SZ];
        for(int i=left;i<endFlg;i++){
            com[i]=com[i]=commands[i];
        }
        com[endFlg]=NULL;
        execvp(com[left],com+left);   //?
        exit(errno);  //执行出错,返回errno
    }else{
        int status;
        waitpid(pid,&status,0);
        int err=WEXITSTATUS(status);  //读取子进程返回码

        if(err){//返回码不为0,意味这子进程出错
            printf("\e[31;1mError:%s\n\e[0m",strerror(err));//?颜色
        }
    }

    return result;
}

