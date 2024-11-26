#include <stdio.h>
#include <cs50.h>

int main(void) {
    long num;
    do {
        num = get_long("Number: ");
    }
    while (num < 0);

    int doubled = 0;
    int notdoubled = 0;
    int digits = 0;
    int helpnumber;
    long num2 = num;

    while (num > 0) {
        notdoubled += (num%10);
        num = num/10;
        digits++;
        if (num > 0){
            helpnumber = (num%10)*2;
            doubled += helpnumber%10;
            helpnumber = helpnumber/10;
            doubled += helpnumber;
            num = num/10;
            digits++;
        }
    }

    long divider = 10;
    for (int i=1; i<(digits-2); i++) {
        divider *= 10;
    }

    int firsttwo = num2 / divider;
    int sum = doubled + notdoubled;

    if (sum%10 == 0) {
        if (digits == 15 && (firsttwo == 34 || firsttwo == 37)) {
            printf("AMEX\n");
        }
        else if (digits == 16 && (firsttwo == 51 || firsttwo == 52 || firsttwo == 53 || firsttwo == 54 || firsttwo == 55)) {
            printf("MASTERCARD\n");
        }
        else if ((digits == 16 || digits == 13) && firsttwo/10 == 4) {
            printf("VISA\n");
        }
        else {
            printf("INVALID\n");
        }
    }
    else {
        printf("INVALID\n");
    }
}
