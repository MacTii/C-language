#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

char **text_modifier(const char *text, int args, ...);

char *lower_to_upper(const char *in);
char *upper_to_lower(const char *in);
char *space_to_dash(const char *in);
char *reverse_letter(const char *in);

void free_texts(char **);

#endif // !__FUNCTIONS_H__