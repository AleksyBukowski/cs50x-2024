#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cipher(string plaintext, int key);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int arglen = strlen(argv[1]);
    for (int i = 0; i < arglen; i++) {
        if (argv[1][i] < 48 || argv[1][i] > 57) {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    string plain = get_string("plaintext: ");
    int key = atoi(argv[1]);
    cipher(plain, key);
}

void cipher(string plaintext, int key) {
    int plainlen = strlen(plaintext);
    string cipher = plaintext;

    for (int j = 0; j < plainlen; j++) {
        if (islower(plaintext[j])) {
            cipher[j] = ((((plaintext[j] - 'a') + key) % 26) + 'a');
        }
        else if (isupper(plaintext[j])) {
            cipher[j] = ((((plaintext[j] - 'A') + key) % 26) + 'A');
        }
        else {
            cipher[j] = plaintext[j];
        }
    }

    printf("ciphertext: %s\n", cipher);
}
