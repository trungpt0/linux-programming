#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

static void sig_handler(int sig)
{
    static int count = 0;

    if (sig == SIGINT) {
        count++;
        printf("Caught SIGINT (%d)\n", count);
        return;
    }

    printf("Caught SIGQUIT - that's all folks!\n");
    exit(EXIT_SUCCESS);
}

int main()
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        err_exit("signal");
    if (signal(SIGQUIT, sig_handler) == SIG_ERR)
        err_exit("signal");

    for (;;)
        pause();
}