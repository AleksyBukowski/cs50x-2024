#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // doing this wouldnt work:
    // string s = "hi";
    // string t = s;
    // t[0] = toupper(t[0]);
    // print s
    // print t
    // as the equals symbol assigns the ADDRESS of string s to string t, therefore, making t[0] upper would also make s[0] upper
    // because it is exactly the same thing.

    char *s = get_string("s: ");
    if (s == NULL) { // <-- checks whether the string has space in memory, if doesn't - terminate
        return 1;
    }

    char *t = malloc(strlen(s) + 1); // malloc stands for memory allocation

    if (t == NULL) { // <-- checks whether we have enough memory (returns a specific address) needed for our string t
        return 1;
    }

    // copies each element of strins s to string t (new string, with different address)
    for (int i = 0, n = strlen(s); i <= n; i++) {
        t[i] = s[i];
    }

    // alternatively, theres a function:
    strcpy(t, s); // <-- copy s and paste it to t strcopy(destination, fromWhere)

    t[0] = toupper(t[0]); // makes the 1st letter of string t uppercase

    printf("%s\n", s);
    printf("%s\n", t);
    printf("%c%c\n", *t, *(t + 1)); // <- works just like an array, but using pointers

    free(t); // frees the memory that was used to store the string t, as C doesn't do it on its own,
    return 0; // but we don't have to (and should not) free the memory of string s because get_string() does its on its own though
}

// NUL is the \0 symbol, which symbolises the end of the string
// NULL is the addres zero which means there aren't any addresses to assign, because the address 0 is not actually used, it's a
// sentinel value that holds NULL to signify an error.
