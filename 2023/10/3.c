#include<stdio.h>
//这是在干啥
int main(void) {
    char* message[] = {"SADLINUX WELCOMEU",
                      "NCOMEUHIDSABYMYLOVEXIYOU LINUX WELCOMETOXUPT",
                      "XIYOUCOME", "SIDWELDHGSWELYFDHSA"};
    char** p_message[] = {message + 3, message + 2, message + 1, message};
        char*** pp_message = p_message;
    printf("%.5s ", **++pp_message);
    printf("%.6s", *--*++pp_message + 3);
    printf("%.3s", *pp_message[-2] + 3);
    printf("%.5s\n", pp_message[-1][-1] + 1);
    return 0;
}