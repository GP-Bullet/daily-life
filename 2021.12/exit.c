/*退出函数
void exit(int value);
exit的功能为，退出当前运行的程序，并将参数value返回给主调进程。
在main中return v;的效果 与exit(v);相同。
exit(1)和exit(-1)
是分别返回1和-1到主调程序。
exit(0)则是返回0。
exit(0)表示程序正常退出，非0表示非正常退出
*/