// the best approach

#include <cs50.h>
#include <stdio.h>

int num;
int factorial(int n);

int main(void) {
    do {
        num = get_int("Number: ");
    }
    while (num < 0);

    factorial(num);
    printf("%i! = %i\n", num, factorial(num));
}

int factorial(int n) {
    if (n == 0) {
        return 1;
    }

    return n * factorial(n - 1);
}
