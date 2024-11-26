#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>

static void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

static void usage_error(const char *proc_name, const char *msg)
{
    if (msg != NULL)
        fprintf(stderr, "%s", msg);

    fprintf(stderr, "usage: %s [options] source target\n\n", proc_name);
    fprintf(stderr, "available options:\n");
#define fpe(str) fprintf(stderr, " " str)
    fpe("-t fstype [e.g., 'ext2' or 'reiserfs']\n");
    fpe("-o data [file system-dependent options,\n");
    fpe(" e.g., 'bsdgroups' for ext2]\n");
    fpe("-f mountflags can include any of:\n");
#define fpe2(str) fprintf(stderr, " " str)
    fpe2("b - MS_BIND create a bind mount\n");
    fpe2("d - MS_DIRSYNC synchronous directory updates\n");
    fpe2("l - MS_MANDLOCK permit mandatory locking\n");
    fpe2("m - MS_MOVE atomically move subtree\n");
    fpe2("A - MS_NOATIME don't update atime (last access time)\n");
    fpe2("V - MS_NODEV don't permit device access\n");
    fpe2("D - MS_NODIRATIME don't update atime on directories\n");
    fpe2("E - MS_NOEXEC don't allow executables\n");
    fpe2("S - MS_NOSUID disable set-user/group-ID programs\n");
    fpe2("r - MS_RDONLY read-only mount\n");
    fpe2("c - MS_REC recursive mount\n");
    fpe2("R - MS_REMOUNT remount\n");
    fpe2("s - MS_SYNCHRONOUS make writes synchronous\n");
    
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int opt;
    char *data, *fstype;
    unsigned long flags = 0;

    data = NULL;
    fstype = NULL;

    while ((opt = getopt(argc, argv, "o:t:f")) != -1) {
        switch (opt) {
            case 'o':
                data = optarg;
                break;

            case 't':
                fstype = optarg;
                break;

            case 'f':
                for (int i = 0; i < (int)strlen(optarg); i++) {
                    switch (optarg[i]) {
                        case 'b': flags |= MS_BIND; break;
                        case 'd': flags |= MS_DIRSYNC; break;
                        case 'l': flags |= MS_MANDLOCK; break;
                        case 'm': flags |= MS_MOVE; break;
                        case 'A': flags |= MS_NOATIME; break;
                        case 'V': flags |= MS_NODEV; break;
                        case 'D': flags |= MS_NODIRATIME; break;
                        case 'E': flags |= MS_NOEXEC; break;
                        case 'S': flags |= MS_NOSUID; break;
                        case 'r': flags |= MS_RDONLY; break;
                        case 'c': flags |= MS_REC; break;
                        case 'R': flags |= MS_REMOUNT; break;
                        case 's': flags |= MS_SYNCHRONOUS; break;
                        default: usage_error(argv[0], NULL);
                    }
                }
                break;
            
            default:
                usage_error(argv[0], NULL);
        }
    }

    if (argc != optind + 2)
        usage_error(argv[0], "wrong number of arguments\n");

    if (mount(argv[optind], argv[optind + 1], fstype, flags, data) == -1)
        err_exit("mount");

    exit(EXIT_SUCCESS);
}