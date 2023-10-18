#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

void find(char *path, char *target_file);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERROR: You need pass in only 2 arguments\n");
        exit(1);
    }
    char *target_path = argv[1];
    char *target_file = argv[2];
    find(target_path, target_file);
    exit(0);
}

void find(char *path, char *target_file)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path,0)) < 0){
        printf("cannot open\n");
        return;
    }

    if(fstat(fd, &st) < 0){
        printf("cannot stat");
        return;
    }

    while(read(fd,&de,sizeof(de)) == sizeof(de)){
        //add the full path
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        if(de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if(stat(buf,&st) < 0){
            printf("connot stat");
        }

        switch(st.type){
            case T_FILE:
                if(!strcmp(de.name,target_file)){
                    printf("%s\n", buf);
                }
                break;
            case T_DIR:
                if (strcmp(de.name, ".") && strcmp(de.name, "..")) {
                    find(buf, target_file);
                }
        }
    }
    close(fd);
    return;
}