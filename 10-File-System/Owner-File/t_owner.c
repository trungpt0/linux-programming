#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

char *get_name_from_idusr(uid_t uid)
{
    struct passwd *pwd;
    
    /* get passwprd user id */
    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

uid_t get_id_from_nameusr(const char *name)
{
    struct passwd *pwd;
    uid_t uid;
    char *ptr;

    if (name == NULL || *name == '\0' )
        return -1;

    uid = strtol(name, &ptr, 10);
    if (*ptr == '\0')
        return uid;

    pwd = getpwnam(name);
    if (pwd == NULL)
        return -1;
    
    return pwd->pw_uid;
}

char *get_name_from_idgrp(gid_t gid)
{
    struct group *grp;

    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t get_id_from_namegrp(const char *name)
{
    struct group *grp;
    gid_t gid;
    char *ptr;

    if (name == NULL || *name == '\0' )
        return -1;

    gid = strtol(name, &ptr, 10);
    if (*ptr == '\0')
        return gid;

    grp = getgrnam(name);
    if (grp == NULL)
        return -1;
    
    return grp->gr_gid;
}

int main(int argc, char *argv[])
{
    uid_t uid;
    gid_t gid;
    bool err_fnd;

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s <owner> <group> <file...>\n"
               "owner or group can be '-', meaning leave unchanged\n",  argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-") == 0) {
        uid = -1;
    } else {
        uid = get_id_from_nameusr(argv[1]);
        if (uid == (uid_t)-1) {
            printf("no such user (%s)", argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp(argv[2], "-") == 0) {
        gid = -1;
    } else {
        gid = get_id_from_namegrp(argv[2]);
        if (gid == (gid_t)-1) {
            printf("no such user (%s)", argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    err_fnd = false;
    for (int i = 3; i < argc; i++) {
        if (chown(argv[i], uid, gid) == -1) {
            printf("chown: %s", argv[1]);
            err_fnd = true;
        }
    }

    exit(err_fnd ? EXIT_FAILURE : EXIT_SUCCESS);
}