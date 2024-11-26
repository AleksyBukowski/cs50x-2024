#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cipher(string plaintext, string key);

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int keylen = strlen(argv[1]);
    if (keylen != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string key = argv[1];
    for (int w = 0; w < keylen; w++) {
        key[w] = toupper(argv[1][w]);
    }

    for (int x = 0; x < keylen; x++) {
        if (!isupper(key[x])) {
                printf("Key is invalid; contains invalid characters.\n");
                return 1;
        }
        for (int y = 0; y < keylen; y++) {
            if (x == y) {
                break;
            }
            else if (key[x] == key[y]) {
                printf("Key is invalid; contains duplicate characters.\n");
                return 1;
            }
        }
    }

    string plain = get_string("plaintext: ");
    cipher(plain, key);
}


void cipher(string plaintext, string key) {
    int plainlen = strlen(plaintext);
    string cipher = plaintext;

    for (int j = 0; j < plainlen; j++) {
        if (islower(plaintext[j])) {
            cipher[j] = tolower(key[plaintext[j] - 'a']);
        }
        else if (isupper(plaintext[j])) {
            cipher[j] = key[plaintext[j] - 'A'];
        }
        else {
            cipher[j] = plaintext[j];
        }
    }

    printf("ciphertext: %s\n", cipher);
}
