#include <stdio.h>
#include <cs50.h>

int main(void){
    int money;
    do {
        money = get_int("Change owed: ");
    }
    while (money < 0);

    int coins = 0;

    while(money>=25){
        money = money - 25;
        coins++;
    }
    while(money>=10){
        money = money - 10;
        coins++;
    }
    while(money>=5){
        money = money - 5;
        coins++;
    }
    while(money>=1){
        money = money - 1;
        coins++;
    }

    printf("%i\n", coins);
}
