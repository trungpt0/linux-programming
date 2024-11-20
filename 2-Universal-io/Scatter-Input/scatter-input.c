#include <stdio.h>
#include <string.h>
#include <stdlib.h>     // exit()
#include <fcntl.h>      // open() close()
#include <sys/uio.h>    // struct iovec
#include <sys/stat.h>   // struct stat

#define STR_SIZE 100

int main(int argc, char *argv[])
{
    int fd;
    struct iovec iov[3];
    ssize_t num_read;

    /* check arguments */
    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        printf("%s <file>\n", argv[0]);

    /* open file: argv[1] */
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        perror("read");

    /* total byte required from struct, int, str */
    ssize_t total_required = 0;
    struct stat my_stat;
    int x;
    char str[STR_SIZE];

    iov[0].iov_base = &my_stat;
    iov[0].iov_len = sizeof(struct stat);
    total_required += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    total_required += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    total_required += iov[2].iov_len;

    /* bytes read from file */
    num_read = readv(fd, iov, 3);
    if (num_read == -1)
        perror("readv");
    if (num_read < total_required)
        printf("read fewer bytes than requested\n");

    printf("total bytes requested: %ld\nbytes read: %ld\n", (long)total_required, (long)num_read);

    exit(EXIT_SUCCESS);
}