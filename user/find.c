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
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512], *p;

    if ((fd = open(path, 0)) < 0)
    {
        printf("ERROR: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        printf("ERROR: cannot stat %s\n", path);
        close(fd);
        return;
    }

    // read the name of each file/folder under the folder specified by fd, which is $path, name is de.name
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        if (de.inum == 0)
            continue;
        // get the full path name of the current file/directory selected
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if (stat(buf, &st) < 0)
        {
            printf("ERROR: cannot stat %s\n", buf);
        }

        switch (st.type)
        {
        case T_FILE:
            if (!strcmp(target_file, de.name))
            {
                printf("%s\n", buf);
            }
            break;
        case T_DIR:
            if (strcmp(de.name, ".") && strcmp(de.name, ".."))
            {
                find(buf, target_file);
            }
        }
    }
    close(fd);
    return;
}