#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int input_fd, output_fd, open_flags;
    mode_t perm;
    ssize_t num_read;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        printf("%s <input file> <output file>\n", argv[0]);

    
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
        printf("cannot open %s file\n", argv[1]);

    open_flags = O_CREAT | O_WRONLY | O_TRUNC;
    perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    output_fd = open(argv[2], open_flags, perm);
    if (output_fd == -1)
        printf("cannot open %s file\n", argv[2]);

    while ((num_read = read(input_fd, buf, BUF_SIZE)) > 0)
        if (write(output_fd, buf, num_read) != num_read)
            printf("err to write to file\n");

    if (num_read == -1)
        perror("read");

    close(input_fd);
    close(output_fd);

    return 0;
}