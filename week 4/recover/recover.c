#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for argument count
    if (argc != 2)
    {
        printf("Usage: ./recover card\n");
        return 1;
    }

    // set filename (card name) variable to the argument provided
    char *filename = argv[1];

    // open the file (card file)
    FILE *f = fopen(filename, "r");
    if (f == NULL) // check whether the file exists (if not, terminate)
    {
        printf("Invalid file\n");
        return 2;
    }

    FILE *img; // declare a variable to use as the each-new-recovered-image-address
    uint8_t chunk[512]; // declare a buffer
    int counter = 0; // counter to count the file names
    char *newfile = malloc(8 * sizeof(char)); // declare a variable to store the names of the new images recovered, make sure it has enough space
    if (newfile == NULL) // if no space in memory for newfile variable, terminate
    {
        printf("Error allocating memory\n");
        return 3;
    }

    do // read card file untill we see the 1st .jpg file
    {
        if(fread(chunk, (512 * sizeof(uint8_t)), 1, f) <= 0) // just in case, if read gets to the end of the file and there are no JPGs, terminate
        {
            printf("The file specified does not contain any .jpg files\n");
            return 4;
        }
    }
    while (!(chunk[0] == 255 && chunk[1] == 216 && chunk[2] == 255 && chunk[3] >= 224));



    img = fopen("000.jpg", "w"); // create the 1st file
    fwrite(chunk, (512 * sizeof(uint8_t)), 1, img); // write the 1st chunk of the 1st file (the chunk containing the typical-to-jpg signature values which we detected above) to the 1st img file
    fread(chunk, (512 * sizeof(uint8_t)), 1, f); // read ANOTHER chunk

    do // read card file until it ends
    {
        if (chunk[0] == 255 && chunk[1] == 216 && chunk[2] == 255 && chunk[3] >= 224) // if signature values at the start detected, then
        {
            fclose(img); // close the current file (previous one)

            counter++; // count one up
            sprintf(newfile, "%03i.jpg", counter); // update the newfile string value and make it contain the new name of another img file...
            img = fopen(newfile, "w"); // ...which we create here
        }
        fwrite(chunk, (512 * sizeof(uint8_t)), 1, img); // write chunk to img file
    }
    while (fread(chunk, (512 * sizeof(uint8_t)), 1, f)); // after the entire card .raw file ends, the loop ends

    free(newfile); // free the memory allocated for newfile string that contained each new .jpgs name
    fclose(img); // close the last img file
    fclose(f); // close the entire card file
    return 0;
}
