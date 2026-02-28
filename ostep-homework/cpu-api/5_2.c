#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>

int main(int argc,char *args[]){
    int fd=open("5_2.output",O_WRONLY|O_CREAT|O_TRUNC,0644);
    int rc=fork();
    if(rc<0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    else if(rc==0){
       const char *child_msg = "CHILD LINE ONE\nCHILD LINE TWO\n";
        write(fd, child_msg, strlen(child_msg));
        printf("Child: write done.\n"); 
    }
    else{
        const char *parent_msg = "PARENT LINE ONE\nPARENT LINE TWO\n";
        write(fd, parent_msg, strlen(parent_msg));
        printf("Parent: write done.\n"); 
   }
    close(fd);
    return 0;
}