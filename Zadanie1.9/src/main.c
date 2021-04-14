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
    f=fopen(napis,"rwb");
    if(f==NULL) return printf("Couldn't open file"),COULDNT_OPEN_FILE;
    int ctrl;
    int z=fscanf(f,"%d",&liczba);
    ctrl=liczba;
    if(z!=1 || ctrl<=0)
    {
        printf("File corrupted");
        fclose(f);
        return FILE_CORRUPTED;
    }
    long suma=0;
    int k=0;
    setbuf(stdin,NULL);
    int i;
    for(i=0;i<ctrl;i++)
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
        k++;
    }
    if(k+1<ctrl)
    {
        printf("File corrupted");
        fclose(f);
        return FILE_CORRUPTED;
    }
    float srednia=(float)suma/(float)k;
    printf("%li\n%f",suma,srednia);
    fclose(f);
    return 0;
}
