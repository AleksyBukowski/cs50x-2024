#include <cs50.h>
#include <stdio.h>

const int SIZE = 10;
int list[SIZE] = {7, 13, 20, 25, 1, 3, 8, 19, 32, 18};


void bubble_sort(int array[], int size);
void print_array(int array[], int size);

int main(void) {
    bubble_sort(list, SIZE);
    print_array(list, SIZE);
}

void bubble_sort(int array[], int size) {
    bool swaps;
    // iterates through each element i times
    for (int i = 0; i < size; i++) {
        // sets the "did we swap during this iteration" boolean to false
        swaps = false;
        // iterates through each pair of elements - j should be less than size minus one
        // (we don't want to step outside of the array with j + 1) and minus i
        // (each i iterations means that the highiest number was "bubbled" and is at the end,
        // no need to check the already sorted end of the list)
        for (int j = 0; j < size - 1 - i; j++) {
            // if the number to the right is lower than the left one
            if (array[j+1] < array[j]) {
                // swap the number to the right with the left one
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                swaps = true;
            }
        }

        if (swaps == false) {
            break;
        }
    }
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
