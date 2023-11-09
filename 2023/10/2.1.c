#include <stdio.h>
#include <string.h>
#include<stdlib.h>
//不用数组吧

char *welcome1() {
    char *a = "Welcome to join the Xiyou Linux Group 2023";
    return a;
}

char *welcome2() {
     char b[20];
     // 请在下面一行中填入你的姓名
     strcpy(b, "Your Name");
    return b;
}
// char *welcome2() {
//     char *b = malloc(50 * sizeof(char));  // 使用动态内存分配创建一个足够大的数组
//     strcpy(b, "欢迎加入，Your Name");  // 复制字符串到动态分配的数组中
//     return b;
// }




int main(void) {
    char *a = welcome1();
    char *b = welcome2();
    printf("%s:", a);
    printf("%s", b);
    return 0;
}