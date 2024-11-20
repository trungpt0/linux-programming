#define _LARGEFILE64_SOURCE 
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int fd;
    off64_t offset;

    /* check arguments */
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        printf("%s <filename> <offset>\n", argv[0]);

    /* open large file */
    fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open64");
    }

    /* set large offset */
    offset = atoll(argv[2]);
    if (lseek64(fd, offset, SEEK_SET) == -1) {
        perror("lseek64");
    }

    // write into file
    if (write(fd, "test", 4) == -1) {
        perror("write");
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
