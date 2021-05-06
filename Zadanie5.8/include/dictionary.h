#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

struct word_count_t
{
    char *word;
    int counter;
};

struct dictionary_t
{
    int size;
    int capacity;
    struct word_count_t *wc;
};

char *my_strcpy(char *destination, const char *source);
int my_strcmp(char *strg1, const char *strg2);

struct dictionary_t* create_dictionary(int N, int *err_code);
void destroy_dictionary(struct dictionary_t** d);

int dictionary_add_word(struct dictionary_t *d, const char *word);
struct word_count_t* dictionary_find_word(const struct dictionary_t *d, const char *word);

void dictionary_display(const struct dictionary_t *d);

#endif // !__DICTIONARY_H__
