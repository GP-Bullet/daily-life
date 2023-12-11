#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>

int not_pick = 0;

typedef struct information
{
    char *name;
    int num;
    int list[77];
} information;

int cmp(const void *a, const void *b)
{
    return (*(information*)b).num - (*(information*)a).num;
}

void statistics(information* candidate)
{
    srand((unsigned int)time(0));
    for (int i = 0; i < 77; i++)
    {
        int t = rand() % 10;
        if (t == 0 || t == 1 || t == 2)
        {
            candidate[0].list[candidate[0].num] = i;
            candidate[0].num++;
        }
        if (t == 3 || t == 4 || t == 5)
        {
            candidate[1].list[candidate[1].num] = i;
            candidate[1].num++;
        }
        if (t == 6 || t == 7 || t == 8)
        {
            candidate[2].list[candidate[2].num] = i;
            candidate[2].num++;
        }
        if(t == 9)
            not_pick++;
    }
}

int main()
{
    information candidate[3];
    candidate[0].name = "Li";
    candidate[1].name = "Wu";
    candidate[2].name = "Fu";
    for (int i = 0; i < 3; i++)
    {
        candidate[i].num = 0;
        memset(candidate[i].list, 0, sizeof(candidate[i].list));
    }
    statistics(candidate);
    printf("投票结束,77名同学中有%d名同学弃票,%d名同学投票\n",not_pick,77-not_pick);
    qsort(candidate, 3, sizeof(candidate[0]), cmp);
    printf("%s获得的票数为:%d\n", candidate[0].name,candidate[0].num);
    printf("%s获得的票数为:%d\n", candidate[1].name,candidate[1].num);
    printf("%s获得的票数为:%d\n", candidate[2].name,candidate[2].num);
    if (candidate[0].num > candidate[1].num)
    {
        printf("%s得票最多,当选为班长，共有以下同学选了他:\n", candidate[0].name);
        for (int i = 0; i < candidate[0].num; i++)
            printf("编号为%d的同学\n", candidate[0].list[i]);
    }
    else if (candidate[0].num == candidate[1].num && candidate[1].num > candidate[2].num)
    {
        printf("%s和%s票数竟然相等,为两人同为班长吗？\n", candidate[0].name, candidate[1].name);
        printf("共有以下同学选了%s:\n", candidate[0].name);
        for (int i = 0; i < candidate[0].num; i++)
            printf("编号为%d的同学\n", candidate[0].list[i]);
        printf("共有以下同学选了%s:\n", candidate[1].name);
        for (int i = 0; i < candidate[1].num; i++)
            printf("编号为%d的同学\n", candidate[1].list[i]);
    }
    else
    {
        printf("三人票数相等\n");
        printf("共有以下同学选了%s:\n", candidate[0].name);
        for (int i = 0; i < candidate[0].num; i++)
            printf("编号为%d的同学\n", candidate[0].list[i]);
        printf("共有以下同学选了%s:\n", candidate[1].name);
        for (int i = 0; i < candidate[1].num; i++)
            printf("编号为%d的同学\n", candidate[1].list[i]);
        printf("共有以下同学选了%s:\n", candidate[2].name);
        for (int i = 0; i < candidate[2].num; i++)
            printf("编号为%d的同学\n", candidate[2].list[i]);
    }

    return 0;
}