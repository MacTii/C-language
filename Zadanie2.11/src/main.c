#include <stdio.h>
#include <string.h>

#define N 1000
#define K 5
#define L 31
#define COULDNT_OPEN_FILE 4
#define CORRECT 0
#define INCORRECT 1
#define PLIK_NULL 2

struct file_t
{
    FILE *f;
    int size;
};

int open_file(struct file_t* f, const char *filename)
{
    if(filename==NULL || f==NULL) return INCORRECT;
    FILE *file = fopen(filename, "a");
    if(file == NULL) return PLIK_NULL;
    f->f = file;
    f->size = ftell(file);
    return 0;
}

struct file_t* find_min(const struct file_t* files, int size)
{
    if(size <= 0 || files==NULL) return NULL;
    int min = 0, i;
    int position = 0;
    min = files->size;
    for(i = 0; i < size ; i++)
    {
        if((files+i)->size < min)
        {
            min = (files+i)->size;
            position = i;
        }
    }
    return (struct file_t*)(files+position);
}

void close_file(struct file_t* f)
{
    if(f==NULL || f->f==NULL) return;
    fclose(f->f);
}

int main()
{
    struct file_t file[K];
    char filename[L],text[N];
    struct file_t *new_file;
    int i=0;
    printf("Podaj nazwy plikow:\n");
    while(1)
    {
        if(i==5) break;
        fgets(filename,L,stdin);
        if(*filename=='\n') break;
        *(filename+strlen(filename)-1)='\0';
        int x=open_file(file+i,filename);
        if(x==0) i++;
    }
    if(i==0)
    {
        printf("Couldn't open file");
        return COULDNT_OPEN_FILE;
    }
    setbuf(stdin,NULL);
    printf("Podaj teksty:\n");
    while(1)
    {   
        fgets(text,N,stdin);
        if(*text=='\n') break;
        *(text+strlen(text)-1)='\0';
        new_file=find_min(file,i);
        if(new_file->f!=NULL) fprintf(new_file->f, "%s\n", text);
        new_file->size=ftell(new_file->f);
    }
    int k;
    for(k=0; k<i; k++) close_file(file+k);
    printf("Files saved");
    return 0;
}

