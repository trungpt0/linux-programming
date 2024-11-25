#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

static void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    struct utsname uts;

    if (uname(&uts) == -1)
        err_exit("uname");

    printf("node name:      %s\n", uts.nodename);
    printf("system name:    %s\n", uts.sysname);
    printf("release:        %s\n", uts.release);
    printf("version:        %s\n", uts.version);
    printf("machine:        %s\n", uts.machine);

#ifdef _GNU_SOURCE
    printf("domain name: %s\n", uts.domainname);
#endif

    exit(EXIT_SUCCESS);
}