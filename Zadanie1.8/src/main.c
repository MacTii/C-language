#include <stdio.h>
#include <ctype.h>

#define COULDNT_OPEN_FILE 4
#define FILE_CORRUPTED 6

int main()
{
    char napis[31];
    int liczba;
    printf("Podaj sciezke do pliku:\n");
    scanf("%30[^\n]s",napis);
    FILE *f;
    f=fopen(napis,"r");
    if(f==NULL) return printf("Couldn't open file"),COULDNT_OPEN_FILE;
    int suma=0;
    for(;;)
    {
        int x=fscanf(f,"%d",&liczba);
        if(x==EOF) break;
        if(x!=1) 
        {
            printf("File corrupted");
            fclose(f);
            return FILE_CORRUPTED;
        }
        suma+=liczba;
    }
    printf("Suma wczytanych liczb wynosi: %d",suma);
    fclose(f);
    return 0;
}
