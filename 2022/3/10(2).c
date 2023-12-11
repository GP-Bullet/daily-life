/*
*用户管理
创建    sudo useradd -s /bin/bash -g gaopeng -d  /home/gaopeng -m bullet    
                    指定shell      分组         家目录           用户名
        passwd          su 切换 
        sudo su
root用户
    sudo groupadd 组名
sudo userdel -r gaopeng删除用户

*网络管理
*ifconfig  查看网卡信息
?网卡
    sudo ifconfig eth0 up/down
    sudo ifconfig etho 192.168.1.123临时IP

*ping     测试网络通畅性
nat和windows公用IP  桥接单独

windows  vmware（虚拟机）
?IP

netstat
finger gaopeng
*常用服务器构建
抓包


*其他命令
*man man 
man ls 函数接口长什么样

*clear  清屏  ctrl +l

alias别名
echo 回显变量或者字符串
    echo $?返回值
date
umask   (chmod)   mode & -(umask)
*/