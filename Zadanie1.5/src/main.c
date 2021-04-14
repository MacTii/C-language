#include <stdio.h>
#include <string.h>

int main()
{
    char napis[31];
    char *wsk=napis;
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s",wsk);
    FILE *f;
    f=fopen(wsk,"w");
    if(f==NULL)
    {
        printf("couldn't create file");
        return 5;
    }
    int i;
    for(i=0;i<101;i++) fprintf(f,"%d\n",i);
    printf("File saved");
    fclose(f);
    return 0;
}
