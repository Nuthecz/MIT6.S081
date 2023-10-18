#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAXNUM 100

int main(int argc, char* argv[]){
    char argument[MAXARG][MAXNUM];
    //when faced with the '/n',start other while(1) to solve
    while(1){
        memset(argument, 0, MAXARG * MAXNUM);
        int count = argc - 1;
        for (int i = 1; i < argc; i++)
        {
            strcpy(argument[i-1], argv[i]);
        }

        int xargc = 0;
        char buf;
        int read_sult;
        int flag = 0;

        //get the string which is split with ' '
        while ((read_sult = read(0, &buf, 1)) > 0 && buf != '\n')
        {
            if(buf == ' ' && flag){
                count++;
                xargc = 0;
                flag = 0;
            }
            else if(buf != ' '){
                argument[count][xargc++] = buf;
                flag = 1;
            }
        }

        if(read_sult <= 0){
            break;
        }
        char *command = argv[1];
        char *xargs[MAXARG];
        for (int i = 0; i < MAXARG - 1; i++)
        {
            xargs[i] = argument[i];
        }
        xargs[MAXARG - 1] = 0;
        
        if (fork() > 0)
        {
            wait(0);
        }
        else{
            exec(command, xargs);
            exit(0);
        }
    }
    exit(0);
}