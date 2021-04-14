#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define COULDNT_CREATE_FILE 5
#define N 1000

int main()
{
    char tablica[10];
    printf("Podaj liczbe liczb:\n");
    int ilosc;
    int x=scanf("%d",&ilosc);
    if(x!=1) return printf("Incorrect input"),INCORRECT_INPUT;
    if(ilosc<1 || ilosc>N) return printf("Incorrect input data"),INCORRECT_INPUT_DATA;
    int i,k=0,suma=10;
    srand(time(0));
    FILE* f;
    for(i=0;i<ilosc;i++)
    {
        if(suma==10)
        {
            suma=0;
            sprintf(tablica,"%d.txt",k);
            if((f=fopen(tablica,"wt"))==NULL) return printf("Couldn't create file"),COULDNT_CREATE_FILE;
            printf("%s\n",tablica);
            k++;
        }
        fprintf(f,"%d\n",rand()%(N+1));
        suma++;
        if(suma==10) fclose(f);
    }
    if(suma!=10) fclose(f);
    return 0;
}