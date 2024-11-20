#include <stdio.h>
#include <stdlib.h>

// Initialized data segment
int initialized_global = 33;

// Uninitialized data segment (BSS)
int uninitialized_global;

// Initialized static variable (data segment)
static int static_initialized = 66;

// Uninitialized static variable (BSS)
static int static_uninitialized;

void demo_memory_segments()
{
    // Stack segment
    int stack_var = 99;

    // Heap segment
    int *heap_var = (int *)malloc(sizeof(int));
    *heap_var = 369;

    /* Process memory segments */
    printf("Initialized data segment (initialized_global)          :%p\n", (void *)&initialized_global);
    printf("Uninitialized data segment (uninitialized_global)      :%p\n", (void *)&uninitialized_global);
    printf("Initialized static variable (static_initialized)       :%p\n", (void *)&static_initialized);
    printf("Uninitialized static variable (static_uninitialized)   :%p\n", (void *)&static_uninitialized);
    printf("Stack segment (stack_var)                              :%p\n", (void *)&stack_var);
    printf("Heap segment (heap_var)                                :%p\n", (void *)heap_var);

    // Free mem heap segment
    free(heap_var);
}

int main()
{
    demo_memory_segments();
    return 0;
}