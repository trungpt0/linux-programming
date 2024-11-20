#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main()
{
    char **env_pos;

    for (env_pos = environ; *env_pos != NULL; env_pos++)
        puts(*env_pos);

    exit(EXIT_FAILURE);
}