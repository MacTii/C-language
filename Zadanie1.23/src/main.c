#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COULDNT_OPEN_FILE 4
#define POINTER_NULL -1
#define FILE_NULL 0

int recursion(FILE *f, int suma, int counter);

void show_new_line()
{
    printf("\n");
}

int read_file(const char *filename)
{
    if(!filename) return POINTER_NULL;
    FILE * f = fopen(filename, "r");
    if (f == NULL) return FILE_NULL;
    int counter = 0, suma_r = 1;
    int suma = recursion(f, suma_r, counter);
    fclose(f);
    return suma;
}

int recursion(FILE *f, int suma, int counter)
{
    char name[31];
    char* begin = name;
    char* wsk = name;
    char znak;
    for (;;)
    {
        int x = fscanf(f, "%c", &znak);
        if (x == EOF)
        {
            if (counter > 0)
            {
                *wsk = '\0';
                int y = read_file(name);
                if (y < 1)
                {
                    printf("%s", name);
                    show_new_line();
                    counter = 0;
                    wsk = begin;
                    return suma;
                }
                if (y >= 1)
                {
                    printf("%s", name);
                    show_new_line();
                    suma = suma + y;
                    counter = 0;
                    wsk = begin;
                    return suma;
                }
            }
            if (counter <= 0) return suma;
        }
        if (znak == '\n')
        {
            *wsk = '\0';
            if (counter > 0)
            {
                printf("%s", name);
                show_new_line();
                int y = read_file(name);
                if (y < 1)
                {
                    counter = 0;
                    wsk = begin;
                }
                if (y >= 1)
                {
                    suma = suma + y;
                    counter = 0;
                    wsk = begin;
                }
            }
            if (counter <= 0)
            {
                counter = 0;
                wsk = begin;
            }
        }
        if (znak != '\n')
        {
            counter += 1;
            *wsk = znak;
            wsk += 1;
        }
    }
}

int main()
{
    char nazwa[31];
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", nazwa);
    int suma = read_file(nazwa);
    if (suma == -1 || suma == 0) return printf("Couldn't open file"), COULDNT_OPEN_FILE;
    printf("%d", suma);
    //system("PAUSE");
    return 0;
}