#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/inotify.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

static void display_inotify_event(struct inotify_event *i)
{
    printf(" wd =%2d; ", i->wd);
    if (i->cookie > 0)
        printf("cookie =%4d; ", i->cookie);

    printf("mask = ");
    if (i->mask & IN_ACCESS)        printf("IN_ACCESS ");
    if (i->mask & IN_ATTRIB)        printf("IN_ATTRIB ");
    if (i->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
    if (i->mask & IN_CLOSE_WRITE)   printf("IN_CLOSE_WRITE ");
    if (i->mask & IN_CREATE)        printf("IN_CREATE ");
    if (i->mask & IN_DELETE)        printf("IN_DELETE ");
    if (i->mask & IN_DELETE_SELF)   printf("IN_DELETE_SELF ");
    if (i->mask & IN_IGNORED)       printf("IN_IGNORED ");
    if (i->mask & IN_ISDIR)         printf("IN_ISDIR ");
    if (i->mask & IN_MODIFY)        printf("IN_MODIFY ");
    if (i->mask & IN_MOVE_SELF)     printf("IN_MOVE_SELF ");
    if (i->mask & IN_MOVED_FROM)    printf("IN_MOVED_FROM ");
    if (i->mask & IN_MOVED_TO)      printf("IN_MOVED_TO ");
    if (i->mask & IN_OPEN)          printf("IN_OPEN ");
    if (i->mask & IN_Q_OVERFLOW)    printf("IN_Q_OVERFLOW ");
    if (i->mask & IN_UNMOUNT)       printf("IN_UNMOUNT ");
    printf("\n");

    if (i->len > 0)
        printf(" name = %s\n", i->name);
}

int main(int argc, char *argv[])
{
    int ino_fd;
    int wd;
    ssize_t num_read;
    char buf[BUF_LEN];
    struct inotify_event *event;
    char *p;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("%s pathname... \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ino_fd = inotify_init();
    if (ino_fd == -1)
        err_exit("inotify_init");

    for (int i = 1; i < argc; i++) {
        wd = inotify_add_watch(ino_fd, argv[i], IN_ALL_EVENTS);
        if (wd == -1)
            err_exit("inotify_add_watch");

        printf("Watching %s using wd %d\n", argv[i], wd);
    }

    for (;;) {
        num_read = read(ino_fd, buf, BUF_LEN);
        if (num_read == 0)
            err_exit("read() from inotify fd returned 0!");

        if (num_read == -1)
            err_exit("read");

        printf("Read %ld bytes from inotify fd\n", (long) num_read);

        for (p = buf; p < buf + num_read; ) {
            event = (struct inotify_event *)p;
            display_inotify_event(event);

            p += sizeof(struct inotify_event) + event->len;
        }
    }
    exit(EXIT_SUCCESS);
}