#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[]){
    if (argc != 2){
        printf("Function only takes in one argument; more specified.\n");
        printf("Usage: ./double <number>\n");
        return 0;
    }

    int len = strlen(argv[1]);
    string num = argv[1];

    for (int j = 0; j < len; j ++){
        if (num[j] < 48 || num[j] > 57){
            printf("Use only numbers!\n");
            printf("Usage: ./double <number>\n");
            return 0;
        }
    }

    int n = atoi(num);
    int sequence[n];

    for (int i = 0; i < n; i++){
        sequence[i] = (i != 0) ? sequence[i-1] * 2 : 1;
        printf("%i ", sequence[i]);
    }
    printf("\n");
}
