#include <cs50.h>
#include <stdio.h>

const int SIZE = 10;
int list[SIZE] = {7, 13, 20, 25, 1, 3, 8, 19, 32, 18};

void insertion_sort(int array[], int size);
void print_array(int array[], int size);

int main(void) {
    insertion_sort(list, SIZE);
    print_array(list, SIZE);
}

// sorts using insertion sort
void insertion_sort(int array[], int size) {
    // goes through each array element starting from the 2nd
    for (int i = 1; i < size; i++) {
        // checks if the right adjacent element is lower than the left one
        for (int j = i; j > 0; j--) {
            // if so, swaps
            if (array[j] < array[j-1]) {
                int temp = array[j-1];
                array[j-1] = array[j];
                array[j] = temp;
            }
        }
    } // with each iteration, we start from next element i, leaving the sorted side of the array which is at the left (below current i index)
    return;
}

void print_array(int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (i < size-1) {
            printf("%i ", array[i]);
        }
        else {
            printf("%i\n", array[i]);
        }
    }
}
