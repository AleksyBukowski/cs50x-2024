// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1169; // 26 * (45 - 1) + 25 (last possible character, "z")

// Hash table
node *table[N];

// global word counter
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashnum = hash(word);
    for (node *ptr = table[hashnum]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hashnum = (strlen(word) - 1) * 26 + (tolower(word[0]) - 'a'); // alternatively, we could do strlen(word) / 2 * 26 ...  <-- the array would be 2 times shorter, but the program would be slower
    // int hashnum = (tolower(word[0]) - 'a') * 45 + strlen(word);
    return hashnum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    char *word = malloc(sizeof(char) * 46);
    if (word == NULL)
    {
        return false;
    }
    int hashnum = 0;

    while (fscanf(f, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        hashnum = hash(word);
        if (table[hashnum] == NULL)
        {
            n->next = NULL;
        }
        else
        {
            n->next = table[hashnum];
        }
        table[hashnum] = n;
        word_count++;
    }

    fclose(f);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *point = table[0]; // point at a random existing memory place that is different to NULL

    for (int i = 0; i < N; i++) // loop through the array and free the memory
    {
        if (table[i] == NULL)
        {
            continue;
        }

        point = table[i];
        for (node *fptr = point; fptr != NULL; fptr = point)
        {
            point = fptr->next;
            free(fptr);
        }
    }

    if (point == NULL) // if the initialized pointer is now pointing to NULL, it means that the entire array was freed
    {
        return true;
    }

    return false;
}
