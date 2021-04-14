#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 100
#define K 30
#define COULDNT_CREATE_FILE 5

int main()
{
    float tab[N];
    float *wsk=tab;
    char napis[K+1];
    srand(time(0));
    printf("Podaj sciezke do pliku:\n");
    scanf("%30[^\n]s",napis);
    FILE *f;
    f=fopen(napis,"wb");
    if(f==NULL) return printf("Couldn't create file"),COULDNT_CREATE_FILE;
    int i;
    for(i=0;i<N;i++) *(wsk+i)=(double)rand()/RAND_MAX*(100);
    fwrite(tab,sizeof tab,1,f);
    printf("File saved");
    fclose(f);
    return 0;
}
