#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE; // creates a variable type BYTE which is simply uint8_t (unsigned int of 8 bits - so a single byte)

int main(int argc, char *argv[])
{
    FILE *src = fopen(argv[1], "rb"); // opens the 1st file in read binary mode
    FILE *dst = fopen(argv[2], "wb"); // opens the 2nd file in write binary mode

    BYTE b; // declares an variable b of type BYTE

    while (fread(&b, sizeof(b), 1, src)) // while there are still bytes of size of a byte (read them one by one) to read from src file
    {
        fwrite(&b, sizeof(b), 1, dst); // write them into the dst file
    }

    // closes the opened files
    fclose(src);
    fclose(dst);
}
