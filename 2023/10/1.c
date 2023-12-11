#include<stdio.h>
#include<string.h>
//不让人hello出来吗

int main(void) {
    char *ptr0 = "Welcome to Xiyou Linux!";
    char ptr1[23] = "Welcome to Xiyou Linux";
    if (ptr0 == ptr1)
      printf("%d\n", printf("Hi Xiyou Linux Group 20"));
    else if (strcmp(ptr0, ptr1))
      printf("%d\n", printf("Hello, Linux Group - 2%d", printf("")));
    printf("ptr0 %d ptr1 %d  %d ",ptr0,ptr1,strcmp(ptr0, ptr1));
    int diff = ptr0 - ptr1;
    printf("Pointer Difference: %d\n", diff);
}