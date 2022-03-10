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












*/