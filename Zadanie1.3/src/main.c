#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char napis1[31],napis2[31];
    char *wsk1=napis1,*wsk2=napis2;
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s",wsk1);
    FILE *f1;
    f1=fopen(wsk1,"r");
    if(f1==NULL)
    {
        printf("couldn't open file");
        return 4;
    }
    setbuf(stdin,NULL);
    printf("Podaj sciezke do pliku wyjsciowego:\n");
    scanf("%30s",wsk2);
    FILE *f2;
    f2=fopen(wsk2,"w");
    if(f2==NULL)
    {
        printf("couldn't create file");
        fclose(f1);
        return 5;
    }
    int chr;
    while((chr=fgetc(f1))!=EOF)
    	fputc(chr,f2);
    printf("File copied");
    fclose(f1);
    fclose(f2);
    return 0;
}
