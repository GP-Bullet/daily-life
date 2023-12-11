#include "ser_thread.cpp"
#include"ser_recv.cpp"

int main()
{ // pthread_mutex_init(&mutexx,NULL);
    struct sockaddr_in serveraddr;
    int listenfd;
    int len;
    char buf[MAXLEN];
    pthread_t tid;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(int));
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(PORT);
    bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(listenfd, 20);
    epollfd = epoll_create(10);
    epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    int flag = fcntl(listenfd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(listenfd, F_SETFL, flag);
    ev.data.fd = listenfd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev);
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "chatroom", &db);
    // assert(status.ok());

    while (1)
    {
        epoll_event events[4096];
        memset(events, 0, 4096);
        int n = epoll_wait(epollfd, events, 4096, 0);
        // printf("%d\n", n);
        if (n < 0)
        {
            // 被信号中断
            if (errno == EINTR)
                continue;
            // 出错,退出
            // break;
        }
        else if (n == 0)
        {
            // 超时,继续
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            if (events[i].events & EPOLLIN)
            {
                if (events[i].data.fd == listenfd)
                {
                    struct sockaddr_in cliaddr;
                    socklen_t cliaddrlen = sizeof(cliaddr);
                    int cfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
                    //cout << "first" << cfd << endl;
                    // int on=1; //开启keepalive
                    // setsockopt(cfd,SOL_SOCKET,SO_KEEPALIVE,&on,sizeof(on));
                    // int val=3; //报文时间间隔
                    // setsockopt(cfd, IPPROTO_TCP,TCP_KEEPIDLE, &val, sizeof(val));
                    // int interval=1;//重发报文间隔
                    // setsockopt(cfd,IPPROTO_TCP,TCP_KEEPINTVL,&interval,sizeof(interval));
                    // int cnt=10;//重发次数
                    // setsockopt(cfd,IPPROTO_TCP,TCP_KEEPCNT,&cnt,sizeof(cnt));

                    epoll_event evv;
                    int flag = fcntl(cfd, F_GETFL);
                    flag |= O_NONBLOCK;
                    fcntl(cfd, F_SETFL, flag);
                    evv.data.fd = cfd;
                    evv.events = EPOLLIN | EPOLLET;
                    epoll_ctl(epollfd, EPOLL_CTL_ADD, cfd, &evv);
                }

                else
                {
                    if (last_choice == "recv_file_fri" || last_choice == "recv_file_gro")
                        continue;
                    pthread_t ttid;
                    char *buf;
                    tmpfd = events[i].data.fd;
                    int len = recvMsg(tmpfd, &buf);
                    if (len == 0)
                    {
                        epoll_ctl(epollfd, EPOLL_CTL_DEL, tmpfd, NULL);
                        close(tmpfd);
                        continue;
                    }
                    string s((buf));
                    free(buf);
                    cout << "asd" << s << endl;
                    json j = json::parse(s);

                    jjjson::usr tmp = j.get<jjjson::usr>();

                    tmp.fd = tmpfd;
                    if (tmp.choice == "inform")
                    {
                        // Inform((void*)&tmp);
                        pthread_create(&ttid, NULL, Inform, (void *)&tmp);
                    }

                    else if (tmp.choice == "recv_file_fri")
                    {
                        Recv_file_fri(tmp);
                    }
                    else if (tmp.choice == "recv_file_gro")
                    {
                        Recv_file_gro(tmp);
                    }
                    else
                    {
                        // pthread_create(&tid, NULL, task, (void *)&tmp);
                        thread Task(task, tmp);
                        Task.join();
                    }
                }
            }
        }
    }
    // pthread_mutex_destroy(&mutexx);
    delete db;
    close(listenfd);
}