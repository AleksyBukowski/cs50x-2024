#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fibonacci(int);
void usage(void);

int main(int argc, string argv[]) {
    if (argc < 2 || argc > 2) {
        usage();
        return 1;
    }

    int len = strlen(argv[1]);
    for (int i = 0; i < len; i++) {
        if (argv[1][i] < 48 || argv[1][i] > 57) {
            usage();
            return 2;
        }
    }

    int expression_num = atoi(argv[1]);
    printf("%i\n", fibonacci(expression_num));

}

int fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }

    return fibonacci(n-1) + fibonacci(n-2);
}

void usage(void) {
    printf("Usage: ./fibonacci <number of the expression>\n");
}
