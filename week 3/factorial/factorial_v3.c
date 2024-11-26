// no recursion

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
    int f = 1;
    if (n == 0) {
        return f;
    }

    for (int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}
