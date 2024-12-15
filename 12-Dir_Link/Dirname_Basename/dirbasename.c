#define _GNU_SOURCE
#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>

void error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    char *t1, *t2;

    for (int i = 1; i < argc; i++) {
        t1 = strdup(argv[i]);
        if (t1 == NULL)
            error_exit("strdup");
        t2 = strdup(argv[i]);
        if (t2 == NULL)
            error_exit("strdup");
        printf("%s ==> %s + %s\n", argv[i], dirname(t1), basename(t2));

        free(t1);
        free(t2);
    }
    exit(EXIT_SUCCESS);
}