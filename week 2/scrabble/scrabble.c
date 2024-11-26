#include <cs50.h>
#include <stdio.h>
#include <string.h>

int calculate(string word);
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
                1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void) {
    string word1 = get_string("Word 1: ");
    string word2 = get_string("Word 2: ");

    int points1 = calculate(word1);
    int points2 = calculate(word2);

    if (points1 > points2) {
        printf("Player 1 wins!\n");
    }
    else if (points1 < points2) {
        printf("Player 2 wins!\n");
    }
    else {
        printf("Tie!\n");
    }
    printf("Score: Word 1: %i\n       Word 2: %i\n", points1, points2);
}

int calculate(string word) {
    int score = 0;
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] >= 65 && word[i] <= 90) { // alternative: if we do #include <ctype.h> and use isupper(word[i]) instead,
            score += points[word[i] - 'A'];   // we receive TRUE if the character is between 65 and 90 ASCII (uppercase letter).
        }
        else if (word[i] >= 97 && word[i] <= 122){ // here analogously, but islower(word[i]) instead, and it would
            score += points[word[i] - 'a'];        // check whether the character is between 97 and 122 ASCII.
        }
    }
    return score;
}
