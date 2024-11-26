#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

node *table[26];

int hash(string phrase);
bool unload(node *list);
void visualizer(node *list);

int main(void)
{
    // Add items
    for (int i = 0; i < 3; i++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // Find phrase bucket
        int bucket = hash(phrase);
        if (bucket == -1)
        {
            printf("Invalid input\n");
            return 1;
        }
        printf("%s hashes to %i\n", phrase, bucket);
    }
}

// TODO: return the correct bucket for a given phrase
int hash(string phrase)
{
    int bucket = toupper(phrase[0]) - 'A';
    if (bucket < 26 && bucket >= 0)
    {
        return bucket;
    }
    return -1;
}
