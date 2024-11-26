// my 1st approach, doesn't make any sense

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
}

int factorial(int n) {
    int f = 1;
    if (n < 0) {
        return 0;
    }

    factorial(n - 1);

    for (int i = 1; i <= n; i++) {
        f *= i;
    }

    if (n == num) {
        printf("%i! = %i\n", num, f);
    }
    return 0;
}
