#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>
#include <sys/fsuid.h>

#define SG_SIZE (NGROUPS_MAX + 1)

/* perror and exit */
void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

/* convert name from id of user */
char *get_name_from_idusr(uid_t uid)
{
    struct passwd *pwd;
    
    /* get passwprd user id */
    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

/* convert id from name of user */
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

/* convert name from id of group */
char *get_name_from_idgrp(gid_t gid)
{
    struct group *grp;

    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

/* convert id from name of group */
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

int main()
{
    uid_t ruid, euid, suid, fsuid;
    gid_t rgid, egid, sgid, fsgid;
    gid_t suppGroups[SG_SIZE];
    int numGroups;
    char *p;

    /* get real, effective, saved of uid and gid */
    if (getresuid(&ruid, &euid, &suid) == -1)
        err_exit("getresuid");
    if (getresgid(&rgid, &egid, &sgid) == -1)
        err_exit("getresgid");

    /* get fs of uid and gid */
    fsuid = setfsuid(0);
    fsgid = setfsgid(0);

    /* display all ids of user */
    printf("UID: ");
    p = get_name_from_idusr(ruid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : p, (long)ruid);
    p = get_name_from_idusr(euid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : p, (long)euid);
    p = get_name_from_idusr(suid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long)suid);
    p = get_name_from_idusr(fsuid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long)fsuid);
    printf("\n");

    /* display all ids of group */
    printf("GID: ");
    p = get_name_from_idgrp(rgid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : p, (long)rgid);
    p = get_name_from_idgrp(egid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : p, (long)egid);
    p = get_name_from_idgrp(sgid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long)sgid);
    p = get_name_from_idgrp(fsgid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long)fsgid);
    printf("\n");

    numGroups = getgroups(SG_SIZE, suppGroups);
    if (numGroups == -1)
        err_exit("getgroups");

    printf("supplementary groups (%d): ", numGroups);
    for (int i = 0; i < numGroups; i++) {
        p = get_name_from_idgrp(suppGroups[i]);
        printf("%s (%ld) ", (p == NULL) ? "???" : p, (long)suppGroups[i]);
    }
    printf("\n");

    exit(EXIT_SUCCESS);
}