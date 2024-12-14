#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/xattr.h>

#define XATTR_SIZE 10000

void usage_error(char *progName) {
    fprintf(stderr, "Usage: %s [-x] file...\n", progName);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -x    Display extended attribute values in hexadecimal format\n");
    fprintf(stderr, "  file  One or more files to display extended attributes\n");
    exit(EXIT_FAILURE);
}

void error_exit(char *name) {
    perror(name);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    char list[XATTR_SIZE], value[XATTR_SIZE];
    ssize_t list_len, value_len;
    int opt;
    bool hex_display;

    while ((opt = getopt(argc, argv, "x")) != -1) {
        switch (opt) {
            case 'x': hex_display = 1; break;
            case '?': usage_error(argv[0]);
        }
    }

    if (optind >= argc + 2)
        usage_error(argv[0]);

    for (int i = optind; i < argc; i++) {
        list_len = listxattr(argv[i], list, XATTR_SIZE);
        if (list_len == -1)
            error_exit("listxattr");

        printf("%s:\n", argv[i]);

        for (int j = 0; j < list_len; j += strlen(&list[j]) + 1) {
            printf("    name = %s; ", &list[j]);

            value_len = getxattr(argv[i], &list[j], value, XATTR_SIZE);
            if (value_len == -1) {
                printf("couldn't get value");
            } else if (!hex_display) {
                printf("value=%.*s", (int)value_len, value);
            } else {
                printf("value=");
                for (int k = 0; k < value_len; k++)
                    printf("%02x ", (unsigned int)value[k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    exit(EXIT_SUCCESS);
}