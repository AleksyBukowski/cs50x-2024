#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void check(string phrase);

// int main(int argc, string argv[]) {
//     check(argv[1]);
// }

int main(void) {
    string text = get_string("Enter a phrase: ");
    check(text);
}

void check(string phrase) {
    bool isAlphabetical = true;
    bool specialChar = false;

    int length = strlen(phrase);    // strlen() is used here instead of being inside the for loop so that
                                    // the function doesn't have to run with each iteration of the loop
    for (int i = 0; i < length-1; i++) {
        // this condition compares a letter, and the letter after it.
        // first, we bring both of these letters to lowercase to make sure we're operating on the same ASCII scope,
        // because, e.g. 'a' is 97 ASCII, and 'D' is 68 ASCII, which would make the word "aDD" not in alphabetical order,
        // even though it is alphabetical. When both letters are converted to lowercase, we then look whether the ASCII code
        // of the letter before is HIGHIER than the code of the next letter - if so, then the word can't be in alphabetical order.
        if (tolower(phrase[i]) > tolower(phrase[i+1])) {
            isAlphabetical = false;
        }

        // here, we check whether the 1st OR the 2nd letter is outside of the ASCII letter scope - if so, we
        // know that we are dealing with a special character.
        if ((!islower(phrase[i]) && !isupper(phrase[i])) || (!islower(phrase[i+1]) && !isupper(phrase[i+1]))) {
            specialChar = true;
        }
    }

    if(isAlphabetical && !specialChar){
        printf("The phrase is in alphabetical order.\n");
    }
    else if (specialChar) {
        printf("The phrase should not contain characters other than letters.\n");
    }
    else{
        printf("The phrase is NOT in alphabetical order.\n");
    }
}
