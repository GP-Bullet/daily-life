#include <stdio.h>
int main()
{
    char *a[5] = {"红色", "黄色", "白色", "蓝色", "黑色"};
    int num = 0;
    printf("得到三种不同色的球的可能取法有：\n");
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                if (i != j && i != k && j != k)
                {
                    num++;
                    printf("%s,%s和%s\n", a[i], a[j], a[k]);
                }
    printf("共有%d种取法\n", num);
    return 0;
}