#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE = 10;
int list[SIZE] = {7, 13, 20, 25, 1, 3, 8, 19, 32, 18};
int sorted_list[SIZE] = {1, 3, 7, 8, 13, 18, 19, 20, 25, 32};

void usage(void);
void binary_search(int array[], int num);

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

    binary_search(sorted_list, number); // binary search must work on a SORTED list!
}

void usage(void) {
    printf("Usage: ./binary_search <number>\n");
}

void binary_search(int array[], int num) {
    int start = 0;
    int end = SIZE-1;
    int middle;
    while (start <= end) {
        middle = (start + end)/2;
        if (array[middle] == num) {
            printf("Number found! array[%i] = %i\n", middle, array[middle]);
            return;
        }
        else if (num < array[middle]) {
            end = middle-1;
        }
        else {
            start = middle+1;
        }
    }
    printf("Number not found!\n");
    return;
}
