#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t child1, child2, grandchild;

    child1 = fork();
    if (child1 == 0) {
        // 子进程1
        printf("子进程1: PID=%d，PGID=%d\n", getpid(), getpgrp());

        child2 = fork();
        if (child2 == 0) {
            // 子进程2
            printf("子进程2: PID=%d，PGID=%d\n", getpid(), getpgrp());

            grandchild = fork();
            if (grandchild == 0) {
                // 孙子进程
                printf("孙子进程: PID=%d，PGID=%d\n", getpid(), getpgrp());
                sleep(1);
                exit(0);
            }
            wait(NULL);
            exit(0);
        }
        wait(NULL);
        exit(0);
    }
    wait(NULL);

    return 0;
}