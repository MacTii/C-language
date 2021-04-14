#include <stdio.h>
#include <stdlib.h>

int file_size_from_path(const char *path)
{
    if(path == NULL) return -2;
    FILE *f;
    f = fopen(path, "r");
    if(f==NULL)
    {
        return -1;
        fclose(f);
    }
    int count = 0;
    int i;
    while(i!=EOF)
    {
        i = fgetc(f);
        count++;
    }
    fclose(f);
    return count-1;
}

int file_size_from_file(FILE *f)
{
    if(f==NULL) return -2;
    long curpos, length;
    curpos = ftell(f);
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, curpos, SEEK_SET);
    return length;
}

int main() {

    char napis[31];
    char *wsk = napis; 
    printf("Podaj sciezke do pliku:\n");
    scanf("%30s", wsk);
    FILE *f;
    f = fopen(wsk, "r");
    if(f == NULL)
    {
        printf("Couldn't open file");
        exit(4);
    }
    int count1 = file_size_from_path(wsk);
    int count2 = file_size_from_file(f);
    if(count1 == count2) printf("Rozmiar pliku wynosi %d bajtow", count1);
    else printf("Error");
    fclose(f);
    return 0;
}
