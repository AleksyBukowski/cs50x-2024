#include <cs50.h>
#include <stdio.h>

const int SIZE = 10;
int list[SIZE] = {7, 13, 20, 25, 1, 3, 8, 19, 32, 18};

void selection_sort(int array[], int size);
void print_array(int array[], int size);

int main(void) {
    selection_sort(list, SIZE);
    print_array(list, SIZE);
}

// sorts using selection sort
void selection_sort(int array[], int size) {
    // goes through each array element
    for (int i = 0; i < size - 1; i++) {
        // starts from the element right next to the i, looks through all the remaining elements
        for (int j = i+1; j < size; j++) {
            // if any of the further j eleme
            if (array[j] < array[i]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
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
