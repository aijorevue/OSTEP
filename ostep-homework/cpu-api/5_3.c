#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int p[2];
    if (pipe(p) < 0) exit(1); // 创建管道：p[0]是读端，p[1]是写端

    int rc = fork();

    if (rc < 0) {
        exit(1);
    } else if (rc == 0) {
        // 子进程
        printf("child: hello\n");
        
        // 打印完后，往管道随便写个东西，或者直接关闭写端
        char sync = 'x';
        write(p[1], &sync, 1); 
    } else {
        // 父进程
        char buf;
        // read 会阻塞在这里，直到子进程写了数据或者关闭了管道
        read(p[0], &buf, 1); 
        
        printf("parent: goodbye\n");
    }

    return 0;
}