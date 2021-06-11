#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#define CHAR_BITS 8

#define COUNT_BITS(value, pointer_to_bits_set_counter, pointer_to_bits_cleared_counter) \
    *pointer_to_bits_set_counter = 0;                                                   \
    *pointer_to_bits_cleared_counter = 0;                                               \
    for (int i = 0; i < (int)sizeof(value) * CHAR_BITS; i++)                            \
    {                                                                                   \
        if (value & (long long)1 << i)                                                  \
            (*pointer_to_bits_set_counter)++;                                           \
        if (!(value & (long long)1 << i))                                               \
            (*pointer_to_bits_cleared_counter)++;                                       \
    }

#define DISPLAY_BITS(value)                                           \
    {                                                                 \
        for (int i = (int)sizeof(value) * CHAR_BITS - 1; i >= 0; i--) \
        {                                                             \
            if (value & (long long)1 << i)                            \
                printf("1");                                          \
            if (!(value & (long long)1 << i))                         \
                printf("0");                                          \
        }                                                             \
    }

#define REVERSE_BITS(pointer_to_variable)                                                        \
    {                                                                                            \
        long long tmp = 0;                                                                       \
        for (int i = (int)sizeof(*pointer_to_variable) * CHAR_BITS - 1, j = 0; i >= 0; i--, j++) \
        {                                                                                        \
            if (*pointer_to_variable & (long long)1 << i)                                        \
                tmp += (long long)1 << j;                                                        \
        }                                                                                        \
        *pointer_to_variable = tmp;                                                              \
    }

#endif // !__FUNCTIONS_H__