#include <stdio.h>
#include <stdint.h>

#define INCORRECT -1
#define CORRECT 0
#define INCORRECT_INPUT 1
#define INVALID_BIT_INDEX 2
#define INVALID_OPERATION 2

struct bit_t
{
    unsigned char b0:1;
    unsigned char b1:1;
    unsigned char b2:1;
    unsigned char b3:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char b6:1;
    unsigned char b7:1;
};

union byte_t
{
    uint32_t value;
    struct bit_t bit[4];
};

int toggle_bit(uint32_t* pvalue, int b)
{
    if(pvalue==NULL || b<0 || b>31) return INCORRECT;
    union byte_t unia;
    unia.value=*pvalue;
    int i=b/8;
    switch(b%8)
    {
        case 0: ((unia.bit+i)->b0)=!((unia.bit+i)->b0);
        break;
        case 1: ((unia.bit+i)->b1)=!((unia.bit+i)->b1);
        break;
        case 2: ((unia.bit+i)->b2)=!((unia.bit+i)->b2);
        break;
        case 3: ((unia.bit+i)->b3)=!((unia.bit+i)->b3);
        break;
        case 4: ((unia.bit+i)->b4)=!((unia.bit+i)->b4);
        break;
        case 5: ((unia.bit+i)->b5)=!((unia.bit+i)->b5);
        break;
        case 6: ((unia.bit+i)->b6)=!((unia.bit+i)->b6);
        break;
        case 7: ((unia.bit+i)->b7)=!((unia.bit+i)->b7);
        break;
    }
    *pvalue=unia.value;
    return CORRECT;
}

int set_bit(uint32_t* pvalue, int b)
{
    if(pvalue==NULL || b<0 || b>31) return INCORRECT;
    union byte_t unia;
    unia.value=*pvalue;
    int i;
    if (b<8) i=0;
    if (b>7 && b<16)
    {
        i=1;
        b=b%8;
    }
    if(b>15 && b<24)
    {
        i=2;
        b=b%16;
    }
    if(b>23 && b<32)
    {
        i=3;
        b=b%24;
    }
    switch(b)
    {
        case 0: ((unia.bit+i)->b0)=1;
        break;
        case 1: ((unia.bit+i)->b1)=1;
        break;
        case 2: ((unia.bit+i)->b2)=1;
        break;
        case 3: ((unia.bit+i)->b3)=1;
        break;
        case 4: ((unia.bit+i)->b4)=1;
        break;
        case 5: ((unia.bit+i)->b5)=1;
        break;
        case 6: ((unia.bit+i)->b6)=1;
        break;
        case 7: ((unia.bit+i)->b7)=1;
        break;
    }
    *pvalue=unia.value;
    return CORRECT;
}

int clear_bit(uint32_t* pvalue, int b)
{
    if(pvalue==NULL || b<0 || b>31) return INCORRECT;
    union byte_t unia;
    unia.value=*pvalue;
    int i;
    if (b<8) i=0;
    if (b>7 && b<16)
    {
        i=1;
        b=b%8;
    }
    if(b>15 && b<24)
    {
        i=2;
        b=b%16;
    }
    if(b>23 && b<32)
    {
        i=3;
        b=b%24;
    }
    switch(b)
    {
        case 0: ((unia.bit+i)->b0)=0;
        break;
        case 1: ((unia.bit+i)->b1)=0;
        break;
        case 2: ((unia.bit+i)->b2)=0;
        break;
        case 3: ((unia.bit+i)->b3)=0;
        break;
        case 4: ((unia.bit+i)->b4)=0;
        break;
        case 5: ((unia.bit+i)->b5)=0;
        break;
        case 6: ((unia.bit+i)->b6)=0;
        break;
        case 7: ((unia.bit+i)->b7)=0;
        break;
    }
    *pvalue=unia.value;
    return CORRECT;
}

int isset_bit(const uint32_t* pvalue, int b)
{
    if(pvalue==NULL || b<0 || b>31) return INCORRECT;
    union byte_t unia;
    unsigned char wsk;
    unia.value=*pvalue;
    int i=b/8;
    switch(b%8)
    {
        case 0: wsk=((unia.bit+i)->b0);
        break;
        case 1: wsk=((unia.bit+i)->b1);
        break;
        case 2: wsk=((unia.bit+i)->b2);
        break;
        case 3: wsk=((unia.bit+i)->b3);
        break;
        case 4: wsk=((unia.bit+i)->b4);
        break;
        case 5: wsk=((unia.bit+i)->b5);
        break;
        case 6: wsk=((unia.bit+i)->b6);
        break;
        case 7: wsk=((unia.bit+i)->b7);
        break;
    }
    return wsk;
}

int main()
{
    uint32_t number;
    printf("Enter a value:\n");
    int x=scanf("%u",&number);
    if(x!=1) return printf("Incorrect input"),INCORRECT_INPUT;
    int index;
    printf("Enter an index of a bit:\n");
    int y=scanf("%d",&index);
    if(y!=1) return printf("Incorrect input"),INCORRECT_INPUT;
    if(index<0 || index>31) return printf("Invalid bit index"),INVALID_BIT_INDEX;
    printf("Select operation (0-toggle, 1-set, 2-clear, 3-read):\n");
    int op;
    int z=scanf("%d",&op);
    if(z!=1) return printf("Incorrect input"),INCORRECT_INPUT;
    if(op!=0 && op!=1 && op!=2 && op!=3) return printf("Invalid operation"),INVALID_OPERATION;
    int val;
    switch(op)
    {
        case 0:
            toggle_bit(&number,index);
            printf("%x",number);
            break;
        case 1:
            set_bit(&number,index);
            printf("%x",number);
            break;
        case 2:
            clear_bit(&number,index);
            printf("%x",number);
            break;
        case 3:
            val=isset_bit(&number,index);
            printf("%d",val);
            break;
    }
    return 0;
}
