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

    // append efficiency is O(n), because it has to look through the list to see where the current node belongs, checking
    // through the list and iterating through numbers that are smaller than the current one we're considering and stopping when we
    // encounter a bigger number - so it's not always n steps, but in worst case it is indded O(n)
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
        // if number belongs to the start of the list (is smaller)
        else if (n->number < list->number)
        {
            n->next =list;
            list = n;
        }
        else // if number belongs later in the list
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next) // check where the current number belongs
            {
                if (ptr->next == NULL) // if its the end already, append it to the end of the list
                {
                    ptr-> next = n;
                    break;
                }
                // if in the middle of the list
                if (n->number < ptr->next->number) // if the currents node number is less than the currents iteration NEXT NODE number, then add it there
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }
            }   // we need the above ifs in that specific order, because if we check for the 2nd if first, we might encounter a segmentation fault
        }       // because we would be accessing things that do not exist with ptr->next->number, if the list already ends and doesn't have anything further
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
