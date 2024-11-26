#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

typedef struct node
{
    char *text;
    struct node *pointers[N];
} node;

void add(int key, char *text, node *list);
char *search(int key, node *list);
void free_mem(node *list);


int main(void)
{
    // create the 1st node
    node *list = malloc(sizeof(node));
    list->text = NULL;

    // add "Harvard" to the trie under the value of 1636
    add(1636, "Harvard", list);
    add(1701, "Yale", list);

    // ask for a key for searching
    int srch = get_int("Enter a key: ");
    printf("%s\n", search(srch, list)); // call and print out the search results

    free_mem(list); // free the list
}

// adds a key to trie
void add(int key, char *text, node *list)
{
    node *ptr = list; // set pointer to the head of the list
    int len = floor(log10(key)) + 1; // length of the key passed
    for (int i = pow(10, len - 1), num; i >= 1; i = i / 10) // iterate through each digit of the integer and allocate nodes
    {
        num = (key / i) % 10;
        if (ptr->pointers[num] != NULL) // if the pointer already exists, just go there
        {
            ptr = ptr->pointers[num];
        }
        else // if not, create it
        {
            node *n = malloc(sizeof(node));
            ptr->pointers[num] = n;
            ptr = n;
        }
    }

    ptr->text = text; // assign the value (e.g. "Harvard") to the specific "road" which comes from the key
}

// search through the trie
char *search(int key, node *list)
{
    node *sptr = list;
    int len = floor(log10(key)) + 1;
    for (int i = pow(10, len - 1), num; i >= 1; i = i / 10) // iterate through each digit of the key
    {
        num = (key / i) % 10;
        if (sptr->pointers[num] != NULL) // if that digits "gate" is opened, go there
        {
            sptr = sptr->pointers[num];
        }
        else // if not, return that the key isnt associated to any value in that trie
        {
            return "Invalid key; value not found";
        }
    }

    return sptr->text; // return the text associated with the key provided
}

// frees the list
void free_mem(node *fptr)
{
    for (int i = 0; i < N; i++) // iterate through each array element in a node
    {
        if (fptr->pointers[i] != NULL) // if a pointer is not null (exists) then call free mem passing THAT pointer
        {
            free_mem(fptr->pointers[i]);
        }
    }
    free(fptr); // if all pointers of the currently considered node are NULL, then free that note and pop that recursive call of the function, returning back to the last call
}
