#include <cs50.h>
#include <stdio.h>

int main(void) {
    int n = 50; // decalres a variable n of value 50
    int *p = &n; // declares a pointer, which will be the value of the address of the variable n

    // int* p = &n; <-- works the same way, but kind of less convenient (although looks clearer -
    // "declare a variable p of type int* (pointer)")

    int **pp = &p;

    printf("%p\n", p); // print the address of n
    printf("%i\n", *p); // go to that address and show me what's inside (variable n)
    // printf("%p\n", pp); // print the address of address of n

    printf("\n");

    string s = "HI!";
    printf("%p\n", s); // s stores the address of the start of the string, and the computer
    printf("%p\n", &s[0]); // knows when to stop because of the \0 null character which ends the string
    // therefore, the address of the string is the same as the adderss of the 1st character of that string
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]); // the characters are one byte away from eachother, because a string is an array
    printf("%p\n", &s[3]); // <-- the null character

    char *str = "hello"; // string is technically a char star (address of the 1st character of a string)
    printf("%s\n", str);
}

// int *p;          <-- declares a pointer
// int i;           <-- declares an int
// int *p2 = &i;    <-- declares a pointer and assigns the address of the integer i

// you use int *<pointer_name> to create a pointer variable
// you use x = *<pointer_name> to access the value stored at the address of the pointer and assign it to x
// you use int *y = &b to acces the address of a variable b and assign it to the pointer of name y
