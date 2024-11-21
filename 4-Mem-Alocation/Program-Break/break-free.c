#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "get_num.h"

#define MAX_ALLOCS 1000000

int main(int argc, char *argv[])
{
    int num_allocs, block_size; // number of allocations and size of each block
    int free_step, free_min, free_max; // parameters for freeing memory
    char *ptr[MAX_ALLOCS]; // array to store pointers to allocated blocks

    /* check arguments */
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        printf("%s <num-allocs> <block-size> <step> <min> <max>\n", argv[0]);

    /* get and check num allocs*/
    num_allocs = getInt(argv[1], GN_GT_0, "num-allocs");
    if (num_allocs > MAX_ALLOCS) {
        printf("num allocs > %d\n", MAX_ALLOCS);
        exit(EXIT_FAILURE);
    }

    /* get block size */
    block_size = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");

    /* get step max min */
    free_step = (argc > 3) ? getInt(argv[3], GN_GT_0, "step") : 1;
    free_min = (argc > 4) ? getInt(argv[4], GN_GT_0, "min") : 1;
    free_max = (argc > 5) ? getInt(argv[5], GN_GT_0, "max") : num_allocs;

    /* check max size to free */
    if (free_max > num_allocs) {
        printf("free_max > %d\n", num_allocs);
        exit(EXIT_FAILURE);
    }

    printf("init program break %10p\n", sbrk(0));
    printf("allocating %d*%d bytes\n", num_allocs, block_size);

    /* alloc block size */
    for (int i = 0; i < num_allocs; i++) {
        ptr[i] = malloc(block_size);
        if (ptr[i] == NULL) {
            perror("exit");
            for (int j = 0; j < i; j++) free(ptr[j]);
        }
    }

    printf("program bread is now: %10p\n", sbrk(0));

    /* free min size to max size by free step */
    printf("freeing blocks from %d to %d in steps of %d\n", free_min, free_max, free_step);
    for (int i = free_min - 1; i < free_max; i += free_step) {
        free(ptr[i]);
        ptr[i] = NULL;
    }

    printf("after free(), program break is: %10p\n", sbrk(0));

    /* free full block size */
    for (int i = 0; i < num_allocs; i++) {
        if (ptr[i] != NULL) {
            free(ptr[i]);
        }
    }

    printf("final program break: %10p\n", sbrk(0));

    exit(EXIT_SUCCESS);
}