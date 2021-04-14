#include <stdio.h>

#define COULDNT_OPEN_FILE 4

int main()
{
    char napis[31];
    printf("Podaj sciezke:\n");
    scanf("%30[^\n]s",napis);
    FILE *f;
    f=fopen(napis,"rb");
    if(f==NULL) return printf("Couldn't open file"),COULDNT_OPEN_FILE;
    int i;
    for(;;)
    {
        i=fgetc(f);
        if(i==EOF) break;
        printf("%d ",i);
    }
    fclose(f);
}
