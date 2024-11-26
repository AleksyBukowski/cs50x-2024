#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int collatz(int);
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

    int number = atoi(argv[1]);
    printf("It took %i steps to go back from %i to 1\n", collatz(number), number);

}

int collatz(int n) {
    if (n == 1) {
        return 0;
    }
    else if (n % 2 == 0) {
        return 1 + collatz(n/2);
    }
    else {
        return 1 + collatz(3*n + 1);
    }
}

void usage(void) {
    printf("Usage: ./collatz <number>\n");
}
