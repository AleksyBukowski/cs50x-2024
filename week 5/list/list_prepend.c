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

    // prepends the new node to the start of the list - prepend efficiency is O(1), because it simply adds another element
    // and makes the previous one point to the current 1st one, and the list points to the 1st element, the newly added one
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
        n->next = list;
        list = n;
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
