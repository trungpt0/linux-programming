#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>

#include "get_num.h"

void exit_err(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

static void disp_proc_time(const char *msg)
{
    clock_t clock_time;
    static long clock_ticks = 0;
    struct tms t;

    if (msg != NULL)
        printf("%s\n", msg);

    if (clock_ticks == 0) {
        clock_ticks = sysconf(_SC_CLK_TCK);
        if (clock_ticks == -1)
            exit_err("sysconf");
    } 

    clock_time = clock();
    if (clock_time == -1)
        exit_err("clock");

    printf("clock() returns: %ld clocks-per-sec (%.2f secs)\n",
        (long)clock_time,
        (double) clock_time / CLOCKS_PER_SEC);

    if (times(&t) == -1)
        exit_err("time");
    
    printf("times() yields: user CPU=%.2f; system CPU: %.2f\n",
        (double) t.tms_utime / clock_ticks,
        (double) t.tms_stime / clock_ticks);
}

int main(int argc, char *argv[])
{
    int num_calls;

    printf("CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n",
        (long)CLOCKS_PER_SEC,
        sysconf(_SC_CLK_TCK));

    disp_proc_time("program start:\n");

    num_calls = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-calls") : 100000000;
    for (int i = 0; i < num_calls; i++)
        (void) getppid();

    disp_proc_time("after getppid() loop:\n");

    exit(EXIT_SUCCESS);
}