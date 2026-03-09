#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>

int main(){
    struct timespec start,end;
    clock_gettime(CLOCK_MONOTONIC,&start);
    for(int i=0;i<1000000;i++){
        getpid();
    }
    clock_gettime(CLOCK_MONOTONIC,&end);
    double total_time=(end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
    printf("Total time for 1 million getpid() calls: %f seconds\n",total_time);
    return 0;
}