#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

static void fpathconf_print(const char *msg, int fd, int name)
{
    long lim;

    errno = 0;

    lim = fpathconf(fd, name);
    if (lim != -1) {
        printf("%s %ld\n", msg, lim);
    } else {
        if (errno = 0) {
            printf("%s (indeterminate)\n", msg);
        } else {
            fprintf(stderr, "fpathconf %s", msg);
            err_exit(msg);
        }    
    }
}

int main()
{
    fpathconf_print("_PC_NAME_MAX: ", STDIN_FILENO, _PC_NAME_MAX);
    fpathconf_print("_PC_PATH_MAX: ", STDIN_FILENO, _PC_PATH_MAX);
    fpathconf_print("_PC_PIPE_BUF: ", STDIN_FILENO, _PC_PIPE_BUF);
}