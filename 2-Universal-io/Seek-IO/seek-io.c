#include <stdio.h>
#include <string.h>
#include <fcntl.h>          // open close
#include <stdlib.h>         // malloc
#include <unistd.h>         // read write
#include <ctype.h>          // isprint
#include <sys/stat.h>
#include <sys/types.h>

#include "get_num.h"

int main(int argc, char *argv[])
{
    int fd;
    size_t len;
    char *buf;
    ssize_t num_read, num_write;
    off_t offset;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        printf("%s <file> {r<length> | R<length> | w<string> | s<offset>}...\n", argv[0]);

    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd == -1)
        perror("open");

    for (int i = 2; i < argc; i++) {
        switch (argv[i][0]) {
            case 'r':
            case 'R':
                len = getLong(&argv[i][1], GN_ANY_BASE, argv[i]);
                
                buf = malloc(len);
                if (buf == NULL)
                    perror("malloc");

                num_read = read(fd, buf, len);
                if (num_read == -1)
                    perror("read");
                if (num_read == 0) {
                    printf("%s: end-of-file\n", argv[i]);
                } else {
                    printf("%s: ", argv[i]);
                    for (int j = 0; j < num_read; j++) {
                        if (argv[i][0] == 'r')
                            printf("%c", isprint((unsigned char)buf[j]) ? buf[j] : '?');
                        else
                            printf("%02x ", (unsigned int)buf[j]);
                    }
                    printf("\n");
                }
                free(buf);
                break;
            
            case 'w':
                num_write = write(fd, &argv[i][1], strlen(&argv[i][1]));
                if (num_read == -1)
                    perror("write");
                printf("%s: wrote %ld bytes\n", argv[i], (long)num_write);
                break;
            
            case 's':
                offset = getLong(&argv[i][1], GN_ANY_BASE, argv[i]);
                if (lseek(fd, offset, SEEK_SET) == -1)
                    perror("lseek");
                printf("%s: seek succeeded\n", argv[i]);
                break;

            default:
                printf("argument must start with [rRws]: %s\n", argv[i]);
        }
    }

    exit(EXIT_SUCCESS);
}