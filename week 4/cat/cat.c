#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./cat <file_name>\n");
        return 1;
    }

    char *filename = argv[1];

    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("File doesn't exist\n");
        return 2;
    }

    char c;
    while ((c = fgetc(f)) != EOF) // gets a single character from file, when it obtained one, then the "cursor" goes to the next char immediately
        printf("%c", c);

    fclose(f);
    return 0;
}

// there is also another function, fputc(<character>, <FILE pointer>) which puts a single char to a file
// you can use it to copy linux cp command, just like here we copied the linux cat command

// fseek() <-- lets you move (rewind or fast forward) a specific ammount of bytes through the file (so you don't have to use fread for that, if you JUST wanna skip
// a specific ammount of bytes etc)

// ftell() <-- tells you at which specific byte are you right now in a file

// feof() <-- tells you whether you've reached the end of the file
// ferror() <-- indicates whether an error has occured in working with a file
