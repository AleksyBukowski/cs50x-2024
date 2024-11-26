#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x = malloc(3 * sizeof(int));
    x[1] = 72; // intentionally buggy, starting from index 1
    x[2] = 73;
    x[3] = 33;
    // free(x);
}

// valgrind ./memory   <-- to run valgrind, checking for memory leaks etc
