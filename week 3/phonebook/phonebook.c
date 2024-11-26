#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// we define a type person, which can store the name and the number
typedef struct {
    string name;
    string number;
} person;

const int N = 3;

string capitalize(string txt);

int main(void) {
    person people[N];

    people[0].name = "Carter";
    people[0].number = "+1-617-495-1000";

    people[1].name = "David";
    people[1].number = "+1-617-495-1000";

    people[2].name = "John";
    people[2].number = "+1-949-468-2750";

    string name = get_string("Name: ");
    // we make sure the name variable is capitalized, so that it matches the format in the people array,
    // which makes the program case insensitive
    name = capitalize(name);

    for (int i = 0; i < N; i++) {
        if (strcmp(people[i].name, name) == 0) {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}

// this function returns any given text as capitalized
string capitalize(string txt) {
    int len = strlen(txt);
    for (int j = 0; j < len; j++) {
        txt[j] = (j != 0) ? tolower(txt[j]) : toupper(txt[j]);
    }
    return txt;
}
