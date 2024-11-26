#include <stdio.h>
#include <cs50.h>

int main(void){
    string s = "HI!";
    // the fourth place hold the sentinel value which is the \0 symbol, which is essentially eight bits (1 byte) each with the value 0, telling the computer that the string ends here.
    // its called a NUL, and it is the 0 character in the ASCII table
    printf("%i %i %i %i\n", s[0], s[1], s[2], s[3]);
}
