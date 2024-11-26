#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define MYFILE "myfile"
#define MYDIR "mydir"
#define FILE_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define DIR_PERMS (S_IRWXU | S_IRWXG | S_IRWXO)
#define UMASK_SETTING (S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH)
#define FP_SPECIAL (S_ISUID | S_ISGID | S_ISVTX)

#define STR_SIZE sizeof("rwxrwxrwx")

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

char *file_perm_str(mode_t perm, int flags) {
    static char str[STR_SIZE];

    snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c",
        (perm & S_IRUSR) ? 'r' : '-', (perm & S_IWUSR) ? 'w' : '-',
        (perm & S_IXUSR) ?
            (((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
            (((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
        (perm & S_IRGRP) ? 'r' : '-', (perm & S_IWGRP) ? 'w' : '-',
        (perm & S_IXGRP) ?
            (((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 's' : 'x') :
            (((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 'S' : '-'),
        (perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-',
        (perm & S_IXGRP) ?
            (((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 't' : 'x') :
            (((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T' : '-')
    );
    
    return str;
}

int main()
{
    int fd;
    mode_t u;
    struct stat sb;

    fd = open(MYFILE, O_RDWR | O_CREAT | O_EXCL, FILE_PERMS);
    if (fd == -1)
        err_exit("open");

    if (mkdir(MYDIR, DIR_PERMS) == -1)
        err_exit("mkdir");

    u = umask(0);

    if (stat(MYFILE, &sb) == -1)
        err_exit("stat-file");

    printf("requested file perms: %s\n", file_perm_str(FILE_PERMS, 0));
    printf("process umask: %s\n", file_perm_str(u, 0));
    printf("actual file perms: %s\n\n", file_perm_str(sb.st_mode, 0));

    if (stat(MYDIR, &sb) == -1)
        err_exit("stat-dir");

    printf("requested dir. perms: %s\n", file_perm_str(DIR_PERMS, 0));
    printf("process umask: %s\n", file_perm_str(u, 0));
    printf("actual dir. perms: %s\n", file_perm_str(sb.st_mode, 0));

    if (unlink(MYFILE) == -1)
        err_exit("unlink");
    if (rmdir(MYDIR) == -1)
        err_exit("rmdir");
    
    exit(EXIT_SUCCESS);
}