#include <stdio.h>

#define N 100

int main()
{
    FILE *f2,*f3,*f5,*f0;
    f2=fopen("2.txt","w");
    if(f2==NULL)
    {
        printf("couldn't create file");
        return 5;
    }
    f3=fopen("3.txt","w");
    if(f3==NULL)
    {
        printf("couldn't create file");
        fclose(f2);
        return 5;
    }
    f5=fopen("5.txt","w");
    if(f5==NULL)
    {
        printf("couldn't create file");
        fclose(f2);
        fclose(f3);
        return 5;
    }
    f0=fopen("0.txt","w");
    if(f0==NULL)
    {
        printf("couldn't create file");
        fclose(f2);
        fclose(f3);
        fclose(f5);
        return 5;
    }
    printf("Podaj liczby:\n");
    int k=1,liczba=1;
    while(liczba!=0)
    {
        scanf("%d",&liczba);
        k=1;
        if(liczba%2==0 && liczba!=0) 
        {
            fprintf(f2,"%d\n",liczba);
            k=0;
        }
        if(liczba%3==0 && liczba!=0) 
        {
            fprintf(f3,"%d\n",liczba);
            k=0;
        }
        if(liczba%5==0 && liczba!=0) 
        {
            fprintf(f5,"%d\n",liczba);
            k=0;
        }
        if(k==1 && liczba!=0) fprintf(f0,"%d\n",liczba);
    }
    printf("Files saved");
    fclose(f2);
    fclose(f3);
    fclose(f5);
    fclose(f0);
    return 0;
}