#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

uint8_t b[4];

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./pdf <filename>\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening a file\n");
        return 1;
    }

    int blocks_read = fread(b, 1, 4, file);

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", b[i]);
    }

    if (b[0] == 37 && b[1] == 80 && b[2] == 68 && b[3] == 70)
    {
        printf("That is a PDF file\n");
    }
    else
    {
        printf("NOT an PDF file.\n");
    }

    printf("Blocks read: %i\n", blocks_read);

    fclose(file);
}
