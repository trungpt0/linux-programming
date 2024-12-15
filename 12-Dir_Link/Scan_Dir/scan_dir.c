#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <errno.h>

void error_exit(char *name)
{
    perror(name);
    exit(EXIT_FAILURE);
}

static void list_file(const char *path)
{
    DIR *dirp;
    struct dirent *dp;
    bool is_current;

    is_current = strcmp(path, ".") == 0;

    dirp = opendir(path);
    if (dirp == NULL) {
        printf("opendir failed on '%s'", path);
        return;
    }

    for (;;) {
        errno = 0;
        dp = readdir(dirp);
        if (dp == NULL)
            break;
        
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        if (!is_current)
            printf("%s/", path);
        printf("%s\n", dp->d_name);
    }

    if (errno != 0)
        error_exit("readdir");
    if (closedir(dirp) == -1)
        error_exit("closedir");
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("%s [dir...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 1)
        list_file(".");
    else
        for (argv++; *argv; argv++)
            list_file(*argv);

    exit(EXIT_SUCCESS);
}