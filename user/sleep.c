#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        // fprintf has one more file pointer printf
        // https://blog.csdn.net/m0_53005929/article/details/119818286
        // 2 indicates a argument which is the shell output
        fprintf(2, "ERROR: sleep time required\n");
        // the between difference exit(0) and exit(1)
        // https://blog.csdn.net/yjk13703623757/article/details/103507673
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}