/*
whoami

chmod 修改文件权限位 change mode
    文字设定法
        u+x  g-w  o-r     a+w(all)
    数字设定法
        uesr   group   other   8421码    
        rw-    r--     r-x
        110    100     101
        6      4        5
    chmod 777 file 

chown   change owner
    sudo (超级权限)临时换成root   
    sudo chown root:root file
    -R
chgrp  change group

*查找与检索
find   文件名
    ./当前目录 *全部文件 -name *通配符
grep 内容  -R   ./*     -I不区分大小写
ctrl +c  退出

*安装和卸载软件
*apt-get  服务器客户端模型
            官方（非官方）服务器      client客户端
sudo /etc/apt/sources.list
sudo apt-get  updata   更新软件源
sudo apt-cache search package    cache(缓存)
                show
                remove
                install


*deb包
sudo dpkg -i xxx.deb
            -r
*源码安装
./configure
make


*磁盘管理
mount  挂载  镜像

sudo fdisk -l
挂载     sudo mount  /dev/sdb1   /mnt(任意目录) (原文件看不到)  
        cd /mnt
        sudo umount /mnt

默认 /media
dd if=sfile of=ssfile.c(复制)


*压缩包   (.gz)(bzip2)
tar   c  creat
        x解压缩
    tar cvf dir (归档文件)  -z  （压缩）  -j
    tar xvf (解包)  -z   -j
    -C指定路径
rar 
zip


*进程管理
who
终端号
ctrl alt f1 f2 f3 f4 f5 f6 f7 图形界面有无

ps   aux
进程   进程号   CPU使用  内存使用      tty使用的终端     stat（状态）       命令名
                                                      r运行 s睡眠                              


ctrl z暂停   到后台暂停
jobs(查看暂停的进程)

fg 1把作业到前台
bg 2在后台运行
前台            后台 
一个进程组       ./app &
shell在后台，ls没用

*kill(向指定进程发送信号)
        kill -l 前32个
        ctrl c sigint sigkill

char *str="hello"只读数据区
    *str='H'
    段错误
    page 4k read only
    kernel   kill -11 当前进程 sigsegv内存非法操作  不存在内存写
    
    sigstop暂停19 18继续

kill 7490(进程号)   kill -9 7671 /sigkill

*env  环境变量  
    ELF .exe


ls    app  是否需要路径
echo $PATH    系统默认路径



export PATH:$PATH:
getit 打开
cd ~   ls -a .bashrc  bash的配置文件

.   source修改的环境变量传给父进程     /bin/bash    父进程 子进程



*/