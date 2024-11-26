#include <cs50.h>
#include <stdio.h>

const int SIZE = 10;
int list[SIZE] = {7, 13, 20, 25, 1, 3, 8, 19, 32, 18};


void merge_sort(int array[], int size);
void print_array(int array[], int size);

int main(void) {
    merge_sort(list, SIZE);
    print_array(list, SIZE);
}

void merge_sort(int array[], int size) {
    
    return;
}

// prints the sorted array
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
