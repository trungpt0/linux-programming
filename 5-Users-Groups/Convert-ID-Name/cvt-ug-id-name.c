#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <grp.h>
#include <unistd.h>
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

int main()
{
    uid_t uid = getuid();
    char *username = get_name_from_idusr(uid);
    uid_t userid = get_id_from_nameusr(username);

    printf("Username: %s\n", username);
    printf("User ID: %d\n", userid);

    gid_t gid = getgid();
    char *grpname = get_name_from_idgrp(gid);
    gid_t grpid = get_id_from_namegrp(grpname);

    printf("Groupname: %s\n", grpname);
    printf("Group ID: %d\n", grpid);

    return 0;
}