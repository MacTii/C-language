#include <stdio.h>
#include <ctype.h>

#define COULDNT_OPEN_FILE 4
#define FILE_CORRUPTED 6

int main()
{
    char napis[31];
    char c = '0';
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", napis);
    FILE *f;
    f = fopen(napis, "r");
    if (f == NULL) return printf("Couldn't open file"), COULDNT_OPEN_FILE;
    int suma = 0, znak = 0, k = 0, ctrl = 0;
    fseek(f, 0, 0);
    int i = 0, count = 0;
    while (i != EOF)
    {
        i = fgetc(f);
        count++;
    }
    if (count == 1)
    {
        printf("File corrupted");
        fclose(f);
        return FILE_CORRUPTED;
    }
    count -= 1;
    fseek(f, 0, 0);
    for (;;)
    {
        int x = fscanf(f, "%c", &c);
        k++;
        if (c == ' ' || c == '\n' || x == EOF)
        {
            znak /= 10;
            //printf("%d %d\n", count, znak);
            if (count <= znak)
            {
                printf("File corrupted");
                fclose(f);
                return FILE_CORRUPTED;
            }
            znak = 0;
            if(c=='\n' || isalpha(c)) break;
        }
        if(isalpha(c))
        {
            printf("File corrupted");
            fclose(f);
            return FILE_CORRUPTED;  
        }
        if (isdigit(c))
        {
            znak += c - '0';
            znak *= 10;
        }
    }
    k = 0;
    for (;;)
    {
        fseek(f, k, 0);
        for (;;)
        {
            int x = fscanf(f, "%c", &c);
            /*if (!isdigit(c) && c != ' ' && c != '\n')
            {
                printf("File corrupted");
                fclose(f);
                system("PAUSE");
                return FILE_CORRUPTED;
            }*/
            k++;
            if (c == ' ' || c == '\n' || x == EOF || isalpha(c))
            {
                znak /= 10;
                if (count <= znak)
                {
                    printf("File corrupted");
                    fclose(f);
                    return FILE_CORRUPTED;
                }
                if (c == '\n') ctrl = 1;
                break;
            }
            /*if (c != 1)
            {
                printf("File corrupted");
                fclose(f);
                return FILE_CORRUPTED;
            }*/
            znak += c - '0';
            znak *= 10;
        }
        fseek(f, 0, 0);
        suma = 0;
        for (;;)
        {
            int x = fscanf(f, "%c", &c);
            suma++;
            if (x == EOF) break;
            if (suma - 1 == znak)
            {
                printf("%c", c);
                break;
            }
        }
        znak = 0;
        if (ctrl == 1) break;
    }
    fclose(f);
    return 0;
}