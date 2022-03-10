/*
which 指定命令所在路径
mkdir   make dir (创建目录)  -p多级目录
tree查看
rm 删除文件
rm dir -rf  force(强制)
rmdir remove dir 删除空目录
rm -r（递归）  rm +rmdir把文件删掉再删空目录
touch(更新时间)创建空文件
mv move 重命名
mv t.c a.c 改成a.c
mv a.c ../移动到上一级
mv a.c ../aa.c
mv ../aa.c ./a.c


cp  copy
cp file1 file2
cp file1 dir/
cp file1 ../

cp dir1 dir2 -r
cp dir1 ~/-r
绝对路径

cat 标准输入 标准输出
ctrl+d  结束

more less cat延伸
more 空格一次一屏 回车
往上shift＋pgup pgdn

head -5 file1   显示前5行
tail -5 file1




//! ln创建链接  软硬链接
                符号链接
    文件名（硬链接）文件大小一样删a对b无影响
    
ln -s a.c b.c（软soft）
快捷方式

tree sudo apt-get install





wc word counter计数(统计工作量)
行数 单词数  字符数
-l    -w    -c-chars-bytes         


od 查看格式od -tc file   Ascii码
            -x 16进制  -d十进制  -o八进制

od --help

du -hm   -hb



df 磁盘使用情况  df --block=GB




*/