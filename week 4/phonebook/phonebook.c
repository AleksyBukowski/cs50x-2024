#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *file = fopen("phonebook.csv", "a"); // <-- opens file phonebook.csv in append mode and assigns the address of it to variable file of type pointer file
    if (file == NULL) // check whether the pointer is NULL, if so, terminate
    {
        return 1;
    }

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    fprintf(file, "%s,%s\n", name, number); // print into file file

    fclose(file);
    return 0;
}
