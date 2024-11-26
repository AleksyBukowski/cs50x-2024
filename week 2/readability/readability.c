#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void check_grade(string txt);

int main(void) {
    string text = get_string("Text: ");
    check_grade(text);
}

void check_grade(string txt) {
    float letters = 0;
    float words = 1;
    float sentences = 0;

    int txtlen = strlen(txt);
    for (int i = 0; i < txtlen; i++) {
        if (isupper(txt[i]) || islower(txt[i])) {
            letters++;
        }
        else if (txt[i] == ' ') {
            words++;
        }
        else if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?') {
            sentences++;
        }
    }

    float L = letters / (words / 100);
    float S = sentences / (words / 100);

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1) {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index <= 16) {
        printf("Grade %i\n", index);
    }
    else {
        printf("Grade 16+\n");
    }
}
