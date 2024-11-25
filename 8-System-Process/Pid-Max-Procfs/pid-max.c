#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 100

static void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int fd;
    ssize_t n;
    char line[MAX_LINE];

    fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
    if (fd == -1)
        err_exit("open");

    n = read(fd, line, MAX_LINE);
    if (n == -1)
        err_exit("read");

    if (argc > 1)
        printf("old value: ");
    printf("%.*s", (int)n, line);

    if (argc > 1) {
        if (write(fd, argv[1], strlen(argv[1])) != (ssize_t)strlen(argv[1]))
            err_exit("write");

        system("echo /proc/sys/kernel/pid_max now contains "
               "`cat /proc/sys/kernel/pid_max`");
    }

    exit(EXIT_SUCCESS);
}