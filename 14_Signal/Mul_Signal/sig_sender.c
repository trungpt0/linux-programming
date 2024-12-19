#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#include "get_num.h"

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int num_sigs, sig;

    if (argc < 4 || strcmp(argv[1], "--help") == 0) {
        printf("%s pid num-sigs sig-num [sig-num-2]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid = getLong(argv[1], 0, "PID");
    num_sigs = getInt(argv[2], GN_GT_0, "num-sigs");
    sig = getInt(argv[3], 0, "sig-num");

    printf("%s: sending signal %d to process %ld %d times\n", argv[0], sig, (long) pid, num_sigs);

    for (int i = 0; i < num_sigs; i++)
        if (kill(pid, sig) == -1)
            err_exit("kill");

    if (argc > 4)
        if (kill(pid, getInt(argv[4], 0, "sig-num-2")) == -1)
            err_exit("kill");

    printf("%s: exiting\n", argv[0]);
    exit(EXIT_SUCCESS);
}