#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

void print_chicken(void);
void print_egg(void);
void print_rabbit(void);

void (**easter(int size, void (*print_chicken)(void), void (*print_egg)(void), void (*print_rabbit)(void))) (void);

#endif // !__FUNCTIONS_H__