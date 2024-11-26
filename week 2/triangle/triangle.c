#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(void);
int exists(float a, float b, float c);
void isright(float a, float b, float c);

int main(int argc, string argv[]) {
    if (argc != 4) {
        printf("Please specify 3 numbers.\n");
        usage();
        return (1);
    }

    for (int i = 1; i < argc; i++) {
        for (int j = 0; j < strlen(argv[i]); j++) {
            if ((argv[i][j] < 48 || argv[i][j] > 57) && argv[i][j] != 46) {
                printf("Invalid input; only numbers are expected.\n");
                usage();
                return (2);
            }
        }
    }
    float a = atof(argv[1]);
    float b = atof(argv[2]);
    float c = atof(argv[3]);
    int existence = exists(a, b, c);
    if (existence) {
        isright(a, b, c);
    }
}

void usage(void) {
    printf("Usage: ./triangle <a> <b> <c>\n");
}

int exists(float a, float b, float c) {
    if ((a + b < c) || (a + c < b) || (b + c < a)) {
        printf("This triangle does NOT exist.\n");
        return 0;
    }
    else {
        printf("Triangle exists.\n");
        return 1;
    }
}

void isright(float a, float b, float c) {
    if ((a > b && a > c && (a*a == b*b + c*c)) || (b > a && b > c && (b*b == a*a + c*c)) || (c > b && c > a && (c*c == a*a + b*b))) {
        printf("It is a right triangle.\n");
    }
    else {
        printf("It's NOT a right triangle.\n");
    }
}
