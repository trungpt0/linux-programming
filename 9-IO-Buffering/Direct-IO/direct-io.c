#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>

#include "get_num.h"

static void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int fd;
    size_t length, alignment;
    off_t offset;
    void *buf;
    ssize_t num_read;

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s <file-length> <offset> <alignment>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    length = getLong(argv[2], GN_ANY_BASE, "length");
    offset = (argc > 3) ? getLong(argv[3], GN_ANY_BASE, "offset") : 0;
    alignment = (argc > 4) ? getLong(argv[4], GN_ANY_BASE, "alignment") : 4096;
    
    fd = open(argv[1], O_RDONLY | O_DIRECT);
    if (fd == -1)
        err_exit("open");

    buf = (char *)memalign(alignment * 2, length + alignment) + alignment;
    if (buf == NULL)
        err_exit("memalign");

    if (lseek(fd, offset, length) == -1)
        err_exit("lseek");

    num_read = read(fd, buf, length);
    if (num_read == -1)
        err_exit("read");
    printf("read %ld bytes\n", (long)num_read);

    exit(EXIT_SUCCESS);
}