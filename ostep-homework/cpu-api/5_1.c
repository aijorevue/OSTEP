#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc,char *argv[]){
    int x=100;
    printf("x = %d\n",x);
    int rc=fork();
    if(rc<0){
        fprintf(stderr,"fork failed\n");
        exit(1);
    }
    else if(rc==0){
   
        printf("x in child = %d\n",x);
    }
    else{
        int wc=wait(NULL);
   x=3000;
        printf("x in parent = %d\n",x);
    }
}