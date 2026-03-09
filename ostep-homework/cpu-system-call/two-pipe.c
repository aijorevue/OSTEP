#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <sys/wait.h>

#define ITERATIONS 100000

int main() {
    int pipe1[2], pipe2[2];
    char ch = 'x';

    // 1. 强制将进程绑定到 CPU 核心 0
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &set) == -1) {
        perror("sched_setaffinity");
        exit(1);
    }

    // 2. 创建两个管道
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        exit(1);
    } else if (rc == 0) {
        // 子进程：读 pipe1，写 pipe2
        for (int i = 0; i < ITERATIONS; i++) {
            read(pipe1[0], &ch, 1);
            write(pipe2[1], &ch, 1);
        }
    } else {
        // 父进程：写 pipe1，读 pipe2
        struct timespec start, end;

        // 开始计时
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < ITERATIONS; i++) {
            write(pipe1[1], &ch, 1);
            read(pipe2[0], &ch, 1);
        }

        // 结束计时
        clock_gettime(CLOCK_MONOTONIC, &end);

        double total_time_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        
        // 注意：一次循环包含 2 次上下文切换
        printf("总耗时: %.2f 毫秒\n", total_time_ns / 1e6);
        printf("平均每次上下文切换耗时: %.2f 纳秒\n", total_time_ns / (ITERATIONS * 2));

        wait(NULL);
    }

    return 0;
}