#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/time.h>

#define SECONDS_IN_TROPICAL_YEAR (365.24219 * 24 * 60 * 60)

/* perror and exit */
void err_ext(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    time_t tim;
    struct timeval tv;
    struct tm *gmp, *locp;
    struct tm gm, loc;

    /* time() return seconds sice the Epoch */
    tim = time(NULL);
    printf("seconds since the Epoch (1 Jan 1970): %ld (about %6.3f years)\n", 
        (long)tim,
        tim / SECONDS_IN_TROPICAL_YEAR);

    /* seconds and microseconds since Epoch */
    if (gettimeofday(&tv, NULL) == -1)
        err_ext("gettimeofday");
    printf("current time (gettimeofday): %ld seconds and %ld microseconds (%ld.%lds) since Epoch\n",
        (long)tv.tv_sec,
        (long)tv.tv_usec,
        (long)tv.tv_sec,
        (long)tv.tv_usec);

    /* converting and displaying times from Epoch to UTC */
    gmp = gmtime(&tim);
    if (gmp == NULL)
        err_ext("gmtime");

    gm = *gmp;
    printf("broken down by gmtime():\n");
    printf("year:%d   mon:%d   mday:%d   hour:%d   min:%d   sec:%d   wday:%d   yday:%d   isdst=%d\n",
        gm.tm_year, gm.tm_mon, gm.tm_mday,
        gm.tm_hour, gm.tm_min, gm.tm_sec,
        gm.tm_wday, gm.tm_yday, gm.tm_isdst
        );

    /* converting and displaying times from Epoch to local time */
    locp = localtime(&tim);
    if (locp == NULL)
        err_ext("localtime");
    
    loc = *locp;
    printf("broken down by localtime():\n");
    printf("year:%d   mon:%d   mday:%d   hour:%d   min:%d   sec:%d   wday:%d   yday:%d   isdst=%d\n",
        loc.tm_year, loc.tm_mon, loc.tm_mday,
        loc.tm_hour, loc.tm_min, loc.tm_sec,
        loc.tm_wday, loc.tm_yday, loc.tm_isdst
        );
    
    printf("asctime() formats the gmtime() value as: %s", asctime(&gm));
    printf("ctime() formats the time() value as: %s", ctime(&tim));

    printf("mktime() of gmtime() value: %ld secs\n", (long) mktime(&gm));
    printf("mktime() of localtime() value: %ld secs\n", (long) mktime(&loc));
    
    exit(EXIT_SUCCESS);
}