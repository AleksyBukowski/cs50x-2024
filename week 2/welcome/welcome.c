#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[]){
    if (argc == 2){
        printf("Welcome, %s.\n", argv[1]);
    }
    else if (argc == 1){
        printf("Please, specify an argument.\n");
    }
    else {
        printf("Too many arguments specified.\n");
    }
}
