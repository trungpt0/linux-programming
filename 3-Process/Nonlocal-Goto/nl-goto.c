#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

static jmp_buf env;

static void f2(void)
{
    longjmp(env, 2);
}

static void f1(int argc)
{
    if (argc == 1)
        longjmp(env, 1);
    f2();
}

int main(int argc, char *argv[])
{
    /* check arguments > 2 -> error */
    if (argc > 2) {
        printf("--help\n");
        exit(EXIT_FAILURE);
    }

    /* check '--help' */
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("%s <something>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /* init nonlocal jump */
    switch (setjmp(env)) {            
        case 0:
            printf("goto f1()\n");
            f1(argc);
            break;

        case 1:
            printf("jump back from f1()\n");
            break;

        case 2:
            printf("jump back from f2()\n");
            break;
    }

    exit(EXIT_SUCCESS);
}