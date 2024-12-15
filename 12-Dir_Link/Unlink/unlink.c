#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "get_num.h"

#define CMD_SIZE 200
#define BUF_SIZE 1024

void error_exit(char *name)
{
    perror(name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int fd;
    int num_blocks;
    char shell_cmd[CMD_SIZE];
    char buf[BUF_SIZE];

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("%s temp-file [num-1kB-blocks]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    num_blocks = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1kB-blocks") : 100000;

    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1)
        error_exit("open");

    if (unlink(argv[1]) == -1)
        error_exit("unlink");

    for (int i = 0; i < num_blocks; i++)
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE)
            error_exit("partial/failed write");

    snprintf(shell_cmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
    system(shell_cmd);

    if (close(fd) == -1)
        error_exit("close");

    system(shell_cmd);
    exit(EXIT_SUCCESS);
}