#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Please specify at least one element\n");
        return 1;
    }

    node *list = NULL;
    int number;

    // append efficiency is O(n), because it has to look through the entire list to seek for the end and then
    // add the newest element to the end of the list
    for (int i = 1; i < argc; i++)
    {
        number = atoi(argv[i]);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            printf("Memory error\n");
            return 2;
        }
        n->number = number;
        n->next = NULL;

        if (list == NULL)
        {
            list = n;
        }
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL)
                {
                    ptr-> next = n;
                    break;
                }
            }
        }
    }

    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }


    // freeing the memory
    // node *fptr = list->next;
    // for (int i = 1; i < argc; i++)
    // {
    //     fptr = list->next;
    //     free(list);
    //     list = fptr;
    // }

    node *fptr = list->next;
    while (fptr != NULL)
    {
        fptr = list->next;
        free(list);
        list = fptr;
    }
}
