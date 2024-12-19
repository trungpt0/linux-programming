#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

static void sig_handler()
{
    printf("ouch!\n");
}

int main()
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        err_exit("signal");

    for (int i = 0; ; i++) {
        printf("%d\n", i);
        sleep(3);   
    }
}