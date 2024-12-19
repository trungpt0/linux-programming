#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include "get_num.h"

static void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int s, sig;

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s sig-num pid\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sig = getInt(argv[2], 0, "sig-num");
    s = kill(getLong(argv[1], 0, "pid"), sig);

    if (sig != 0) {
        if (s == -1) 
            err_exit("kill");
    } else {
        if (s == 0) {
            printf("Process exists and we can send it a signal\n");
        } else {
            if (errno == EPERM)
                printf("Process exists, but we don't have permission to send it a signal\n");
            else if (errno == ESRCH)
                printf("Process does not exist\n");
            else
                err_exit("kill");
        }
    }
    exit(EXIT_SUCCESS);
}