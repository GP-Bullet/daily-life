#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int hours;
    int minutes;
    int seconds;
    int time = 0;
    printf("请输入一个时间：\n(最长时间为:99:59:59,单位:时:分:秒)\n");
    scanf("%d:%d:%d", &hours, &minutes, &seconds);
    printf("倒计时开始：\n");

    time += hours * 3600;
    time += minutes * 60;
    time += seconds;
    printf("%02d:%02d:%02d", hours, minutes, seconds);
    fflush(stdout);
    seconds-=1;

    for (int i = 0; i <= time; i++)
    {
        if (seconds >= 0)
        {
            printf("\b\b%02d", seconds);
            seconds--;
        }
        else if (seconds == -1 && minutes > 0)
        {
            minutes--;
            seconds = 59;
            printf("\b\b\b\b\b%02d:%02d", minutes, seconds);
            seconds--;
        }
        else if (seconds == -1 && minutes == 0 && hours > 0)
        {
            hours--;
            minutes = 59;
            seconds = 59;
            printf("\b\b\b\b\b\b\b\b%02d:%02d:%02d", hours, minutes, seconds);
            seconds--;
        }
        fflush(stdout);
        if (i != time)
            usleep(1000000);

    }
    printf("\n倒计时结束.\n");
    return 0;
}