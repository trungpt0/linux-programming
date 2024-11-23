#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <shadow.h>
#include <errno.h>
#include <stdbool.h>

void fatal(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    char *username, *password, *encrypted, *p;
    long lg_max;
    bool auth_ok;
    size_t name_len;
    struct passwd *pwd;
    struct spwd *spwd;

    /* login name max */
    lg_max = sysconf(_SC_LOGIN_NAME_MAX);
    if (lg_max == -1)
        lg_max = 256;

    /* allocating username size */
    username = malloc(lg_max);
    if (username == NULL)
        fatal("malloc");

    /* entering username */
    printf("Username: ");
    fflush(stdout);
    if (fgets(username, lg_max, stdin) == NULL)
        exit(EXIT_FAILURE);

    name_len = strlen(username);
    if (username[name_len - 1] == '\n')
        username[name_len - 1] = '\0';

    /* get password name */
    pwd = getpwnam(username);
    if (pwd == NULL)
        fatal("getpwnam");

    /* get shadow password name */
    spwd = getspnam(username);
    if (spwd == NULL && errno == EACCES)
        fatal("Permission denied to read shadow file");
    if (spwd != NULL)
        pwd->pw_passwd = spwd->sp_pwdp;

    /* enter user password */
    password = getpass("Password: ");
    if (password == NULL)
        fatal("getpass failed");

    /* encrypt password and erase cleartext version immediately */
    encrypted = crypt(password, pwd->pw_passwd);
    for (p = password; *p != '\0'; )
        *p++ = '\0';
    if (encrypted == NULL)
        fatal("crypt");

    /* authenticating user pwd and shadow pwd */
    auth_ok = (strcmp(encrypted, pwd->pw_passwd) == 0);
    if (!auth_ok)
        fatal("Authentication failed");

    printf("successfully authenticated: UID=%ld\n", (long)pwd->pw_uid);

    exit(EXIT_SUCCESS);
}
