/*
*进程学习
?虚拟地址 为什么要有 用来干啥
映射到物理内存物理地址
虚拟内存映射表  内核管理   1page=4096字节 按页面管理
*malloc(4096)物理地址分配一页，开数组开（4096的整数倍）
读写页面访问属性      （用户可操作级别较低，）
只读数据段把页面设成只读属性

*Intel工作级别0，1，2，3级CPU工作级别
3，用户态    0级，内核态（驱动函数）
系统调用 用户到内核     通过软中断的手段

应用程序printf--调底层函数write--write还会调底层system-write(内核态0级)
system-write由汇编实现的x86  int 0x80  ARM swi 软中断




进程共用kernel物理内存
进程只能读写用户空间

PCB进程控制块（资源池、文件描述符、运行状态）
PCB间相互可看到




0~4G  0-3G用户空间
代码段TEXT 从磁盘加载

*/