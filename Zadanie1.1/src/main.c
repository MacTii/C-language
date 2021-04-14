#include <stdio.h>
#include <stdlib.h>

#define N 30

int main()
{
    char napis[31];
    char *wsk=napis;
    printf("Podaj sciezke do pliku:\n");
    int i;
    for(i=0;i<N;i++)
    {
        scanf("%c",wsk+i);
        if(*(wsk+i)=='\n')
        {
            *(wsk+i)='\0';
            break;
        }
    }
    FILE *f;
    if((f=fopen(wsk,"r"))==NULL)
    {
        printf("couldn't open file");
        exit(4);
    }
    int j,suma=0;
    for(;;)
    {
        j=fgetc(f);
        suma++;
        if(j==EOF) break;
        putchar(j);
    }
    if(suma==1) printf("nothing to show");
    fclose(f);
    return 0;
}
