#include <stdio.h>
#include "flights.h"

#define N 39
#define SIZE_STRUCT 100
#define RESULT_STRUCT 4
#define COULDNT_OPEN_FILE 4
#define COULDNT_CREATE_FILE 5
#define FILE_CORRUPTED 6
#define INCORRECT_INPUT_DATA 2

int main()
{
    struct flight flights[SIZE_STRUCT];
    struct flight wynik[RESULT_STRUCT];
    char filename[N+1];
    printf("Podaj nazwe pliku: ");
    scanf("%39s",filename);
    int x=load_flights(flights, SIZE_STRUCT, filename);
    if(x==-2) return printf("Couldn't open file"),COULDNT_OPEN_FILE;
    if(x==-3) return printf("File corrupted"),FILE_CORRUPTED;
    int n=0;
    n += statistics_flight(flights, x, wynik, PASSENGER) > 0 && 1;
    n += statistics_flight(flights, x, wynik+n, CARGO) && 1;
    n += !best_flight(flights, x, wynik+n, PASSENGER) && 1;
    n += !best_flight(flights, x, wynik+n, CARGO) && 1;
    if(n > 0)
    {
        int x=save_flights(wynik, n, filename);
        if(x==2) return printf("Couldn't create file"),COULDNT_CREATE_FILE;
        printf("File saved");
    }
    if(n<=0) return printf("Incorrect input data"),INCORRECT_INPUT_DATA;
    return 0;
}
