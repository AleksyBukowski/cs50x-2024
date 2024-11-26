// calculates the average of N numbers.

#include <stdio.h>
#include <cs50.h>

// number of numbers to consider
const int N = 3;

// the prototype of average function initializing it
float average(int length, int array[]);

// lets you type in the specific numbers and calls the average function
int main(void){
    int numbers[N];
    for(int i = 0; i < N; i++){
        numbers[i] = get_int("Number %i value: ", i+1);
    }
    printf("The avg value of the %i numbers you typed in is: %f\n", N, average(N, numbers));
}

// calculates the average value of the numbers provided
float average(int length, int array[]){
    int sum = 0;
    for (int j = 0; j < N; j++){
        sum+= array[j];
    }
    return sum / (float) length;
}
