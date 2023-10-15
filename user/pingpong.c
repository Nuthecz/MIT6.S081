#include "kernel/types.h"
#include "user/user.h"
#define MAXSIZE 1

int main(int argc, char *argv[]){
    int p1[2], p2[2];
    char buf[MAXSIZE];
    pipe(p1);
    pipe(p2);
    int pid = fork();

    if(pid > 0){
        close(p1[0]);
        close(p2[1]);
        write(p1[1], " ", MAXSIZE);
        read(p2[0], buf, MAXSIZE);
        printf("%d: received pong\n", getpid());
        close(p1[1]);
        close(p2[0]);
    }
    else{
        close(p1[1]);
        close(p2[0]);
        read(p1[0], buf, MAXSIZE);
        printf("%d: received ping\n", getpid());
        write(p2[1], " ", MAXSIZE);
        close(p1[0]);
        close(p2[1]);
        exit(0);
    }
    exit(0);
}