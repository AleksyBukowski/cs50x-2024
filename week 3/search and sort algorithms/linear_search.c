#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 10;
int list[SIZE] = {7, 13, 20, 25, 1, 3, 8, 19, 32, 18};

void usage(void);
void linear_search(int array[], int num);

int main(int argc, string argv[]) {
    if (argc < 2 || argc > 2) {
        usage();
        return 1;
    }

    int arg_len = strlen(argv[1]);
    for (int m = 0; m < arg_len; m++) {
        if (argv[1][m] < 48 || argv[1][m] > 57) {
            usage();
            return 2;
        }
    }

    int number = atoi(argv[1]);

    linear_search(list, number);
}

void usage(void) {
    printf("Usage: ./linear_search <number>\n");
}

void linear_search(int array[], int num) {
    for (int i = 0; i < SIZE; i++) {
        if (array[i] == num) {
            printf("Number found! array[%i] = %i\n", i, array[i]);
            return;
        }
    }
    printf("Number not found!\n");
    return;
}
