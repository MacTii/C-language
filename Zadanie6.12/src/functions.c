#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void print_chicken(void)
{
    printf(" MM\n<' \\___/|\n  \\_  _/\n    ][\n");
}

void print_egg(void)
{
    printf("  .~~~.\n /     \\\n(\\/\\/\\/\\)\n \\     /\n  `~~~`\n");
}

void print_rabbit(void)
{
    printf(" \\\\   //\n  )\\-/(\n  /o o\\\n ( =T= )\n /'---'\\\n");
}

void (**easter(int size, void (*chicken)(void), void (*egg)(void), void (*rabbit)(void)))(void)
{
    if (size < 1 || !chicken || !egg || !rabbit)
        return NULL;

    void (**fun)(void) = (void (**)(void))calloc(size, sizeof(void (*)(void)));
    if (!fun)
        return NULL;

    srand((unsigned int)time(0));
    for (int i = 0; i < size; i++)
    {
        int choice = rand() % 3;
        switch (choice)
        {
        case 0:
            *(fun + i) = chicken;
            break;
        case 1:
            *(fun + i) = egg;
            break;
        case 2:
            *(fun + i) = rabbit;
            break;
        default:
            break;
        }
    }
    return fun;
}