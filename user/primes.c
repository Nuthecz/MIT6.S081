#include "kernel/types.h"
#include "user/user.h"
#define NUM 36
void child(int *p);
//the parent thread is for pl and input the number
//the child thread is for selecting and printing, its child is for recursion
int main(int argc, char* argv[]){
    int pl[2];
    pipe(pl);

    if(fork() > 0){
        close(pl[0]);
        for (int i = 2; i < NUM; i++)
        {
            write(pl[1], &i, sizeof(int));
        }
        close(pl[1]);
        wait(0);
    }
    else{
        child(pl);
    }
    exit(0);
}

void child(int* pl){
    int pr[2];
    int n;

    close(pl[1]);
    int read_result = read(pl[0], &n, sizeof(int));
    if(!read_result)
        exit(0);

    pipe(pr);
    if (fork() > 0)
    {
        close(pr[0]);
        printf("prime %d\n", n);
        int prime = n;
        while (read(pl[0], &n, sizeof(int)))
        {
            if (n % prime)
            {
                write(pr[1], &n, sizeof(int));
            }
        }
        close(pr[1]);
        wait(0);
        exit(0);
    }
    else{
        child(pr);
    }
}