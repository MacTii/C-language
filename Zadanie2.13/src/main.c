#include <stdio.h>

#define INCORRECT_V1 -1
#define INCORRECT_V2 1
#define COULDNT_OPEN_FILE -2
#define FILE_CORRUPTED -3
#define N 100
#define K 30
#define L 1100

struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename)
{
    if(cp==NULL || size<=0 || filename==NULL) return INCORRECT_V1;
    FILE* f=fopen(filename,"rb");
    if(f==NULL) return COULDNT_OPEN_FILE;
    unsigned int number;
    int x=fread(&number,sizeof(unsigned int),1,f);
    if(x!=1)
    {
        fclose(f);
        return FILE_CORRUPTED;
    }
    if(number%sizeof(struct message_t)!=0)
    {
        fclose(f);
        return FILE_CORRUPTED;
    }
    int przesuniecie=4;
    fseek(f, przesuniecie, SEEK_SET);
    int z = number/sizeof(struct message_t);
    int control;
    if(z<=size)
    {
        int k=fread(cp, sizeof(struct message_t), z, f);
        if(k!=z)
        {
            fclose(f);
            return FILE_CORRUPTED;
        }
        control=1;
    }
    if(z>size)
    {
        int k = fread(cp, sizeof(struct message_t), size, f);
        if(k!=size)
        {
            fclose(f);
            return FILE_CORRUPTED;
        }
        control=2;
    }
    fclose(f);
    return (control==1)? z:size;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size)
{
    if(cp==NULL || size<=0 || msg==NULL || text_size<=0) return INCORRECT_V2;
    int i=0,k=0;
    while(i<size)
    {
        unsigned int j;
        for(j=0;k<text_size && j<sizeof(struct message_t);j++)
        {
            if((j>0 && j<8) || (j >19 && j < sizeof(struct message_t))) *(msg+k++)=*((char*)(cp+i)+j);
        }
        i++;
    }
    *(msg+k-1)='\0';
    return 0;
}

int main()
{
    char filename[K+1];
    printf("Enter file name: ");
    scanf("%30[^\n]",filename);
    struct message_t p[N];
    int x = load_data(p, N, filename);
    if(x==-2) return printf("Couldn't open file"),4;
    if(x==-1 || x==-3) return printf("File corrupted"),6;
    char text[L+1];
    int y=decode_message(p, sizeof(p), text, sizeof(text));
    if(y==1) return printf("File corrupted"),6;
    printf("%s", text);
    return 0;
}