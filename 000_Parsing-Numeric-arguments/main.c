#include <stdio.h>
#include <stdlib.h>

#include "get_num.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number> <flag>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int flags = atoi(argv[2]);

    long long_num = getLong(argv[1], flags, "Main Argument");
    printf("Parsed long: %ld\n", long_num);

    int int_num = getInt(argv[1], flags, "Main Argument");
    printf("Parsed int: %d\n", int_num);

    return EXIT_SUCCESS;
}