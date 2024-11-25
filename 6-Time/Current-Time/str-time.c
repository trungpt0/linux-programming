#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define SBUF_SIZE 1000

int main(int argc, char *argv[])
{
    struct tm tim;
    char sbuf[SBUF_SIZE];
    char *ofmt;

    /* check arguments */
    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s <input-date-time> <in-format> [out-format]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* set locale to the user's environment */
    if (setlocale(LC_ALL, "") == NULL) {
        perror("setlocale");
        exit(EXIT_FAILURE);
    }

    /* parse the input date-time string using the provided input format */
    memset(&tim, 0, sizeof(struct tm));
    if (strptime(argv[1], argv[2], &tim) == NULL) {
        perror("strptime");
        exit(EXIT_FAILURE);
    }

    /* convert the parsed date-time to calendar time */
    tim.tm_isdst = -1;
    printf("calendar time (seconds since Epoch): %ld\n", (long)mktime(&tim));
    
    /* format the date-time into the output buffer using the specified format */
    ofmt = (argc > 3) ? argv[3] : "%H:%M:%S %A, %d %B %Y %Z";
    if (strftime(sbuf, SBUF_SIZE, ofmt, &tim) == 0) {
        perror("strftime");
        exit(EXIT_FAILURE);
    }
    printf("strftime() yields: %s\n", sbuf);

    exit(EXIT_SUCCESS);
}