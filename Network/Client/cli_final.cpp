#include"cli_group.cpp"
#include"cli_ui.cpp"


using namespace std;

int main(int argc,char **argv)
{   
    struct sockaddr_in serveraddr;
    int len;
    char buf[MAXLEN];
    pthread_t tid;
    cfd=socket(AF_INET,SOCK_STREAM,0); 
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&serveraddr.sin_addr);
    serveraddr.sin_port=htons(PORT);
     //pthread_create(&tid,NULL,Recv,void *base)
     connect(cfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)); //将cfd的主动socket连接到由serveraddr指定的监听socket；
    cout<<"cfd"<<cfd<<endl;
        //loading1_dis();              
//!记得把注释去掉
        //log1_dis();
        login1_menu();
      
      return 0;
}









//close(cfd);