#include <stdio.h>
#include "flights.h"

#define INCORRECT_SAVE 1
#define PLIK_NULL_SAVE 2
#define FILE_CORRUPTED_SAVE 3
#define CORRECT 0
#define INCORRECT_LOAD -1
#define PLIK_NULL_LOAD -2
#define FILE_CORRUPTED_LOAD -3
#define INCORRECT_S -1
#define INCORRECT_B 1
#define NO_INFORMATION 2

int save_flights(const struct flight *flights, int size, const char *filename)
{
    if(flights==NULL || size<=0 || filename==NULL) return INCORRECT_SAVE;
    FILE *f;
    f=fopen(filename,"wb");
    if(f==NULL) return PLIK_NULL_SAVE;
    fwrite(&size,sizeof(int),1,f);
    size_t result2=fwrite(flights,sizeof(struct flight),size,f);
    if(!result2)
    {
        fclose(f);
        return FILE_CORRUPTED_SAVE;
    }
    fclose(f);
    return CORRECT;
}

int load_flights(struct flight *flights, int size, const char *filename)
{
    if(flights==NULL || size<=0 || filename==NULL) return INCORRECT_LOAD;
    FILE *f;
    f=fopen(filename,"rb");
    if(f==NULL) return PLIK_NULL_LOAD;
    int n=0;
    size_t result1=fread(&n,sizeof(int),1,f);
    if(result1!=1 || n<=0)
    {
        fclose(f);
        return FILE_CORRUPTED_LOAD;
    }
    if(n>size) n=size;
    int x=(int)fread(flights,sizeof(struct flight),n,f);
    if(x!=n)
    {
        fclose(f);
        return FILE_CORRUPTED_LOAD;
    }
    fclose(f);
    return n>0? n:FILE_CORRUPTED_LOAD;
}

int statistics_flight(const struct flight *flights, int size, struct flight *f, enum flight_t type)
{
    if(flights==NULL || size<=0 || f==NULL || (type!=CARGO && type!=PASSENGER)) return INCORRECT_S;
    f->type=type;
    f->flight_number=0;
    if(type==CARGO) f->tonnages=0;
    if(type==PASSENGER) f->npassengers=0;
    int suma=0,i=0;
    while(i<size)
    {
        if((flights+i)->type==type)
        {
            if(type==CARGO)
            {
                if((flights+i)->tonnages<0) return INCORRECT_S;
            }
            if(type==CARGO) f->tonnages += (flights+i)->tonnages;
            if(type==PASSENGER) f->npassengers += (flights+i)->npassengers;
            suma++;
        }
        i++;
    }
    f->flight_number=suma;
    return suma;
}

int best_flight(const struct flight *flights, int size, struct flight *f, enum flight_t type)
{
    if(flights==NULL || size <=0 || f==NULL || (type!=CARGO && type!=PASSENGER)) return INCORRECT_B;
    f->type = type;
    f->flight_number = 0;
    if(type==CARGO) f->tonnages = 0;
    if(type == PASSENGER) f->npassengers = 0;
    int i=0,suma=0;
    while(i<size)
    {
        if((flights+i)->type == type)
        {
            if(type==CARGO)
            {
                if((flights+i)->tonnages < 0) return INCORRECT_B;
            }
            if(type==CARGO)
            {
                if(f->tonnages<(flights+i)->tonnages || (f->tonnages==(flights+i)->tonnages && f->flight_number<(flights+i)->flight_number)) *f =*(flights+i);
            }
            if(type == PASSENGER)
            {
                if(f->npassengers < (flights+i)->npassengers || (f->npassengers == (flights+i)->npassengers && f->flight_number < (flights+i)->flight_number)) *f=*(flights+i);
            }
            suma++;
        }
        i++;
    }
    if(suma==0) return NO_INFORMATION;
    return CORRECT;
}
