#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
int main(int argc,char * argv[]){
    int rc=fork();
    if(rc<0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    else if(rc==0){
        printf("hello, I am child (pid:%d)\n",(int)getpid());
        char *myargs[]={"ls","-l",NULL};
        execvp(myargs[0],myargs);
    }
    else{
        int wc=wait(NULL);
        printf("hello, I am parent of %d (pid:%d), wc=%d\n",rc,(int)getpid(),wc);
    }
    return 0;
}