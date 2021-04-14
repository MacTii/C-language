#include <stdio.h>

#define INCORRECT 1
#define PLIK_NULL 2
#define FILE_CORRUPTED 3
#define FILE_CORR 4
#define CORRECT 0
#define N 1000
#define L 30
#define COULDNT_OPEN_FILE 4
#define INCORRECT_INPUT_DATA 1
#define COULDNT_CREATE_FILE 5
#define FILE_CORRUPTED_E 3
#define FILE_CORRUPTED_D 6

struct bit_t
{
    unsigned int b0:1;
    unsigned int b1:1;
    unsigned int b2:1;
    unsigned int b3:1;
    unsigned int b4:1;
    unsigned int b5:1;
    unsigned int b6:1;
    unsigned int b7:1;
};

union byte_t
{
    unsigned char byte;
    struct bit_t bit;
};

void show()
{
    printf("\n");
}

int decode(const char *filename, char *txt, int size)
{
    if(filename==NULL || txt==NULL || size<=0) return INCORRECT;
    FILE *f = fopen(filename,"r");
    if(f==NULL) return PLIK_NULL;
    union byte_t result;
    union byte_t read;
    int size_read=0,number,i=0;
    while(1)
    {   
        if(feof(f) || i+1==size) break;
        int x=fscanf(f,"%d",&number);
        if(x!=1)
        {
            fclose(f);
            return FILE_CORRUPTED;
        }
        read.byte = number;
        switch(size_read)
        {
            case 0:
                result.bit.b7 = read.bit.b0;
                size_read++;
                break;
            case 1:
                result.bit.b6 = read.bit.b0;
                size_read++;
                break;
            case 2:
                result.bit.b5 = read.bit.b0;
                size_read++;
                break;
            case 3:
                result.bit.b4 = read.bit.b0;
                size_read++;
                break;
            case 4:
                result.bit.b3 = read.bit.b0;
                size_read++;
                break;
            case 5:
                result.bit.b2 = read.bit.b0;
                size_read++;
                break;
            case 6:
                result.bit.b1 = read.bit.b0;
                size_read++;
                break;
            case 7:
                result.bit.b0 = read.bit.b0;
                *(txt+i) = (char)result.byte;
                i+=1;
                size_read=0;
                break;
        }
    }
    if(size_read!=0)
    {
        fclose(f);
        return FILE_CORRUPTED;
    }
    *(txt+i)='\0';
    fclose(f);
    return CORRECT;
}

int encode(const char *input, char *txt, const char *output)
{
    if(input==NULL || txt==NULL || output==NULL) return INCORRECT;
    FILE *f=fopen(input,"r");
    if(f==NULL) return PLIK_NULL;
    FILE *w=fopen(output,"w");
    if(w==NULL)
    {
        fclose(f);
        return FILE_CORR;
    }
    int i,err,check=1;
    char znak='\0';
    char znak2='\n';
    union byte_t read;
    union byte_t result;
    for(i=0;*(txt+i)!=znak && check;i+=1)
    {
        read.byte=*(txt+i);
        int j;
        for(j=0;j<8;j+=1)
        {   
            long pos1=ftell(f); 
            err=fscanf(f,"%d",(int*)&result.byte);  
            long pos2=ftell(f);
            if(!err)
            {
                fclose(f);
                fclose(w);
                return FILE_CORRUPTED;
            }
            else
            {
                if(err==EOF && j!=0)
                {
                    fclose(f);
                    fclose(w);
                    return FILE_CORRUPTED;
                }
                else
                {
                    if(err==EOF)
                    {
                        check=0;
                        break;
                    }
                }
            }
            int l=1;        
            char temp;
            fseek(f,pos1+l,SEEK_SET);
            fscanf(f,"%c",&temp);
            fseek(f,pos2,SEEK_SET);
            if(temp=='\n') fprintf(w,"\n");
            switch(j)
            {
                case 0:
                    result.bit.b0=read.bit.b7;
                    break;
                case 1:
                    result.bit.b0=read.bit.b6;
                    break;
                case 2:
                    result.bit.b0=read.bit.b5;
                    break;
                case 3:
                    result.bit.b0=read.bit.b4;
                    break;
                case 4:
                    result.bit.b0=read.bit.b3;
                    break;
                case 5:
                    result.bit.b0=read.bit.b2;
                    break;
                case 6:
                    result.bit.b0=read.bit.b1;
                    break;
                case 7:
                    result.bit.b0=read.bit.b0;
                    break;
            }
            fprintf(w,"%d ",result.byte);
        }
    }
    if(*(txt+i)!=znak)
    {
        fclose(f);
        fclose(w);
        return FILE_CORRUPTED;
    }
    int k=1;
    char temp;
    long pos1=ftell(f); 
    fseek(f,pos1+k,SEEK_SET);
    fscanf(f,"%c",&temp);
    fseek(f,pos1,SEEK_SET);
    if(temp==znak2) fprintf(w,"\n");
    int z=0;
    while((err=fscanf(f," %d",(int*)&result.byte))!=EOF)
    {
        result.bit.b0=z;    
        fprintf(w,"%d ",result.byte);
        long pos1=ftell(f); 
        fseek(f,pos1+k,SEEK_SET);
        fscanf(f,"%c",&temp);
        fseek(f,pos1,SEEK_SET);
        if(temp==znak2) fprintf(w,"\n");
    }
    fclose(f);
    fclose(w);
    return CORRECT;
}

int main()
{
    printf("Do you want to encode (E/e) or decode (D/d) a message? ");
    char znak,tab[N+1],input[L+1],output[L+1];
    scanf("%c",&znak);
    char c;
    do{
    c=getchar();
    }while(c!='\0'&&c!='\n');
    if(znak=='E' || znak=='e')
    {
        printf("Enter a message to be encoded: ");
        scanf("%1000[^\n]",tab);
        char c;
        do{
        c=getchar();
        }while(c!='\0'&&c!='\n');
        printf("Enter input file name: ");
        scanf("%30[^\n]",input);
        do{
        c=getchar();
        }while(c!='\0'&&c!='\n');
        printf("Enter output file name: ");
        scanf("%30[^\n]",output);
        do{
        c=getchar();
        }while(c!='\0'&&c!='\n');
        int x=encode(input,tab,output);
        if(x==2) return printf("Couldn't open file"),COULDNT_OPEN_FILE;
        if(x==4) return printf("Couldn't create file"),COULDNT_CREATE_FILE;
        if(x==3) return  printf("File corrupted"),FILE_CORRUPTED_E;
        printf("File saved");
    }
    else if(znak=='D' || znak=='d')
    {
        printf("Enter input file name: ");
        scanf("%30s",input);
        int x=decode(input,tab,N+1);
        if(x==2) return printf("Couldn't open file"),COULDNT_OPEN_FILE;
        if(x==3) return printf("File corrupted"),FILE_CORRUPTED_D;
        printf("%s", tab);
    }
    else return printf("Incorrect input data"),INCORRECT_INPUT_DATA;
    return 0;
}
